#include "osrb_pch.h"
#include "EnchantBot.h"
#include "OsrItemInfo.h"
#include "Utility.h"

EnchantBot::EnchantBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_state = EnchantBotState::STANDBY;
	ResetEnchantList(m_currentEnchantDisplayList);
	ResetEnchantList(m_wantedEnchantDisplayList);

	m_amount_chancecard_3 = 0;
	m_amount_chancecard_5 = 0;
	m_amount_chancecard_8 = 0;
	m_amount_enchprot_e1 = 0;
	m_amount_enchprot_e5 = 0;
	m_next_action = EnchantAction::Add_EnchantItem;
	m_previous_enchantnum = 0;
	m_waiting_for_answer = false;
	m_currentEnchantItemUID = 0;
	m_optimiseEnchanting = false;
	m_withLuckyCard = false;
	m_auto_enchant = false;	  
	m_using_chancecard_8 = false;
	m_using_enchprot_e1 = false;
	m_using_enchprot_e5 = false;
	m_using_speedcard = false;

	m_enchant_timer = BuddyTimer(ENCHANT_TIME_BASE, ENCHANT_TIME_VARIANCE);
	m_action_timer = BuddyTimer(ENCHANT_ACTION_TIME_BASE, ENCHANT_ACTION_TIME_VARIANCE);

	m_enchantTargetKind = EnchantItemKind::Weapon_advanced;

	ZeroMemory(&m_statisticsSession, sizeof(ItemLabStatistics));
}

EnchantBot::~EnchantBot()
{
}

void EnchantBot::Tick()
{												   
	if (!IsEnabled()) {
		return;
	}

	bool character_in_laboratory = (OSR_API->GetCurrentBuildingKind() == BUILDINGKIND_LABORATORY);
	if (m_state != EnchantBotState::NOT_IN_LABORATORY && !character_in_laboratory) 
	{
		SetEnchantBotState(EnchantBotState::NOT_IN_LABORATORY);
		ResetCurrentEnchantItem();
	}

	switch (GetEnchantBotState())
	{
	case EnchantBotState::NOT_IN_LABORATORY:
		if (character_in_laboratory) {
			SetEnchantBotState(EnchantBotState::STANDBY);
		}
		break;
	case EnchantBotState::STANDBY:
	{
		if (m_selectNewEnchantItem)
		{
			INVEN_DISPLAY_INFO* selected = OSR_API->GetSelectedItem();
			if (selected && selected != m_lastSelectedItem && IsValidEnchantItem(selected->pItem)) // weapon and armor are enchantable	
			{
				SetNewEnchantItem(selected->pItem->UniqueNumber);
				m_selectNewEnchantItem = false;
			}
		}
		break;
	}
	case EnchantBotState::ENCHANT_SINGLE: 
		if (m_waiting_for_answer) // maybe rework this into recieved packet code
		{
			CItemInfo* targetitem = OSR_API->FindItemFromTarget(m_currentEnchantItemUID);
			if (targetitem && TryTargetItemToInventory())
			{ 
				// Update item
				m_enchant_item.Update(m_currentEnchantItemUID);
				m_buddy->GetPersistingTools()->PersistEnchantments(m_statisticsWeapon);
				UpdateEnchantItemAmount();
				UpdateTotalCost();
				RebuildCurrentEnchantDisplayList();

				if (!m_auto_enchant) {
					SetEnchantBotState(EnchantBotState::STANDBY);
				}

				if (EnchantFinished())
				{
					m_buddy->NotifySound(NotifyType::Information);
					if (m_buddy->NotificationPopupAllowed())
					{
						std::string msg = "Successfully enchanted to E" + std::to_string(m_wantedEnchantDisplayList.size());
						m_buddy->OpenMessageBoxAsync(msg, GetName(), NotifyType::Warning);
					}
					SetEnchantBotState(EnchantBotState::STANDBY);
				}
				UpdateEnchantStats();
				m_waiting_for_answer = false; 				
			}
		}
		else
		{
			if (m_currentEnchantItemUID == 0 || EnchantFinished()) {
				SetEnchantBotState(EnchantBotState::STANDBY);
			} 

			if (DoEnchantAction(m_next_action)) {
				m_next_action = GetNextAction();  		
			}
		}
		break;
	}	  
}
		
void EnchantBot::RenderImGui()
{
	if (!DrawEnableCheckBox()) {
		//return;
	}	 

	ImGui::NewLine();
	ImGui::BeginDisabledMode(m_state == EnchantBotState::NOT_IN_LABORATORY || !IsEnabled());
	{ 
		ImGui::BeginGroup(); // Weapon Selection
		{
			ImGui::Separator();
			ImGui::Text("Item Selection");
			ImGui::Separator();

			if (ImGui::Button("Select New"))
			{
				ResetCurrentEnchantItem();
				m_selectNewEnchantItem = true;
				SetEnchantBotState(EnchantBotState::STANDBY);
				//ZeroMemory(&m_inventory_enchantcards, sizeof(EnchantCardsAmount));
			}
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Press the \"Select New\" button and then click on an weapon/armor in inventory to select a new enchant item.");
			}
			ImGui::SameLine();
			if (m_selectNewEnchantItem) {
				ImGui::Text("waiting for selection...");
			}
			else if (m_currentEnchantItemUID == 0) {
				ImGui::Text("Select item to start enchanting.");
			}
			else {
				m_enchant_item.RenderImGui();
			}
		}
		ImGui::EndGroup();


		ImGui::NewLine();
		ImGui::BeginColumns("EnchantBotColumns", 2, ImGuiColumnsFlags_NoResize);
		{
			ImGui::SetColumnWidth(0, 540);
			ImGui::BeginChild("EnchantBotCol1", ImVec2(), false);
			{	  
				ImGui::Separator();
				ImGui::Text("Settings");
				ImGui::Separator();

				RenderSettings();
			}
			ImGui::EndChild();
		}
		ImGui::NextColumn();
		{
			int current_idx = 0;
			ImGui::BeginChild("EnchantBotCol2", ImVec2(), false);
			{
				ImGui::Separator();
				ImGui::Text("Current Enchants");
				ImGui::Separator();

				ImGui::NewLine();
				ImGui::PushItemWidth(135);
				ImGui::VectorListBox("##current_enchants", &current_idx, m_currentEnchantDisplayList, 13);
				ImGui::PopItemWidth();
			}
			ImGui::EndChild();
		}
		ImGui::EndColumns();
	}
	ImGui::EndDisabledMode();
}

std::string EnchantBot::GetName() const
{
	return "EnchantBot";
}

void EnchantBot::RenderSuccessPercentage(int enchstep, int total_tries, int fails)
{  	
	float success_ratio = 0.0f;
	if (total_tries != 0 && total_tries != fails) {
		success_ratio = (1 - (float)fails / (float)total_tries) ;
	} 

	float probabiliy = g_Enchant_probabilities[enchstep] / 10000.0f;
	float delta = probabiliy - success_ratio;
	std::string success_percentage_string = Utility::to_string_with_precision<float>(success_ratio * 100, 1) + "%%";

	ImColor color = ImColor(255,255,0,255);
	float color_ratio = std::min(1.0f, fabs(delta) / probabiliy * 10.0f);

	if (delta > 0.03f) // bad -> gradually remove green
	{
		color.Value.y = 1.0f - color_ratio;
	}
	else // good -> gradually remove red
	{
		color.Value.x = 1.0f - color_ratio;
	}

	ImGui::PushStyleColor(ImGuiCol_Text, color.Value);
	ImGui::DrawTextRightAligned(success_percentage_string, ImGui::GetColumnWidth());
	ImGui::PopStyleColor();

	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Success percentage");
	}
}

EnchantBotState EnchantBot::GetEnchantBotState()
{
	return m_state;
}

void EnchantBot::SetEnchantBotState(EnchantBotState state)
{
	m_state = state;
}

void EnchantBot::ResetCurrentEnchantItem()
{
	m_buddy->GetPersistingTools()->PersistEnchantments(m_statisticsWeapon);
	m_buddy->GetPersistingTools()->CloseStream();
	m_currentEnchantItemUID = 0; 
	ResetEnchantList(m_currentEnchantDisplayList);		
}

void EnchantBot::ResetLab()
{
	//OSR_API->OnButtonClick(TO_INT(LabButtonCode::Cancel));
	m_using_chancecard_8 = false;
	m_using_enchprot_e1 = false;
	m_using_enchprot_e5 = false;
	m_using_speedcard = false; 
	m_waiting_for_answer = false;
}

void EnchantBot::UpdateEnchantStats()
{
	int postEnch = m_enchant_item.GetItemInfo()->m_nEnchantNumber;
	if (m_previous_enchantnum >= 5) 
	{
		if (postEnch <= m_previous_enchantnum)
		{
			m_statisticsSession.m_enchantStats[m_previous_enchantnum - 5][0] += 1;
			m_statisticsWeapon.m_enchantStats[m_previous_enchantnum - 5][0] += 1;
			m_statisticsSession.m_enchantStats[m_previous_enchantnum - 5][1] += 1;
			m_statisticsWeapon.m_enchantStats[m_previous_enchantnum - 5][1] += 1;
		}
		else {
			m_statisticsSession.m_enchantStats[m_previous_enchantnum - 5][0] += 1;
			m_statisticsWeapon.m_enchantStats[m_previous_enchantnum - 5][0] += 1;
		}
	}
}

void EnchantBot::UpdateInventoryEnchantCards()
{	   
	GearType geartype = OSR_API->GetPlayerGearType();
	if (m_currentEnchantItemUID != 0) {
		geartype = OSR_API->UnitKindToGearType(m_enchant_item.GetItemInfo()->m_pItemInfo->ReqUnitKind);
	}
	CItemInfo* iteminfo = nullptr;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Accuracy, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.accuracy = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Reattack, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.reattack = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::MinMax, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.damage = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Speed, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.speed = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Range, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.range = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Time, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.time = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Weight, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.weight = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Overheating, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.overheat = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Shield, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.shield = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::Energy, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.energy = (iteminfo) ? iteminfo->CurrentCount : 0;

	iteminfo = GetEnchantItemFromInventory(EnchantCard::EnergyShield, m_enchantTargetKind, geartype);
	m_inventory_enchantcards.energyshield = (iteminfo) ? iteminfo->CurrentCount : 0;   			
}

  
bool EnchantBot::IsValidEnchantItem(ITEM_BASE* enchantItem)
{
	return (IS_WEAPON(enchantItem->Kind) || enchantItem->Kind == ITEMKIND_DEFENSE);
}

void EnchantBot::SetNewEnchantItem(UID64_t uid)
{
	if (uid == 0) {
		return;
	}

	ResetLab();

	m_next_action = EnchantAction::Add_EnchantItem;
	m_enchant_item = OsrItemInfo(uid);


	if (!m_enchant_item.IsArmor() && !m_enchant_item.IsWeapon()) 
	{
		m_currentEnchantItemUID = 0;
		return;
	}  		
	
	m_currentEnchantItemUID = uid;

	m_buddy->GetPersistingTools()->CloseStream();
	m_buddy->GetPersistingTools()->SetItem(uid);
	m_statisticsWeapon = m_buddy->GetPersistingTools()->GetStats();
	UpdateTotalCost();

	auto old_enchanttargetkind = m_enchantTargetKind;

	if (m_enchant_item.IsWeapon())
	{	 
		if (IS_SECONDARY_WEAPON(m_enchant_item.GetItemInfo()->Kind)) {
			m_enchantTargetKind = EnchantItemKind::Weapon_advanced;
		}
		else {
			m_enchantTargetKind = EnchantItemKind::Weapon_standard;
		}

	}
	else {
		m_enchantTargetKind = EnchantItemKind::Armor;
	}

	if (old_enchanttargetkind != m_enchantTargetKind) 
	{
		ResetEnchantList(m_wantedEnchantDisplayList);
	}

	UpdateEnchantItemAmount();
	RebuildCurrentEnchantDisplayList();
}
  
void EnchantBot::RenderSettings()
{	  
	ImGui::BeginColumns("SettingsColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
	{
		ImGui::SetColumnWidth(0, 335);
		ImGui::BeginChild("SettingsCol1");
		{ 

			ImGui::BeginColumns("WantedEnchantsColumns", 2 ,ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
			{
				ImGui::NewLine();
				ImGui::SetColumnWidth(0, 160);
				ImGui::PushItemWidth(150);
				ImGui::VectorListBox("##wanted_enchants", &m_wanted_enchants_sel_idx, m_wantedEnchantDisplayList, 13);
				ImGui::PopItemWidth(); 

				if (ImGui::Button("Reset List", ImVec2(100, 0))) {
					ResetEnchantList(m_wantedEnchantDisplayList);
				}
			}
			ImGui::NextColumn();
			{ 	
				ImGui::BeginChild("EnchantButtons", ImVec2(150, 150));
				{ 	
					ImGui::NewLine();
					ImGui::Text("Add Enchant Cards:");
					ImGui::Separator();
					ImGui::NewLine();
					RenderEnchantButtons();
				}
				ImGui::EndChild();	
				ImGui::NewLine();
				ImGui::BeginChild("EnchantInformation", ImVec2(150,0));
				{
					ImGui::Separator();
					ImGui::Text(m_wantedEnchantDisplayList.at(m_wanted_enchants_sel_idx).c_str());
					ImGui::Separator();

					if (m_wantedEnchantInfo.size() > 0)
					{
						ImGui::BeginDisabledMode(m_wanted_enchants_sel_idx < 5);
						{
							EnchantInformation& selected = m_wantedEnchantInfo.at(m_wanted_enchants_sel_idx);
							const char* chance_items[] = {
								"None",
								"+3%",
								"+5%",
								"+8%",
							};

							int chance_idx = TO_INT(selected.chance);
							if (ImGui::ComboEx("Chance: ", &chance_idx, &chance_items, 4, -1, true, 75.0f))
							{
								selected.chance = TO_ENUM(EnchantChance, chance_idx);
							}

							const char* protect_items[] = {
								"None",
								"E1",
								"E5",
							};

							int protect_idx = TO_INT(selected.protect);
							if (ImGui::ComboEx("Protect:", &protect_idx, &protect_items, 3, -1, true, 75.0f))
							{
								selected.protect = TO_ENUM(EnchantProtect, protect_idx);
								// every change in this setting should set this flag to false
								m_optimiseEnchanting = false;
							}
						}
						ImGui::EndDisabledMode();

						if (ImGui::Button("Remove Enchant")) {
							RemoveEnchantEntry(m_wanted_enchants_sel_idx);
						}
					}
				}
				ImGui::EndChild();	
			}
			ImGui::EndColumns();
		}
		ImGui::EndChild();
	}	
	ImGui::NextColumn();
	{
		ImGui::BeginChild("SettingsCol2");
		{	
			ImGui::BeginChild("EnchantItemsOverview", ImVec2(0, 150));
			{
				ImGui::NewLine();
				ImGui::Text("Enchantitems Overview");
				ImGui::Separator();
				ImGui::BeginColumns("EnchantItemsColumns", 2, ImGuiColumnsFlags_NoResize);
				{
					ImGui::SetColumnWidth(0, 125);
					ImGui::Text("E1 Protect");
					ImGui::Text("E5 Protect");
					ImGui::Text("3%% Chance Card");
					ImGui::Text("5%% Chance Card");
					ImGui::Text("8%% Chance Card");
				}
				ImGui::NextColumn();
				{
					RenderColoredEnchantItemAmount(m_amount_enchprot_e1);
					RenderColoredEnchantItemAmount(m_amount_enchprot_e5);
					RenderColoredEnchantItemAmount(m_amount_chancecard_3);
					RenderColoredEnchantItemAmount(m_amount_chancecard_5);
					RenderColoredEnchantItemAmount(m_amount_chancecard_8);
				}
				ImGui::EndColumns();

				RenderStatisticsPopup();
				if (ImGui::Button("Show Statistics")) {
					ImGui::OpenPopup("StatisticsPopup");
				} 
			}
			ImGui::EndChild();
			ImGui::NewLine();
			ImGui::BeginChild("EnchantControl", ImVec2(0, 0));
			{
				ImGui::Separator();
				ImGui::Text("Control");
				ImGui::Separator();

				if (ImGui::Checkbox("Optimize Protects", &m_optimiseEnchanting))
				{
					SetOptimizedEnchantSettings(m_optimiseEnchanting);
				}
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Automatically set optimized protect card setting.");
				}
				ImGui::Checkbox("Use Chance Cards", &m_withLuckyCard);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Uses the configured Percent Enchant Chance Cards to enchant.");
				}
				ImGui::Checkbox("Auto Enchant", &m_auto_enchant);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Enchants until the target is reached or there are no enchantment items left.");
				}
				if (ImGui::Button("Enchant"))
				{
					if (m_state == EnchantBotState::STANDBY && m_enchant_timer.IsReady()) {
						SetEnchantBotState(EnchantBotState::ENCHANT_SINGLE);
					}
				}
			}
			ImGui::EndChild();
		}
		ImGui::EndChild();
	}
	ImGui::EndColumns();
	
}

void EnchantBot::RenderEnchantButtons()
{ 
	int wantend_enchant_count = m_wantedEnchantDisplayList.size();	  
					   
	if ((m_currentEnchantItemUID != 0 && m_enchantTargetKind != EnchantItemKind::Armor) || m_currentEnchantItemUID == 0)
	{  		
		if (ImGui::Button("Reattack", ImVec2(100, 0)) && wantend_enchant_count < 13) {
			InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::Reattack);
		}
		ImGui::SameLine();
		RenderColoredEnchantItemAmount(m_inventory_enchantcards.reattack);

		if (ImGui::Button("Accuracy", ImVec2(100, 0)) && wantend_enchant_count < 13) {
			InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::Accuracy);
		}
		ImGui::SameLine();
		RenderColoredEnchantItemAmount(m_inventory_enchantcards.accuracy);

		if (ImGui::Button("Attack", ImVec2(100, 0)) && wantend_enchant_count < 13) {
			InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::MinMax);
		}
		ImGui::SameLine();
		RenderColoredEnchantItemAmount(m_inventory_enchantcards.damage);

		if (m_enchantTargetKind == EnchantItemKind::Weapon_advanced)
		{
			if (ImGui::Button("Speed", ImVec2(100, 0)) && wantend_enchant_count < 13) {
				InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::Speed);
			}
			ImGui::SameLine();
			RenderColoredEnchantItemAmount(m_inventory_enchantcards.speed);
		}
		
		/*
		if (ImGui::Button("Weight", ImVec2(100, 20)) && wantend_enchant_count <= 13) {
			InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::Weight);
		}
		ImGui::SameLine();
		RenderColoredEnchantItemAmount(m_inventory_enchantcards.weight);

		if (ImGui::Button("Range", ImVec2(100, 20)) && wantend_enchant_count <= 13) {
			InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::Range);
		}
		ImGui::SameLine();
		RenderColoredEnchantItemAmount(m_inventory_enchantcards.range);

		if (m_enchantTargetKind == EnchantItemKind::Weapon_standard)
		{
			if (ImGui::Button("Time", ImVec2(100, 20)) && wantend_enchant_count <= 13) {
				InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::Time);
			}
			ImGui::SameLine();
			RenderColoredEnchantItemAmount(m_inventory_enchantcards.time);
		}
		*/
	}
	else if ((m_currentEnchantItemUID != 0 && m_enchantTargetKind == EnchantItemKind::Armor))
	{
		if (ImGui::Button("Shield", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::Shield);
		}
		ImGui::SameLine();
		RenderColoredEnchantItemAmount(m_inventory_enchantcards.shield);

		if (ImGui::Button("Energy/Shield", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::EnergyShield);
		}
		ImGui::SameLine();
		RenderColoredEnchantItemAmount(m_inventory_enchantcards.energyshield);

		if (ImGui::Button("Energy", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			InsertEnchantList(m_wantedEnchantDisplayList, EnchantCard::Energy);
		}
		ImGui::SameLine();
		RenderColoredEnchantItemAmount(m_inventory_enchantcards.energy);
	}  	

}

void EnchantBot::RenderColoredEnchantItemAmount(int amount)
{
	if (amount >= 100)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, COLOR_ENCHANTITEM_GT_100);
		ImGui::Text(std::to_string(amount).c_str());
		ImGui::PopStyleColor();

	}
	else if (amount > 0 && amount < 100)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, COLOR_ENCHANTITEM_LT_100);
		ImGui::Text(std::to_string(amount).c_str());
		ImGui::PopStyleColor();
	}
	else if (amount == 0)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, COLOR_ENCHANTITEM_EQ_0);
		ImGui::Text(std::to_string(amount).c_str());
		ImGui::PopStyleColor();
	}
}

void EnchantBot::RenderStatisticsPopup()
{
	ImGui::SetNextWindowSize(ImVec2(550.0f, 390.0f));
	if (ImGui::BeginPopup("StatisticsPopup"/*, &m_popup_statistics_open*/, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar))
	{ 	
		ImGui::BeginMenuBar();
		{
			ImGui::Text("EnchantBot Statistics Popup");
		}
		ImGui::EndMenuBar();

		ImGui::BeginColumns("StatisticsColums", 3, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
		{
			// descriptions
			ImGui::BeginChild("StatisticDescriptionsChild");
			{
				ImGui::Text("Enchants:");
				ImGui::Separator();

				ImGui::BeginGroup();
				{
					ImGui::Text("E5  -> E6:");
					ImGui::Text("E6  -> E7:");
					ImGui::Text("E7  -> E8:");
					ImGui::Text("E8  -> E9:");
					ImGui::Text("E9  -> E10:");
					ImGui::Text("E10 -> E11:");
					ImGui::Text("E11 -> E12:");
				}
				ImGui::EndGroup();

				ImGui::NewLine();

				ImGui::BeginGroup();
				{
					ImGui::Text("Used Items and Cost:");
					ImGui::Separator();

					ImGui::Text("E1 Protects:");
					ImGui::Text("E5 Protects:");
					ImGui::Text("3%% Chance Cards:");
					ImGui::Text("5%% Chance Cards:");
					ImGui::Text("8%% Chance Cards:");
					ImGui::Text("Enchantcards:");
					ImGui::Text("Speedcards:");
					ImGui::Text("Energy/Shield Cards:");

					ImGui::NewLine();
					ImGui::Separator();
					ImGui::Text("Total spi cost:");
					ImGui::Separator();
				}
				ImGui::EndGroup();
			}
			ImGui::EndChild();

			ImGui::NextColumn();
			// session statistics
			ImGui::BeginChild("StatisticSessionChild");
			{
				ImGui::BeginGroup(); // run view
				{
					ImGui::Text("Session");
					ImGui::Separator();

					ImGui::BeginColumns("SessionRunViewColumns", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
					{
						ImGui::SetColumnWidth(0, 90);
						for (int i = 0; i < 7; i++)
						{
							std::string triesfails = Utility::string_format("%u - %u", m_statisticsSession.m_enchantStats[i][0], m_statisticsSession.m_enchantStats[i][0] - m_statisticsSession.m_enchantStats[i][1]);  //std::to_string(m_statisticsSession.m_enchantStats[i][0]) + " - " + std::to_string(m_statisticsSession.m_enchantStats[i][0] - m_statisticsSession.m_enchantStats[i][1]);
							ImGui::Text(triesfails.c_str());
							if (ImGui::IsItemHovered()) {
								ImGui::SetTooltip("total tries - success");
							}
							ImGui::NextColumn();
							RenderSuccessPercentage(i + 5, m_statisticsSession.m_enchantStats[i][0], m_statisticsSession.m_enchantStats[i][1]);
							ImGui::NextColumn();
						}
					}
					ImGui::EndColumns();
				}
				ImGui::EndGroup();
				ImGui::NewLine();
				ImGui::BeginGroup();
				{
					ImGui::NewLine();
					ImGui::Separator();
					ImGui::BeginColumns("SessionCostColumns", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize); 				
					{
						ImGui::SetColumnWidth(0, 90);
						ImGui::Text(std::to_string(m_statisticsSession.m_used_enchprots_e1).c_str());
						ImGui::Text(std::to_string(m_statisticsSession.m_used_enchprots_e5).c_str());
						ImGui::Text(std::to_string(m_statisticsSession.m_used_chancecards_3).c_str());
						ImGui::Text(std::to_string(m_statisticsSession.m_used_chancecards_5).c_str());
						ImGui::Text(std::to_string(m_statisticsSession.m_used_chancecards_8).c_str());
						ImGui::Text(std::to_string(m_statisticsSession.m_used_enchantcards).c_str());
						ImGui::Text(std::to_string(m_statisticsSession.m_used_speedcards).c_str());
						ImGui::Text(std::to_string(m_statisticsSession.m_used_energyshieldcard).c_str());
					}
					ImGui::NextColumn();
					{
						ImGui::DrawTextRightAligned(m_cost_enchprots_e1_string.c_str(), ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_enchprots_e5_string.c_str(), ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_chancecards_3_string.c_str(), ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_chancecards_5_string.c_str(), ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_chancecards_8_string.c_str(), ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_enchantcards_string.c_str(), ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_speedcards_string.c_str(), ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_energyshieldcards_string.c_str(), ImGui::GetColumnWidth());
					}
					ImGui::EndColumns();
					ImGui::NewLine();
					ImGui::Separator();
					//ImGui::Text(m_cost_total_string.c_str());
					ImGui::DrawTextRightAligned(m_cost_total_string);
					ImGui::Separator();
				}
				ImGui::EndGroup();
			}
			ImGui::EndChild();
		}
		ImGui::NextColumn();
		{ 
			ImGui::BeginChild("WeaponStatisticsChild");
			{
				ImGui::BeginGroup(); // run view
				{
					ImGui::Text("This weapon");
					ImGui::Separator();

					ImGui::BeginColumns("WeaponRunViewColumns", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
					{
						ImGui::SetColumnWidth(0, 90);
						for (int i = 0; i < 7; i++)
						{
							std::string triesfails = Utility::string_format("%u - %u", m_statisticsWeapon.m_enchantStats[i][0], m_statisticsWeapon.m_enchantStats[i][0] - m_statisticsWeapon.m_enchantStats[i][1]);//std::to_string(m_statisticsWeapon.m_enchantStats[i][0] - m_statisticsWeapon.m_enchantStats[i][1]) + " - " + std::to_string(m_statisticsWeapon.m_enchantStats[i][0]);
							ImGui::Text(triesfails.c_str());
							if (ImGui::IsItemHovered()) {
								ImGui::SetTooltip("total tries- success");
							}
							ImGui::NextColumn();
							RenderSuccessPercentage(i + 5, m_statisticsWeapon.m_enchantStats[i][0], m_statisticsWeapon.m_enchantStats[i][1]);
							ImGui::NextColumn();
						}
					}
					ImGui::EndColumns();
				}
				ImGui::EndGroup();
				ImGui::NewLine();
				ImGui::BeginGroup();
				{
					ImGui::NewLine();
					ImGui::Separator();
					ImGui::BeginColumns("WeaponCostColumns", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
					{
						ImGui::SetColumnWidth(0, 90);
						ImGui::Text(std::to_string(m_statisticsWeapon.m_used_enchprots_e1).c_str());
						ImGui::Text(std::to_string(m_statisticsWeapon.m_used_enchprots_e5).c_str());
						ImGui::Text(std::to_string(m_statisticsWeapon.m_used_chancecards_3).c_str());
						ImGui::Text(std::to_string(m_statisticsWeapon.m_used_chancecards_5).c_str());
						ImGui::Text(std::to_string(m_statisticsWeapon.m_used_chancecards_8).c_str());
						ImGui::Text(std::to_string(m_statisticsWeapon.m_used_enchantcards).c_str());
						ImGui::Text(std::to_string(m_statisticsWeapon.m_used_speedcards).c_str());
						ImGui::Text(std::to_string(m_statisticsWeapon.m_used_energyshieldcard).c_str());
					}
					ImGui::NextColumn();
					{
						ImGui::DrawTextRightAligned(m_cost_enchprots_e1_string_W.c_str(),		ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_enchprots_e5_string_W.c_str(),		ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_chancecards_3_string_W.c_str(),		ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_chancecards_5_string_W.c_str(),		ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_chancecards_8_string_W.c_str(),		ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_enchantcards_string_W.c_str(),		ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_speedcards_string_W.c_str(),			ImGui::GetColumnWidth());
						ImGui::DrawTextRightAligned(m_cost_energyshieldcards_string_W.c_str(),	ImGui::GetColumnWidth());
					}
					ImGui::EndColumns();
					ImGui::NewLine();
					ImGui::Separator();
					//ImGui::Text("Total spi cost:");
					//ImGui::SameLine();
					ImGui::DrawTextRightAligned(m_cost_total_string_W);
					//ImGui::Text(m_cost_total_string_W.c_str());
					ImGui::Separator();
				}
				ImGui::EndGroup();
			}
			ImGui::EndChild();
		}
		ImGui::EndColumns();
		ImGui::EndPopup();
	}
}


void EnchantBot::ResetEnchantList(ListVector& enchantlist)
{
	enchantlist.clear();
	InsertEnchantList(enchantlist, EnchantCard::None);	// dummy enchant
	if (&enchantlist == &m_wantedEnchantDisplayList) 
	{
		m_wanted_enchants_sel_idx = 0;
		m_wantedEnchantInfo.clear();
		m_wantedEnchantInfo.push_back(EnchantInformation());
	}
}
	
void EnchantBot::InsertEnchantList(ListVector& enchantlist, EnchantCard enchanttype)
{
	// remove dummy entrys if we are adding the first enchant
	if (enchantlist.size() == 1 && enchantlist[0] == GetEnchantItemText(EnchantCard::None)) 
	{
		enchantlist.clear();

		if (&enchantlist == &m_wantedEnchantDisplayList)
		{
			m_wantedEnchantInfo.clear();
		}		
	}
			
	size_t enchantnum = enchantlist.size() + 1;  
	/*
	std::string enchantstr = "E:" + std::to_string(enchantnum);
	if (enchantnum < 10) {
		enchantstr += " ";
	}
	*/

	std::string itemtext;
	if (enchanttype == EnchantCard::None)
	{
		itemtext = GetEnchantItemText(EnchantCard::None);
	}
	else
	{
		itemtext = Utility::string_format("E:%-2zu %s", enchantnum, GetEnchantItemText(enchanttype).c_str());
	}
	
	enchantlist.push_back(itemtext);

	if (&enchantlist == &m_wantedEnchantDisplayList)
	{
		/*
		EnchantListType::iterator it = enchantlist.begin() + index;
		enchantlist.insert(it + 1, itemtext);

		if (it != enchantlist.end() - 1)
		{
			// update texts	when the insertion was not at the end
			int enchantnum = 1;
			for (auto& enchantlistitem : enchantlist)
			{
				std::string enchantstr = "E:" + std::to_string(enchantnum);
				if (enchantnum < 10) {
					enchantstr += " ";
				}
				enchantlistitem.replace(0, 4, enchantstr);
				enchantnum++;
			}
		}
		*/

		// insert also in additional info vector
		EnchantInformation enchantinfo = EnchantInformation();
		enchantinfo.enchant = enchanttype;
		if (enchantnum > 5)
		{
			if (m_optimiseEnchanting && enchantnum <= 7) 
			{
				enchantinfo.protect = EnchantProtect::E1;
			}
			else
			{
				enchantinfo.protect = EnchantProtect::E5;
			}
		}
		m_wantedEnchantInfo.push_back(enchantinfo);
		if (m_wantedEnchantInfo.size() > 1)
		{
			m_wanted_enchants_sel_idx++;
		}
	}
}

void EnchantBot::RemoveEnchantEntry(uint32_t enchantindex)
{
	if (enchantindex >= m_wantedEnchantInfo.size())
	{
		return;
	}

	if (enchantindex == 0 && m_wantedEnchantInfo.size() == 1)
	{
		ResetEnchantList(m_wantedEnchantDisplayList);
		return;
	}

	auto it = m_wantedEnchantInfo.erase(m_wantedEnchantInfo.begin() + enchantindex);
	SetOptimizedEnchantSettings(m_optimiseEnchanting);
	
	if (it == m_wantedEnchantInfo.end())
	{
		m_wantedEnchantDisplayList.erase(m_wantedEnchantDisplayList.end() - 1); // remove last entry
		if (enchantindex == m_wanted_enchants_sel_idx)
		{
			// selection now points to an invalid entry -> set it to last entry in list
			m_wanted_enchants_sel_idx = m_wantedEnchantInfo.size() - 1;
		}
	}
	else
	{
		// easiest way at this point is to rebuild the complete list
		RebuildWantedEnchantDisplayList();
	}
}

void EnchantBot::RebuildWantedEnchantDisplayList()
{
	m_wantedEnchantDisplayList.clear();
	uint32_t enchantnum = 1;
	for (auto& enchinfo : m_wantedEnchantInfo)
	{
		std::string itemtext;
		if (enchinfo.enchant == EnchantCard::None)
		{
			itemtext = GetEnchantItemText(EnchantCard::None);
		}
		else
		{
			itemtext = Utility::string_format("E:%-2zu %s", enchantnum, GetEnchantItemText(enchinfo.enchant).c_str());
		}
		m_wantedEnchantDisplayList.push_back(itemtext);
		enchantnum++;
	}
}

void EnchantBot::RebuildCurrentEnchantDisplayList()
{
	if (m_currentEnchantItemUID == 0)
	{
		return;
	}

	ResetEnchantList(m_currentEnchantDisplayList);
	for (auto enchant : m_enchant_item.GetItemInfo()->m_vecDefEnchant)
	{
		switch (m_enchantTargetKind)
		{
		case EnchantItemKind::Weapon_advanced:
		case EnchantItemKind::Weapon_standard:

			switch (enchant.m_nDesParam)
			{
			case static_cast<BYTE>(Desparam::AdvancedAccuracy) :
			case static_cast<BYTE>(Desparam::StandardAccuracy) :
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Accuracy);
				break;
			case static_cast<BYTE>(Desparam::AdvancedQuickFire) :
			case static_cast<BYTE>(Desparam::StandardQuickFire) :
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Reattack);
				break;
			case static_cast<BYTE>(Desparam::AdvancedAttack) :
			case static_cast<BYTE>(Desparam::StandardAttack) :
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::MinMax);
				break;
			case static_cast<BYTE>(Desparam::StandardOverheating) :
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Overheating);
				break;
			case static_cast<BYTE>(Desparam::AdvancedRange) :
			case static_cast<BYTE>(Desparam::StandardRange) :
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Range);
				break;
			case static_cast<BYTE>(Desparam::AdvancedTime) :
			case static_cast<BYTE>(Desparam::StandardTime) :
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Time);
				break;
			case static_cast<BYTE>(Desparam::StandardWeight) :
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Weight);
				break;
			case static_cast<BYTE>(Desparam::AdvancedSpeed) :
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Speed);
				break;
			default:
				continue;
				break;
			}
			break;
		case EnchantItemKind::Armor:
			switch (enchant.m_nDesParam)
			{
			case static_cast<BYTE>(Desparam::Shield) :
				if (enchant.m_fDesValue == 100.0f)
				{
					// energyshield card
					break;
				}
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Shield);
				break;
			case static_cast<BYTE>(Desparam::Energy) :
				if (enchant.m_fDesValue == 100.0f)
				{
					// energyshield card
					InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::EnergyShield);
					break;
				}
				InsertEnchantList(m_currentEnchantDisplayList, EnchantCard::Energy);
				break;
			default:
				continue;
				break;
			}
			break;
		default:
			continue;
			break;
		}
	}
}

bool EnchantBot::DoEnchantAction(EnchantAction action)
{
	if (!m_action_timer.IsReady()) {
		return false;
	}
	else {
		m_action_timer.Reset();
	}

	if (m_currentEnchantItemUID == 0) {
		return false;
	}

	if (m_wantedEnchantDisplayList.size() <= m_enchant_item.GetItemInfo()->m_nEnchantNumber) { // should never happen at this place, but you never know xD
		return false;
	}
		   
	CItemInfo* enchantitem = nullptr;

	// move items to source, step by step
	switch (action)
	{
	case EnchantAction::Add_EnchantItem:
		{
			// Enchanting should have a minimum time between each complete enchants, independetly from the time between the single enchant actions
			if (!m_enchant_timer.IsReady()) {
				return false;
			}
			m_enchant_timer.Reset();
			// first item will be the item to be enchanted
			enchantitem = m_enchant_item.GetItemInfo();
		}
		break;

	case EnchantAction::Add_EnchantCard:
		{
			/*
			if (m_wantedEnchantInfo.at(m_enchant_item.GetItemInfo()->m_nEnchantNumber).enchant == EnchantCard::Speed) {
				m_using_speedcard = true;
			}
			if (m_wantedEnchantInfo.at(m_enchant_item.GetItemInfo()->m_nEnchantNumber).enchant == EnchantCard::EnergyShield) {
				m_using_energyshieldcard = true;
			}
			*/
			GearType geartype = OSR_API->UnitKindToGearType(m_enchant_item.GetItemInfo()->m_pItemInfo->ReqUnitKind);
			enchantitem = GetEnchantItemFromInventory(m_wantedEnchantInfo.at(m_enchant_item.GetItemInfo()->m_nEnchantNumber).enchant, m_enchantTargetKind, geartype);
		}
		break;
	case EnchantAction::Add_ProtectCard:
		{
			auto protectcard = m_wantedEnchantInfo.at(m_enchant_item.GetItemInfo()->m_nEnchantNumber).protect;
			if (protectcard != EnchantProtect::None)
			{
				enchantitem = GetEnchantItemFromInventory(m_wantedEnchantInfo.at(m_enchant_item.GetItemInfo()->m_nEnchantNumber).protect);
			}
			else
			{
				return true;
			}
		}
		/*
		if (m_enchant_item.GetItemInfo()->m_nEnchantNumber < 5) { // no need to add an enchant protect card
			return true;
		}

		if (m_optimiseEnchanting)
		{
			if (m_enchant_item.GetItemInfo()->m_nEnchantNumber == 5 || m_enchant_item.GetItemInfo()->m_nEnchantNumber == 6)
			{
				enchantitem = GetEnchantItemFromInventory(EnchantItemType::EnchantProtectE1, m_enchantTargetKind, geartype);
				if (enchantitem) {
					m_using_enchprot_e1 = true;
				}
			}
			else
			{
				enchantitem = GetEnchantItemFromInventory(EnchantItemType::EnchantProtectE5, m_enchantTargetKind, geartype);
				m_using_enchprot_e5 = true;
			}
		}
		else
		{
			enchantitem = GetEnchantItemFromInventory(EnchantItemType::EnchantProtectE5, m_enchantTargetKind, geartype);
			m_using_enchprot_e5 = true;
		}
		*/
		break;
	case EnchantAction::Add_PercentageCard: // next and optional item is an enchant chance card
		{
			auto chancecard = m_wantedEnchantInfo.at(m_enchant_item.GetItemInfo()->m_nEnchantNumber).chance;
			if (chancecard != EnchantChance::None)
			{
				enchantitem = GetEnchantItemFromInventory(m_wantedEnchantInfo.at(m_enchant_item.GetItemInfo()->m_nEnchantNumber).chance);
			}
			else
			{
				return true;
			}
		}
		/*
		if (m_enchant_item.GetItemInfo()->m_nEnchantNumber == 10)
		{
			enchantitem = GetEnchantItemFromInventory(EnchantItemType::EnchantChance8P, m_enchantTargetKind, geartype);
			m_using_chancecard_8 = true;
		}
		else {
			return true;
		}
		*/
		break;
	case EnchantAction::Use_OkButton: 
		{
			m_previous_enchantnum = m_enchant_item.GetItemInfo()->m_nEnchantNumber;
			OSR_API->OnButtonClick(TO_INT(LabButtonCode::Send));
			m_waiting_for_answer = true;

			auto prevEnchantInfo = m_wantedEnchantInfo.at(m_previous_enchantnum);
			AddLastEnchantToStatistic(prevEnchantInfo);

			/*
			if (m_using_chancecard_8) 
			{
				m_statisticsSession.m_used_chancecards_8++;
				m_statisticsWeapon.m_used_chancecards_8++;
			}

			if (m_using_enchprot_e1) 
			{
				m_statisticsSession.m_used_enchprots_e1++;
				m_statisticsWeapon.m_used_enchprots_e1++;
			}

			if (m_using_enchprot_e5)
			{
				m_statisticsSession.m_used_enchprots_e5++;
				m_statisticsWeapon.m_used_enchprots_e5++;
			}

			if (m_using_speedcard) 
			{
				m_statisticsSession.m_used_speedcards++;
				m_statisticsWeapon.m_used_speedcards++;
			}
			else if (m_using_energyshieldcard)
			{
				m_statisticsSession.m_used_energyshieldcard++;
				m_statisticsWeapon.m_used_energyshieldcard++;
			} 		
			else
			{
				m_statisticsSession.m_used_enchantcards++;
				m_statisticsWeapon.m_used_enchantcards++;
			}
			m_buddy->GetPersistingTools()->PersistEnchantments(m_statisticsWeapon);
			m_using_chancecard_8 = false;
			m_using_enchprot_e1 = false;
			m_using_enchprot_e5 = false;
			m_using_speedcard = false;

			UpdateTotalCost();	
			*/
			return true;
		}
	}

	if (enchantitem) 
	{
		//  finally move the item to the source fields
		OSR_API->InvenToSourceItem(enchantitem, 1, false); 
		if (action == EnchantAction::Add_EnchantItem) {
			m_enchant_item.UpdateItemInfo();
		}
		return true;
	}
	else
	{			
		//enchant item not found	 		
		m_buddy->NotifySound(NotifyType::Information);
		if (m_buddy->NotificationPopupAllowed())
		{											
			std::string msg;
			switch (action)
			{
			case EnchantAction::Add_EnchantItem:
				msg = "Missing Enchantitem!";
				break;
			case EnchantAction::Add_EnchantCard:
				msg = "Missing Enchantcard!";
				break;
			case EnchantAction::Add_ProtectCard:
				msg = "Missing Protectcard!";
				break;
			case EnchantAction::Add_PercentageCard:
				msg = "Missing Chancecard!";
				break;		
			}  
			m_buddy->OpenMessageBoxAsync(msg, GetName(), NotifyType::Warning);
		}
		
		SetEnchantBotState(EnchantBotState::STANDBY);
		ResetLab();
		
		return false;
	}  	
}

CItemInfo* EnchantBot::GetEnchantItemFromInventory(EnchantCard enchantitem, EnchantItemKind itemkind, GearType geartype)
{
	switch (itemkind)
	{
	case EnchantItemKind::Armor: 		
		switch (enchantitem)
		{
		case EnchantCard::Shield:
			switch (geartype)
			{
			case GearType::IGear:
				return OSR_API->FindItemInInventoryByItemNum(ItemNumber::IGearShieldCard);
			case GearType::BGear:
				return OSR_API->FindItemInInventoryByItemNum(ItemNumber::BGearShieldCard);
			case GearType::MGear:
				return OSR_API->FindItemInInventoryByItemNum(ItemNumber::MGearShieldCard);
			case GearType::AGear:
				return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AGearShieldCard);
			default:
				return nullptr;
			}
		case EnchantCard::Energy:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnergyCard);
		case EnchantCard::EnergyShield:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnergyShieldCard);
		default:
			return nullptr;
		}
	case EnchantItemKind::Weapon_advanced:
		switch (enchantitem)
		{
		case EnchantCard::Accuracy:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedProbabilityCard);
		case EnchantCard::Reattack:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedQuickFireCard);
		case EnchantCard::MinMax:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedAttackCard);
		case EnchantCard::Speed:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedSpeedCard);
		case EnchantCard::Range:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedRangeCard);
		case EnchantCard::Weight:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedWeightCard);
		default:
			return nullptr;
		}
	case EnchantItemKind::Weapon_standard:
		switch (enchantitem)
		{
		case EnchantCard::Accuracy:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardProbabilityCard);
		case EnchantCard::Reattack:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardQuickFireCard);
		case EnchantCard::MinMax:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardAttackCard);
		case EnchantCard::Overheating:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardOverheatingCard);
		case EnchantCard::Range:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardRangeCard);
		case EnchantCard::Time:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardTimeCard);
		case EnchantCard::Weight:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardWeightCard);
		default:
			return nullptr;
		}
	default:
		return nullptr;
	}
}

CItemInfo* EnchantBot::GetEnchantItemFromInventory(EnchantProtect enchantitem)
{
	switch (enchantitem)
	{
	case EnchantProtect::None:
		return nullptr;
	case EnchantProtect::E1:
		return OSR_API->FindItemInInventoryByItemNum(ItemNumber::BasicItemProtectCard);
	case EnchantProtect::E5:
	{
		auto item = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantItemProtectCard);
		if (!item) {
			item = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantItemProtectCard2);
		}
		return item;
	}
	default:
		return nullptr;
	}
}

CItemInfo* EnchantBot::GetEnchantItemFromInventory(EnchantChance enchantitem)
{
	switch (enchantitem)
	{
	case EnchantChance::None:
		return nullptr;
	case EnchantChance::Percent_3:
		return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance3PercentCard);
	case EnchantChance::Percent_5:
		return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance5PercentCard);
	case EnchantChance::Percent_8:
		return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance8PercentCard);
	default:
		return nullptr;
	}
}

void EnchantBot::UpdateEnchantItemAmount()
{
	CItemInfo* chancecard_8 = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance8PercentCard);
	m_amount_chancecard_8 = (chancecard_8) ? chancecard_8->CurrentCount : 0;

	CItemInfo* chancecard_5 = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance5PercentCard);
	m_amount_chancecard_5 = (chancecard_5) ? chancecard_5->CurrentCount : 0;

	CItemInfo* chancecard_3 = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance3PercentCard);
	m_amount_chancecard_3 = (chancecard_3) ? chancecard_3->CurrentCount : 0;

	int amount_e5_prot = 0;
	CItemInfo* e5_enchprot = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantItemProtectCard);
	if (e5_enchprot) {
		amount_e5_prot += e5_enchprot->CurrentCount;
	}
	e5_enchprot = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantItemProtectCard2);
	if (e5_enchprot) {
		amount_e5_prot += e5_enchprot->CurrentCount;
	} 
	m_amount_enchprot_e5 = amount_e5_prot;

	CItemInfo* e1_enchprot = OSR_API->FindItemInInventoryByItemNum(ItemNumber::BasicItemProtectCard);
	m_amount_enchprot_e1 = (e1_enchprot) ? e1_enchprot->CurrentCount : 0;

	UpdateInventoryEnchantCards();
}

void EnchantBot::UpdateTotalCost()
{
	m_statisticsSession.m_cost_enchprots_e1		= m_statisticsSession.m_used_enchprots_e1 * COST_ENCHANTPROTECT_E1;
	m_statisticsSession.m_cost_enchprots_e5		= m_statisticsSession.m_used_enchprots_e5 * COST_ENCHANTPROTECT_E5;
	m_statisticsSession.m_cost_chancecards_3	= m_statisticsSession.m_used_chancecards_3 * COST_ENCHANT_CHANCE_3;
	m_statisticsSession.m_cost_chancecards_5	= m_statisticsSession.m_used_chancecards_5 * COST_ENCHANT_CHANCE_5;
	m_statisticsSession.m_cost_chancecards_8	= m_statisticsSession.m_used_chancecards_8 * COST_ENCHANT_CHANCE_8;
	m_statisticsSession.m_cost_enchantcards		= m_statisticsSession.m_used_enchantcards * COST_ENCHANTCARD_COMMON;
	m_statisticsSession.m_cost_speedcards		= m_statisticsSession.m_used_speedcards * COST_ENCHANTCARD_SPEED;
	m_statisticsSession.m_cost_energyshieldcard = m_statisticsSession.m_used_energyshieldcard * COST_ENCHANTCARD_ENERGYSHIELD;

	m_statisticsSession.m_cost_total = 
		m_statisticsSession.m_cost_enchprots_e1 + m_statisticsSession.m_cost_enchprots_e5 +
		m_statisticsSession.m_cost_chancecards_3 + m_statisticsSession.m_cost_chancecards_5 + m_statisticsSession.m_cost_chancecards_8 + 
		m_statisticsSession.m_cost_enchantcards + m_statisticsSession.m_cost_speedcards + m_statisticsSession.m_cost_energyshieldcard +
		(m_statisticsSession.m_used_speedcards + m_statisticsSession.m_used_enchantcards + m_statisticsSession.m_used_energyshieldcard) * COST_ENCHANT_SINGLE;
																													   
	m_cost_enchprots_e1_string		= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_enchprots_e1 / 1000000.0f, 1) + "kk";
	m_cost_enchprots_e5_string		= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_enchprots_e5 / 1000000.0f, 1) + "kk";
	m_cost_chancecards_3_string		= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_chancecards_3 / 1000000.0f, 1) + "kk";
	m_cost_chancecards_5_string		= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_chancecards_5 / 1000000.0f, 1) + "kk";
	m_cost_chancecards_8_string		= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_chancecards_8 / 1000000.0f, 1) + "kk";
	m_cost_enchantcards_string		= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_enchantcards / 1000000.0f, 1) + "kk";
	m_cost_speedcards_string		= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_speedcards / 1000000.0f, 1) + "kk";
	m_cost_energyshieldcards_string	= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_energyshieldcard / 1000000.0f, 1) + "kk";
	m_cost_total_string				= Utility::to_string_with_precision<float>(m_statisticsSession.m_cost_total / 1000000.0f, 1) + "kk";

	m_statisticsWeapon.m_cost_enchprots_e1		= m_statisticsWeapon.m_used_enchprots_e1 * COST_ENCHANTPROTECT_E1;
	m_statisticsWeapon.m_cost_enchprots_e5		= m_statisticsWeapon.m_used_enchprots_e5 * COST_ENCHANTPROTECT_E5;
	m_statisticsWeapon.m_cost_chancecards_3		= m_statisticsWeapon.m_used_chancecards_3 * COST_ENCHANT_CHANCE_3;
	m_statisticsWeapon.m_cost_chancecards_5		= m_statisticsWeapon.m_used_chancecards_5 * COST_ENCHANT_CHANCE_5;
	m_statisticsWeapon.m_cost_chancecards_8		= m_statisticsWeapon.m_used_chancecards_8 * COST_ENCHANT_CHANCE_8;
	m_statisticsWeapon.m_cost_enchantcards		= m_statisticsWeapon.m_used_enchantcards * COST_ENCHANTCARD_COMMON;
	m_statisticsWeapon.m_cost_speedcards		= m_statisticsWeapon.m_used_speedcards * COST_ENCHANTCARD_SPEED;
	m_statisticsWeapon.m_cost_energyshieldcard	= m_statisticsWeapon.m_used_energyshieldcard * COST_ENCHANTCARD_ENERGYSHIELD;

	m_statisticsWeapon.m_cost_total = 
		m_statisticsWeapon.m_cost_enchprots_e1 + m_statisticsWeapon.m_cost_enchprots_e5 +
		m_statisticsWeapon.m_cost_chancecards_3 + m_statisticsWeapon.m_cost_chancecards_5 + m_statisticsWeapon.m_cost_chancecards_8 + 
		m_statisticsWeapon.m_cost_enchantcards + m_statisticsWeapon.m_cost_speedcards + m_statisticsWeapon.m_cost_energyshieldcard +
		(m_statisticsWeapon.m_used_speedcards + m_statisticsWeapon.m_used_enchantcards + m_statisticsWeapon.m_used_energyshieldcard) * COST_ENCHANT_SINGLE;

	m_cost_enchprots_e1_string_W		= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_enchprots_e1 / 1000000.0f, 1) + "kk";
	m_cost_enchprots_e5_string_W		= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_enchprots_e5 / 1000000.0f, 1) + "kk";
	m_cost_chancecards_3_string_W		= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_chancecards_3 / 1000000.0f, 1) + "kk";
	m_cost_chancecards_5_string_W		= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_chancecards_5 / 1000000.0f, 1) + "kk";
	m_cost_chancecards_8_string_W		= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_chancecards_8 / 1000000.0f, 1) + "kk";
	m_cost_enchantcards_string_W		= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_enchantcards / 1000000.0f, 1) + "kk";
	m_cost_speedcards_string_W			= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_speedcards / 1000000.0f, 1) + "kk";
	m_cost_energyshieldcards_string_W	= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_energyshieldcard / 1000000.0f, 1) + "kk";
	m_cost_total_string_W				= Utility::to_string_with_precision<float>(m_statisticsWeapon.m_cost_total / 1000000.0f, 1) + "kk";
}

bool EnchantBot::TrySimulateButtonClick(LabButtonCode button)
{
	if (m_action_timer.IsReady())
	{
		OSR_API->OnButtonClick(TO_INT(button));
		m_action_timer.Reset();
		return true;
	}
	else {
		return false;
	}
}

bool EnchantBot::TryTargetItemToInventory()
{
	// wait until we could simulate the button to transfer the results into the inventory
	if (!TrySimulateButtonClick(LabButtonCode::Ok)) {
		return false;
	}

	// item should be in inventory now, set the current enchant item again					
	//SetEnchantItem(m_currentEnchantItemUID);
	m_next_action = EnchantAction::Add_EnchantItem;
	return true;
}

bool EnchantBot::EnchantFinished()
{
	// check if all the wanted enchants are more or equal to the current enchants
	return TO_INT(m_enchant_item.GetItemInfo()->m_nEnchantNumber) >= m_wantedEnchantDisplayList.size();
}

EnchantAction EnchantBot::GetNextAction()
{
	EnchantAction last_action = m_next_action;
	EnchantAction next_action;
	while (true)
	{
		switch (last_action)
		{
		case EnchantAction::Add_EnchantItem:   			
			return EnchantAction::Add_EnchantCard;
		case EnchantAction::Add_EnchantCard:
			if (m_enchant_item.GetItemInfo()->m_nEnchantNumber < 5) {// no need to add an enchant protect card 		
				last_action = EnchantAction::Add_ProtectCard;
			}
			else {
				return EnchantAction::Add_ProtectCard;
			}  			
			break;
		case EnchantAction::Add_ProtectCard:
			if (m_withLuckyCard) {
				return EnchantAction::Add_PercentageCard;
			}			
			last_action = EnchantAction::Add_PercentageCard;
			break;
		case EnchantAction::Add_PercentageCard:
			return EnchantAction::Use_OkButton;
		case EnchantAction::Use_OkButton:						 
			// reset to start 
			return EnchantAction::Add_EnchantItem;		
		}
	}			
}
void EnchantBot::AddLastEnchantToStatistic(const EnchantInformation& enchantinfo)
{
	switch (enchantinfo.chance)
	{
	case EnchantChance::None:
		break;
	case EnchantChance::Percent_3:
		m_statisticsSession.m_used_chancecards_3++;
		m_statisticsWeapon.m_used_chancecards_3++;
		break;
	case EnchantChance::Percent_5:
		m_statisticsSession.m_used_chancecards_5++;
		m_statisticsWeapon.m_used_chancecards_5++;
		break;
	case EnchantChance::Percent_8:
		m_statisticsSession.m_used_chancecards_8++;
		m_statisticsWeapon.m_used_chancecards_8++;
		break;
	default:
		break;
	}

	switch (enchantinfo.protect)
	{
	case EnchantProtect::None:
		break;
	case EnchantProtect::E1:
		m_statisticsSession.m_used_enchprots_e1++;
		m_statisticsWeapon.m_used_enchprots_e1++;
		break;
	case EnchantProtect::E5:
		m_statisticsSession.m_used_enchprots_e5++;
		m_statisticsWeapon.m_used_enchprots_e5++;
		break;
	default:
		break;
	}
	
	switch (enchantinfo.enchant)
	{
	case EnchantCard::None:
		std::exception("EnchantBot Error");
		break;
	case EnchantCard::Speed:
		m_statisticsSession.m_used_speedcards++;
		m_statisticsWeapon.m_used_speedcards++;
		break;
	case EnchantCard::EnergyShield:
		m_statisticsSession.m_used_energyshieldcard++;
		m_statisticsWeapon.m_used_energyshieldcard++;	  
		break;
	default:
		m_statisticsSession.m_used_enchantcards++;
		m_statisticsWeapon.m_used_enchantcards++;
		break;
	}

	m_buddy->GetPersistingTools()->PersistEnchantments(m_statisticsWeapon);
	UpdateTotalCost();
}

std::string EnchantBot::GetEnchantItemText(EnchantCard enchantcard)
{
	switch (enchantcard)
	{
	case EnchantCard::Accuracy:
		return "Accuracy";
	case EnchantCard::Reattack:
		return "Reattack";
	case EnchantCard::MinMax:
		return "Min/Max";
	case EnchantCard::Speed:
		return "Speed";
	case EnchantCard::Overheating:
		return "Overheat";
	case EnchantCard::Range:
		return "Range";
	case EnchantCard::Time:
		return "Time";
	case EnchantCard::Weight:
		return "Weight";
	case EnchantCard::Shield:
		return "Shield";
	case EnchantCard::Energy:
		return "Energy";
	case EnchantCard::EnergyShield:
		return "Energy/Shield";
	case EnchantCard::None:
		return "None";
	default:
		return "Error";
	}
}

std::string EnchantBot::GetEnchantItemText(EnchantChance enchantchance)
{
	switch (enchantchance)
	{
	case EnchantChance::None:
		return "None";
	case EnchantChance::Percent_3:
		return "Enchant Chance +3% Card";
	case EnchantChance::Percent_5:
		return "Enchant Chance +5% Card";
	case EnchantChance::Percent_8:
		return "Enchant Chance +8% Card";
	default:						
		return "Error";
	}
}

std::string EnchantBot::GetEnchantItemText(EnchantProtect enchantprotect)
{
	switch (enchantprotect)
	{
	case EnchantProtect::None:
		return "None";
	case EnchantProtect::E1:
		return "Basic Item Protect Card";
	case EnchantProtect::E5:
		return "Enchant Item Protect Car";
	default:
		return "Error";
	}
}

void EnchantBot::SetOptimizedEnchantSettings(bool optimized)
{
	for (uint32_t index = 0; index < m_wantedEnchantInfo.size(); index++)
	{
		if (index < 5)
		{
			m_wantedEnchantInfo[index].protect = EnchantProtect::None;
		}
		else if (index < 7 && optimized)
		{
			m_wantedEnchantInfo[index].protect = EnchantProtect::E1;
		}
		else
		{
			m_wantedEnchantInfo[index].protect = EnchantProtect::E5;
		}
	}
}

FeatureType EnchantBot::GetType() const
{
	return FeatureType::EnchantBot;
}

void EnchantBot::OnEnable()
{
	UpdateEnchantItemAmount();
	const BuddyFeatureBase* gambleBot = m_buddy->GetFeatureByType(FeatureType::GambleBot);
	if (gambleBot && gambleBot->IsEnabled())
	{
		MessageBeep(MB_ICONWARNING);
		Enable(false);
	}
}
void EnchantBot::OnDisable()
{
	m_buddy->GetPersistingTools()->CloseStream();
}
