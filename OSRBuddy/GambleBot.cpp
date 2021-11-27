#include "osrb_pch.h"
#include "GambleBot.h"

#include "SDK/AtumApplication.h"
#include "OSRBuddy.h"
#include "OSRAPI.h"
#include "OSRBuddyDefine.h"
#include "OSRImGuiMenu.h" 
#include "Utility.h"

#include "PersistingTools.h"


#include <algorithm> // std::find

namespace Features
{
	// pierce
	std::vector<AdvancedPrefix> GoodAdvanced_Pierce_PrefixList = { AdvancedPrefix::Bandit, AdvancedPrefix::Traitor, AdvancedPrefix::Archrival, AdvancedPrefix::Adversary, AdvancedPrefix::Bane, AdvancedPrefix::Challenger, AdvancedPrefix::Stronghold };
	std::vector<AdvancedPrefix> BestAdvanced_Pierce_PrefixList = { AdvancedPrefix::Bandit, AdvancedPrefix::Traitor};
	std::vector<StandardPrefix> GoodStandard_Pierce_PrefixList = { StandardPrefix::Bandit, StandardPrefix::Traitor, StandardPrefix::Archrival, StandardPrefix::Adversary, StandardPrefix::Bane, StandardPrefix::Challenger_1, StandardPrefix::Challenger_2, StandardPrefix::Stronghold };
	std::vector<StandardPrefix> BestStandard_Pierce_PrefixList = { StandardPrefix::Bandit, StandardPrefix::Traitor };

	// reattack prob
	std::vector<AdvancedPrefix> GoodAdvanced_ProbReattack_PrefixList = { AdvancedPrefix::Legend, AdvancedPrefix::Bio, AdvancedPrefix::Meteo, AdvancedPrefix::Silence, AdvancedPrefix::Attack };
	std::vector<AdvancedPrefix> BestAdvanced_ProbReattack_PrefixList = { AdvancedPrefix::Legend, AdvancedPrefix::Bio };
	std::vector<StandardPrefix> GoodStandard_ProbReattack_PrefixList = { StandardPrefix::Legend, StandardPrefix::Bio, StandardPrefix::Meteo, StandardPrefix::Silence, StandardPrefix::Attack };
	std::vector<StandardPrefix> BestStandard_ProbReattack_PrefixList = { StandardPrefix::Legend, StandardPrefix::Bio };

	std::vector<AdvancedSuffix> GoodAdvanced_ProbReattack_SuffixList = { AdvancedSuffix::Legend, AdvancedSuffix::Bio, AdvancedSuffix::Meteo, AdvancedSuffix::Silence, AdvancedSuffix::Attack };
	std::vector<AdvancedSuffix> BestAdvanced_ProbReattack_SuffixList = { AdvancedSuffix::Legend, AdvancedSuffix::Bio };
	std::vector<StandardSuffix> GoodStandard_ProbReattack_SuffixList = { StandardSuffix::Legend, StandardSuffix::Bio, StandardSuffix::Meteo, StandardSuffix::Silence, StandardSuffix::Attack };
	std::vector<StandardSuffix> BestStandard_ProbReattack_SuffixList = { StandardSuffix::Legend, StandardSuffix::Bio };

	// minmax prob
	std::vector<AdvancedPrefix> GoodAdvanced_ProbDamage_PrefixList = { AdvancedPrefix::Navas, AdvancedPrefix::Agareth, AdvancedPrefix::Asmodi, AdvancedPrefix::Kobal, AdvancedPrefix::Warrior, AdvancedPrefix::Hound, AdvancedPrefix::Proson, AdvancedPrefix::Aloken, AdvancedPrefix::Tobit, AdvancedPrefix::Neopyte};
	std::vector<AdvancedPrefix> BestAdvanced_ProbDamage_PrefixList = { AdvancedPrefix::Navas, AdvancedPrefix::Agareth, AdvancedPrefix::Asmodi, AdvancedPrefix::Kobal, AdvancedPrefix::Warrior, };
	std::vector<StandardPrefix> GoodStandard_ProbDamage_PrefixList = { StandardPrefix::Navas, StandardPrefix::Agareth, StandardPrefix::Asmodi, StandardPrefix::Kobal, StandardPrefix::Warrior, StandardPrefix::Hound, StandardPrefix::Proson, StandardPrefix::Aloken, StandardPrefix::Tobit, StandardPrefix::Neopyte };
	std::vector<StandardPrefix> BestStandard_ProbDamage_PrefixList = { StandardPrefix::Navas, StandardPrefix::Agareth, StandardPrefix::Asmodi, StandardPrefix::Kobal, StandardPrefix::Warrior, };

	std::vector<AdvancedSuffix> GoodAdvanced_ProbDamage_SuffixList = { AdvancedSuffix::Navas, AdvancedSuffix::Agareth, AdvancedSuffix::Asmodi, AdvancedSuffix::Kobal, AdvancedSuffix::Warrior, AdvancedSuffix::Hound, AdvancedSuffix::Proson, AdvancedSuffix::Aloken, AdvancedSuffix::Tobit, AdvancedSuffix::Neophyte };
	std::vector<AdvancedSuffix> BestAdvanced_ProbDamage_SuffixList = { AdvancedSuffix::Navas, AdvancedSuffix::Agareth, AdvancedSuffix::Asmodi, AdvancedSuffix::Kobal, AdvancedSuffix::Warrior, };
	std::vector<StandardSuffix> GoodStandard_ProbDamage_SuffixList = { StandardSuffix::Navas, StandardSuffix::Agareth, StandardSuffix::Asmodi, StandardSuffix::Kobal, StandardSuffix::Warrior, StandardSuffix::Hound, StandardSuffix::Proson, StandardSuffix::Aloken, StandardSuffix::Tobit, StandardSuffix::Neophyte };
	std::vector<StandardSuffix> BestStandard_ProbDamage_SuffixList = { StandardSuffix::Navas, StandardSuffix::Agareth, StandardSuffix::Asmodi, StandardSuffix::Kobal, StandardSuffix::Warrior, };

	// reattack minmax
	std::vector<AdvancedPrefix> GoodAdvanced_ReattackDamage_PrefixList = { AdvancedPrefix::Max, AdvancedPrefix::Squire, AdvancedPrefix::Rukieper, AdvancedPrefix::Major };
	std::vector<AdvancedPrefix> BestAdvanced_ReattackDamage_PrefixList = { AdvancedPrefix::Max, AdvancedPrefix::Squire };
	std::vector<StandardPrefix> GoodStandard_ReattackDamage_PrefixList = { StandardPrefix::Max, StandardPrefix::Squire, StandardPrefix::Rukieper, StandardPrefix::Major };
	std::vector<StandardPrefix> BestStandard_ReattackDamage_PrefixList = { StandardPrefix::Max, StandardPrefix::Squire };

	std::vector<AdvancedSuffix> GoodAdvanced_ReattackDamage_SuffixList = { AdvancedSuffix::Max, AdvancedSuffix::Squire, AdvancedSuffix::Rukieper, AdvancedSuffix::Major };
	std::vector<AdvancedSuffix> BestAdvanced_ReattackDamage_SuffixList = { AdvancedSuffix::Max, AdvancedSuffix::Squire };
	std::vector<StandardSuffix> GoodStandard_ReattackDamage_SuffixList = { StandardSuffix::Max, StandardSuffix::Squire, StandardSuffix::Rukieper, StandardSuffix::Major };
	std::vector<StandardSuffix> BestStandard_ReattackDamage_SuffixList = { StandardSuffix::Max, StandardSuffix::Squire };


	GambleBot::GambleBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
	{
		m_state = GambleBotState::STANDBY;
		UpdateTotalGambleItemAmount();
		m_current_gambleitem_uid = 0;
		m_is_advanced_weapon = false;
		m_select_new_weapon = false;

		m_do_prefix_gamble = false;
		m_do_suffix_gamble = false;
		m_do_prefix_gamble_temp = false;
		m_do_suffix_gamble_temp = false;

		m_next_gamble_action = GambleAction::NONE;
		m_waiting_for_answer = false;

		m_gamble_check_time = 0.0f;			
		m_internal_action_check_time = 0.0f;	

		ZeroMemory(&m_suffix_selection, sizeof(FixSelection));
		ZeroMemory(&m_prefix_selection, sizeof(FixSelection));

		m_gamble_timer = BuddyTimer(GAMBLE_TIME_BASE, GAMBLE_TIME_VARIANCE);
		m_action_timer = BuddyTimer(GAMBLE_ACTION_TIME_BASE, GAMBLE_ACTION_VARIANCE);
	}

	GambleBot::~GambleBot()
	{

	}

	void GambleBot::Tick()
	{												 
		if (!IsEnabled()) {
			return;
		}

		INVEN_DISPLAY_INFO* selected = nullptr;	
		bool character_in_laboratory = (OSR_API->GetCurrentBuildingKind() == BUILDINGKIND_LABORATORY);
		if (GetGambleBotState() != GambleBotState::NOT_IN_LABORATORY && !character_in_laboratory) 
		{
			SetGambleBotState(GambleBotState::NOT_IN_LABORATORY);
			ResetGambleItem();
		}
	

		switch (GetGambleBotState())
		{
		case GambleBotState::NOT_IN_LABORATORY:
			if (character_in_laboratory) 
			{
				//DetermineNextAction();
				SetGambleBotState(GambleBotState::STANDBY);
			}
			break;

		case GambleBotState::STANDBY:
			if (m_select_new_weapon)
			{
				selected = OSR_API->GetSelectedItem();
				if (selected && selected->pItem->UniqueNumber != m_current_gambleitem_uid && IS_WEAPON(selected->pItem->Kind))
				{																										  
					SetGambleItem(selected->pItem->UniqueNumber);
					m_next_gamble_action = DetermineNextAction();
					m_select_new_weapon = false;
				}
			}
			break;

		case GambleBotState::GAMBLING:
			if (m_waiting_for_answer) // maybe rework this into recieved packet code
			{
				CItemInfo* targetitem = OSR_API->FindItemFromTarget(m_current_gambleitem_uid);
				if (targetitem && TryTargetItemToInventory())
				{
					m_next_gamble_action = DetermineNextAction();
					if (m_auto_gamble) {
						AddNeededSourceItems(m_next_gamble_action);
					}
					else {
						SetGambleBotState(GambleBotState::STANDBY);
					}	  
					m_item_persisting->Save(m_statisticsWeapon);
					m_waiting_for_answer = false;
				}
			}
			else
			{
				if (m_next_gamble_action == GambleAction::NONE) 
				{
					Reset();
					SetGambleBotState(GambleBotState::STANDBY);
				} 

				if (TryDoGambleAction()) {		
					m_waiting_for_answer = true;
				}
			}
			break;
		}

	}

	void GambleBot::RenderImGui()
	{
		if (!DrawEnableCheckBox()) {
			//return;
		}

		ImGui::NewLine();  
		ImGui::BeginDisabledMode(m_state == GambleBotState::NOT_IN_LABORATORY || !IsEnabled());
		{  
			ImGui::BeginGroup(); // Weapon Selection
			{
				ImGui::Separator();
				ImGui::Text("Item Selection");
				ImGui::Separator();

				if (ImGui::Button("Select New"))
				{
					ResetGambleItem();
					m_select_new_weapon = true;
					SetGambleBotState(GambleBotState::STANDBY);
				}  
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Press the \"Select New\" button and then click on an weapon in inventory to select a new gamble item.");
				}
				ImGui::SameLine();
				if (m_select_new_weapon) {
					ImGui::Text("waiting for selection...");   
				}
				else if (m_current_gambleitem_uid == 0) {
					ImGui::Text("Select item to start gambling.");
				}
				else {
					m_gamble_item.RenderImGui();
				}
			}
			ImGui::EndGroup();
	

			ImGui::NewLine();

			ImGui::BeginColumns("GambleBotColumns", 2, ImGuiColumnsFlags_NoResize);
			{
				ImGui::SetColumnWidth(0, 430);
				ImGui::BeginChild("KitBotCol1", ImVec2(), false);
				{ 				
					//ImGui::Separator();
					ImGui::Text("Settings");
					ImGui::Separator();

					ImGui::NewLine();
					DrawSettings();
				}
				ImGui::EndChild();
			}
			ImGui::NextColumn();
			{
				ImGui::BeginChild("KitBotCol2", ImVec2(), false);
				{
					ImGui::BeginGroup();
					{
						//ImGui::Separator();
						ImGui::Text("Gambleitems Overview");
						ImGui::Separator();

						ImGui::NewLine();
						ImGui::BeginColumns("GambleItemsColumns", 3, ImGuiColumnsFlags_NoResize);
						{
							ImGui::SetColumnWidth(0, 75);
							ImGui::SetColumnWidth(1, 110);
							ImGui::Text("Prefix:");
							ImGui::NewLine();
							ImGui::NewLine();
							ImGui::Text("Suffix:");
							ImGui::NewLine();
							ImGui::NewLine();
						}
						ImGui::NextColumn();
						{
							ImGui::Text("SG Advanced");
							ImGui::Text("SG Standard");
							ImGui::Text("Initialization");
							ImGui::Text("SG Advanced");
							ImGui::Text("SG Standard");
							ImGui::Text("Initialization");
						}
						ImGui::NextColumn();
						{							
							DrawColoredGambleItemAmount(m_amount_SG_ADV_Prefix);
							DrawColoredGambleItemAmount(m_amount_SG_STD_Prefix);
							DrawColoredGambleItemAmount(m_amount_removal_Prefix);
							DrawColoredGambleItemAmount(m_amount_SG_ADV_Suffix);
							DrawColoredGambleItemAmount(m_amount_SG_STD_Suffix);
							DrawColoredGambleItemAmount(m_amount_removal_Suffix);
						}
						ImGui::EndColumns();  
					}
					ImGui::EndGroup();
					ImGui::NewLine();
					ImGui::BeginGroup();
					{
						ImGui::Separator();
						ImGui::Text("Control");
						ImGui::Separator();

						ImGui::Text("Next gamble action:");
						ImGui::Text(GetGambleActionString(m_next_gamble_action));
						ImGui::NewLine();

						if (ImGui::Button("Gamble"))
						{
							if (m_state == GambleBotState::STANDBY && m_gamble_timer.IsReady()) {
								SetGambleBotState(GambleBotState::GAMBLING);
							}
						}
						ImGui::SameLine();
						ImGui::Checkbox("Auto", &m_auto_gamble);
						if (ImGui::IsItemHovered()) {
							ImGui::SetTooltip("Will keep gambling until fix is found or there are no more gamble items");
						}
					}
					ImGui::EndGroup();
				}
				ImGui::EndChild();
			}
			ImGui::EndColumns();
		}
		ImGui::EndDisabledMode();
	}

	std::string GambleBot::GetName() const
	{
		return  "GambleBot";
	}

	void GambleBot::DrawSettings()
	{  	
		const char* items[] = { "None", "Good", "Best" };

		ImGui::BeginColumns("SettingsColumns", 2, ImGuiColumnsFlags_NoResize);
		{  
			ImGui::BeginChild("PrefixOptions", ImVec2(0, 0), false);
			{
				ImGui::Text("Prefix Options:");
				//ImGui::Separator();

				if (ImGui::Checkbox("Gambling active", &m_do_prefix_gamble_temp))
				{
					if (m_state == GambleBotState::STANDBY) {
						m_next_gamble_action = DetermineNextAction();
					}
				}
				ImGui::NewLine();
				ImGui::Text("Stop autogamble at:");		
				ImGui::Checkbox("Any non-green Fix", &m_prefix_selection.AllNonGreen);	
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Stops at any fix that has not a green color");
				}
				ImGui::NewLine();
				ImGui::PushItemWidth(80);
				ImGui::ComboEx("Any Fix", reinterpret_cast<int*>(&m_prefix_selection.Any), items, 3, -1, false);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Stops if any of the below good/best fixes are found");
				}

				ImGui::PushStyleColor(ImGuiCol_Text, AceColouredString::TranslateAceCharToColor('e').Value);
				ImGui::ComboEx("Prob/Damage", reinterpret_cast<int*>(&m_prefix_selection.ProbDamage), items, 3, -1, false);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Best: Navas, Agareth, Asmodi, Kobal, Warrior\nGood: Navas, Agareth, Asmodi, Kobal, Warrior, Hound, Proson, Aloken, Tobit, Neopyte");
				}
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Text, AceColouredString::TranslateAceCharToColor('c').Value);
				ImGui::ComboEx("Prob/Reattack", reinterpret_cast<int*>(&m_prefix_selection.ProbReattack), items, 3, -1, false);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Best: Legend, Bio\nGood: Legend, Bio, Attack, Silence, Meteo");
				}
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Text, AceColouredString::TranslateAceCharToColor('r').Value);
				ImGui::ComboEx("Reattack/Damage", reinterpret_cast<int*>(&m_prefix_selection.ReattackDamage), items, 3, -1, false);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Best: Max, Squire\nGood: Max, Squire, Major, Rukieper");
				}
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Text, AceColouredString::TranslateAceCharToColor('y').Value);
				ImGui::ComboEx("Pierce", reinterpret_cast<int*>(&m_prefix_selection.Pierce), items, 3, -1, false);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Best: Bandit, Traitor\nGood: Bandit, Traitor, Archrival, Adversary, Bane, Challenger, Stronghold");
				}
				ImGui::PopStyleColor();
				ImGui::PopItemWidth();
			}
			ImGui::EndChild();
		}
		ImGui::NextColumn();
		ImGui::BeginChild("SuffixOptions", ImVec2(0, 0), false);
		{  
			ImGui::Text("Suffix Options:");
			//ImGui::Separator();

			if (ImGui::Checkbox("Gambling active##Suffix", &m_do_suffix_gamble_temp))
			{
				if (m_state == GambleBotState::STANDBY) {
					m_next_gamble_action = DetermineNextAction();
				}
			}
			ImGui::NewLine();
			ImGui::Text("Stop autogamble at:");						  
			ImGui::Checkbox("Any non-green Fix##Suffix", &m_suffix_selection.AllNonGreen);	
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Stops at any fix that has not a green color");
			}

			ImGui::NewLine();
			ImGui::PushItemWidth(80);
			ImGui::ComboEx("Any Fix##Suffix", reinterpret_cast<int*>(&m_suffix_selection.Any), items, 3, -1, false); 
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Stops if any of the below good/best fixes are found");
			}

			ImGui::PushStyleColor(ImGuiCol_Text, AceColouredString::TranslateAceCharToColor('e').Value);
			ImGui::ComboEx("Prob/Damage##Suffix", reinterpret_cast<int*>(&m_suffix_selection.ProbDamage), items, 3, -1, false);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Best: Navas, Agareth, Asmodi, Kobal, Warrior\nGood: Navas, Agareth, Asmodi, Kobal, Warrior, Hound, Proson, Aloken, Tobit, Neophyte");
			}	  
			ImGui::PopStyleColor();

			ImGui::PushStyleColor(ImGuiCol_Text, AceColouredString::TranslateAceCharToColor('c').Value);
			ImGui::ComboEx("Prob/Reattack##Suffix", reinterpret_cast<int*>(&m_suffix_selection.ProbReattack), items, 3, -1, false);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Best: Legend, Bio\nGood: Legend, Bio, Attack, Silence, Meteo");
			}
			ImGui::PopStyleColor();

			ImGui::PushStyleColor(ImGuiCol_Text, AceColouredString::TranslateAceCharToColor('r').Value);
			ImGui::ComboEx("Reattack/Damage##Suffix", reinterpret_cast<int*>(&m_suffix_selection.ReattackDamage), items, 3, -1, false);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Best: Max, Squire\nGood: Max, Squire, Major, Rukieper");
			}
			ImGui::PopStyleColor();
			ImGui::PopItemWidth();
		}
		ImGui::EndChild(); 
	}

	void GambleBot::DrawColoredGambleItemAmount(int amount)
	{
		if (amount >= 100) 
		{
			ImGui::PushStyleColor(ImGuiCol_Text, COLOR_GAMBLEITEM_GT_100);	
			ImGui::Text(std::to_string(amount).c_str());
			ImGui::PopStyleColor();
		
		}
		else if (amount > 0 && amount < 100) 
		{
			ImGui::PushStyleColor(ImGuiCol_Text, COLOR_GAMBLEITEM_LT_100);
			ImGui::Text(std::to_string(amount).c_str());
			ImGui::PopStyleColor();
		}
		else if (amount == 0) 
		{
			ImGui::PushStyleColor(ImGuiCol_Text, COLOR_GAMBLEITEM_EQ_0);
			ImGui::Text(std::to_string(amount).c_str());
			ImGui::PopStyleColor();
		}
	}
  						 
	void GambleBot::SetGambleBotState(GambleBotState state)
	{	
		if (m_state == GambleBotState::STANDBY && state == GambleBotState::GAMBLING) {
			AddNeededSourceItems(m_next_gamble_action);
		}

		m_state = state;
	}

	GambleBotState GambleBot::GetGambleBotState()
	{
		return m_state;
	}
   
	void GambleBot::SetGambleItem(UID64_t uid)
	{	
		if (uid == 0) {
			return;
		}

		m_gamble_item = OsrItemInfo(uid);
		if (!m_gamble_item.GetItemInfo() || !m_gamble_item.IsWeapon())
		{
			ResetGambleItem();
			return;
		}

		// try to load previous statistics for this weapon
		m_item_persisting.reset();
		m_item_persisting = m_buddy->GetPersistingTools()->GetLabStatisticPersistence(uid);
		m_item_persisting->Read(m_statisticsWeapon);

		/*
		m_buddy->GetPersistingTools()->CloseStream();
		m_buddy->GetPersistingTools()->SetItem(uid);
		m_buddy->GetPersistingTools()->ReadItemLabStatistics(m_statisticsWeapon);
		*/

		m_is_advanced_weapon = IS_SECONDARY_WEAPON_1(m_gamble_item.GetItemInfo()->Kind);
		m_current_gambleitem_uid = uid;
	}

	bool GambleBot::TrySimulateButtonClick(LabButtonCode button)
	{
		if (m_action_timer.IsReady())
		{
			OSR_API->OnButtonClick((int)button);
			m_action_timer.Reset();
			return true;
		}
		else {
			return false;
		}  	
	}	 	

	bool GambleBot::CheckRarePrefix(CItemInfo* weapon)
	{
		if (!IS_WEAPON(weapon->m_pItemInfo->Kind)) {
			return false;
		}

		if (!weapon->m_pRefPrefixRareInfo) {
			return false;
		}
	
		if (m_prefix_selection.AllNonGreen && weapon->m_pRefPrefixRareInfo->Name[0] == '\\') {
			return true;
		}

		int prefixcode = weapon->m_pRefPrefixRareInfo->CodeNum;
		bool is_standard = IS_PRIMARY_WEAPON(weapon->m_pItemInfo->Kind);
	
		// prob minmax
		switch ((m_prefix_selection.Any == FixCategory::None) ? m_prefix_selection.ProbDamage : m_prefix_selection.Any) 
		{
		case FixCategory::Good:
			if (is_standard)
			{
				if (std::find(GoodStandard_ProbDamage_PrefixList.begin(), GoodStandard_ProbDamage_PrefixList.end(), static_cast<StandardPrefix>(prefixcode)) != GoodStandard_ProbDamage_PrefixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(GoodAdvanced_ProbDamage_PrefixList.begin(), GoodAdvanced_ProbDamage_PrefixList.end(), static_cast<AdvancedPrefix>(prefixcode)) != GoodAdvanced_ProbDamage_PrefixList.end()) {
					return true;
				}
			}
			break;
		case FixCategory::Best:
			if (is_standard)
			{
				if (std::find(BestStandard_ProbDamage_PrefixList.begin(), BestStandard_ProbDamage_PrefixList.end(), static_cast<StandardPrefix>(prefixcode)) != BestStandard_ProbDamage_PrefixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(BestAdvanced_ProbDamage_PrefixList.begin(), BestAdvanced_ProbDamage_PrefixList.end(), static_cast<AdvancedPrefix>(prefixcode)) != BestAdvanced_ProbDamage_PrefixList.end()) {
					return true;
				}
			}
			break;
		}

		// pierce
		switch ((m_prefix_selection.Any == FixCategory::None) ? m_prefix_selection.Pierce : m_prefix_selection.Any)
		{
		case FixCategory::Good:
			if (is_standard)
			{
				if (std::find(GoodStandard_Pierce_PrefixList.begin(), GoodStandard_Pierce_PrefixList.end(), static_cast<StandardPrefix>(prefixcode)) != GoodStandard_Pierce_PrefixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(GoodAdvanced_Pierce_PrefixList.begin(), GoodAdvanced_Pierce_PrefixList.end(), static_cast<AdvancedPrefix>(prefixcode)) != GoodAdvanced_Pierce_PrefixList.end()) {
					return true;
				}
			}
			break;		
		case FixCategory::Best:
			if (is_standard)
			{
				if (std::find(BestStandard_Pierce_PrefixList.begin(), BestStandard_Pierce_PrefixList.end(), static_cast<StandardPrefix>(prefixcode)) != BestStandard_Pierce_PrefixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(BestAdvanced_Pierce_PrefixList.begin(), BestAdvanced_Pierce_PrefixList.end(), static_cast<AdvancedPrefix>(prefixcode)) != BestAdvanced_Pierce_PrefixList.end()) {
					return true;
				}
			}
			break;
		}

		// prob reattack
		switch ((m_prefix_selection.Any == FixCategory::None) ? m_prefix_selection.ProbReattack : m_prefix_selection.Any)
		{
		case FixCategory::Good:
			if (is_standard)
			{
				if (std::find(GoodStandard_ProbReattack_PrefixList.begin(), GoodStandard_ProbReattack_PrefixList.end(), static_cast<StandardPrefix>(prefixcode)) != GoodStandard_ProbReattack_PrefixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(GoodAdvanced_ProbReattack_PrefixList.begin(), GoodAdvanced_ProbReattack_PrefixList.end(), static_cast<AdvancedPrefix>(prefixcode)) != GoodAdvanced_ProbReattack_PrefixList.end()) {
					return true;
				}
			}
			break;
		case FixCategory::Best:
			if (is_standard)
			{
				if (std::find(BestStandard_ProbReattack_PrefixList.begin(), BestStandard_ProbReattack_PrefixList.end(), static_cast<StandardPrefix>(prefixcode)) != BestStandard_ProbReattack_PrefixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(BestAdvanced_ProbReattack_PrefixList.begin(), BestAdvanced_ProbReattack_PrefixList.end(), static_cast<AdvancedPrefix>(prefixcode)) != BestAdvanced_ProbReattack_PrefixList.end()) {
					return true;
				}
			}
			break;
		}

		// reattack minmax
		switch ((m_prefix_selection.Any == FixCategory::None) ? m_prefix_selection.ReattackDamage : m_prefix_selection.Any)
		{
		case FixCategory::Good:
			if (is_standard)
			{
				if (std::find(GoodStandard_ReattackDamage_PrefixList.begin(), GoodStandard_ReattackDamage_PrefixList.end(), static_cast<StandardPrefix>(prefixcode)) != GoodStandard_ReattackDamage_PrefixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(GoodAdvanced_ReattackDamage_PrefixList.begin(), GoodAdvanced_ReattackDamage_PrefixList.end(), static_cast<AdvancedPrefix>(prefixcode)) != GoodAdvanced_ReattackDamage_PrefixList.end()) {
					return true;
				}
			}
			break;
		case FixCategory::Best:
			if (is_standard)
			{
				if (std::find(BestStandard_ReattackDamage_PrefixList.begin(), BestStandard_ReattackDamage_PrefixList.end(), static_cast<StandardPrefix>(prefixcode)) != BestStandard_ReattackDamage_PrefixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(BestAdvanced_ReattackDamage_PrefixList.begin(), BestAdvanced_ReattackDamage_PrefixList.end(), static_cast<AdvancedPrefix>(prefixcode)) != BestAdvanced_ReattackDamage_PrefixList.end()) {
					return true;
				}
			}
			break;
		}

		return false;
	}

	bool GambleBot::CheckRareSuffix(CItemInfo* weapon)
	{
		if (!IS_WEAPON(weapon->m_pItemInfo->Kind)) {
			return false;
		}

		if (!weapon->m_pRefSuffixRareInfo) {
			return false;
		}  


		if (m_suffix_selection.AllNonGreen && weapon->m_pRefSuffixRareInfo->Name[0] == '\\') {
			return true;
		}

		int suffixcode = weapon->m_pRefSuffixRareInfo->CodeNum;
		bool is_standard = IS_PRIMARY_WEAPON(weapon->m_pItemInfo->Kind);

		// prob minmax
		switch ((m_suffix_selection.Any == FixCategory::None) ? m_suffix_selection.ProbDamage : m_suffix_selection.Any)
		{
		case FixCategory::Good:
			if (is_standard)
			{
				if (std::find(GoodStandard_ProbDamage_SuffixList.begin(), GoodStandard_ProbDamage_SuffixList.end(), static_cast<StandardSuffix>(suffixcode)) != GoodStandard_ProbDamage_SuffixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(GoodAdvanced_ProbDamage_SuffixList.begin(), GoodAdvanced_ProbDamage_SuffixList.end(), static_cast<AdvancedSuffix>(suffixcode)) != GoodAdvanced_ProbDamage_SuffixList.end()) {
					return true;
				}
			}
			break;
		case FixCategory::Best:
			if (is_standard)
			{
				if (std::find(BestStandard_ProbDamage_SuffixList.begin(), BestStandard_ProbDamage_SuffixList.end(), static_cast<StandardSuffix>(suffixcode)) != BestStandard_ProbDamage_SuffixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(BestAdvanced_ProbDamage_SuffixList.begin(), BestAdvanced_ProbDamage_SuffixList.end(), static_cast<AdvancedSuffix>(suffixcode)) != BestAdvanced_ProbDamage_SuffixList.end()) {
					return true;
				}
			}
			break;
		}

		// prob reattack
		switch ((m_suffix_selection.Any == FixCategory::None) ? m_suffix_selection.ProbReattack : m_suffix_selection.Any)
		{  
		case FixCategory::Good:
			if (is_standard)
			{
				if (std::find(GoodStandard_ProbReattack_SuffixList.begin(), GoodStandard_ProbReattack_SuffixList.end(), static_cast<StandardSuffix>(suffixcode)) != GoodStandard_ProbReattack_SuffixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(GoodAdvanced_ProbReattack_SuffixList.begin(), GoodAdvanced_ProbReattack_SuffixList.end(), static_cast<AdvancedSuffix>(suffixcode)) != GoodAdvanced_ProbReattack_SuffixList.end()) {
					return true;
				}
			}
			break;
		case FixCategory::Best:
			if (is_standard)
			{
				if (std::find(BestStandard_ProbReattack_SuffixList.begin(), BestStandard_ProbReattack_SuffixList.end(), static_cast<StandardSuffix>(suffixcode)) != BestStandard_ProbReattack_SuffixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(BestAdvanced_ProbReattack_SuffixList.begin(), BestAdvanced_ProbReattack_SuffixList.end(), static_cast<AdvancedSuffix>(suffixcode)) != BestAdvanced_ProbReattack_SuffixList.end()) {
					return true;
				}
			}
			break;
		}

		// reattack minmax
		switch ((m_suffix_selection.Any == FixCategory::None) ? m_suffix_selection.ReattackDamage : m_suffix_selection.Any)
		{
		case FixCategory::Good:
			if (is_standard)
			{
				if (std::find(GoodStandard_ReattackDamage_SuffixList.begin(), GoodStandard_ReattackDamage_SuffixList.end(), static_cast<StandardSuffix>(suffixcode)) != GoodStandard_ReattackDamage_SuffixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(GoodAdvanced_ReattackDamage_SuffixList.begin(), GoodAdvanced_ReattackDamage_SuffixList.end(), static_cast<AdvancedSuffix>(suffixcode)) != GoodAdvanced_ReattackDamage_SuffixList.end()) {
					return true;
				}
			}
			break;
		case FixCategory::Best:
			if (is_standard)
			{
				if (std::find(BestStandard_ReattackDamage_SuffixList.begin(), BestStandard_ReattackDamage_SuffixList.end(), static_cast<StandardSuffix>(suffixcode)) != BestStandard_ReattackDamage_SuffixList.end()) {
					return true;
				}
			}
			else
			{
				if (std::find(BestAdvanced_ReattackDamage_SuffixList.begin(), BestAdvanced_ReattackDamage_SuffixList.end(), static_cast<AdvancedSuffix>(suffixcode)) != BestAdvanced_ReattackDamage_SuffixList.end()) {
					return true;
				}
			}

			break;
		}

		return false;
	}

	const char* GambleBot::GetGambleActionString(GambleAction action)
	{
		switch (action)
		{
		case GambleAction::NONE:
			return "No action";
		case GambleAction::ADD_PREFIX:
			return "Add prefix";
		case GambleAction::ADD_SUFFIX:
			return "Add suffix";
		case GambleAction::ADD_PREFIX_AND_SUFFIX:
			return "Add prefix and suffix";
		case GambleAction::REMOVE_PREFIX:
			return "Remove prefix";
		case GambleAction::REMOVE_SUFFIX:
			return "Remove suffix";
		case GambleAction::REMOVE_PREFIX_AND_SUFFIX:
			return "Remove prefix and suffix";
		default:
			return "Unknown";
		}
	}

	void GambleBot::UpdateTotalGambleItemAmount()
	{
		m_amount_removal_Prefix = GetTotalInventoryAmount(GambleItem::INIT_PREFIX);
		m_amount_removal_Suffix = GetTotalInventoryAmount(GambleItem::INIT_SUFFIX);

		m_amount_SG_ADV_Prefix = GetTotalInventoryAmount(GambleItem::SG_ADV_PREFIX);
		m_amount_SG_ADV_Suffix = GetTotalInventoryAmount(GambleItem::SG_ADV_SUFFIX);

		m_amount_SG_STD_Prefix = GetTotalInventoryAmount(GambleItem::SG_STD_PREFIX);
		m_amount_SG_STD_Suffix = GetTotalInventoryAmount(GambleItem::SG_STD_SUFFIX);
	}

	int GambleBot::GetTotalInventoryAmount(GambleItem gambleItem)
	{
		int amount = 0;
		CItemInfo* gambleitem = nullptr;

		switch (gambleItem)
		{
		case GambleItem::SG_ADV_PREFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Adv_Weapon_SG_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
		
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Advance_Weapon_Super_Gamble_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			break;

		case GambleItem::SG_ADV_SUFFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Adv_Weapon_SG_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
		
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Advance_Weapon_Super_Gamble_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			break;

		case GambleItem::SG_STD_PREFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Std_Weapon_SG_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
		
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Std_Weapon_Super_Gamble_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			break;

		case GambleItem::SG_STD_SUFFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Std_Weapon_SG_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Std_Weapon_Super_Gamble_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			break;

		case GambleItem::INIT_PREFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Gamble_Initialization_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Gamble_Initialization_Card_2);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			break;
		case GambleItem::INIT_SUFFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Gamble_Initialization_Card);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Gamble_Initialization_Card_2);
			if (gambleitem) {
				amount += gambleitem->CurrentCount;
			}
			break;
		}

		return amount;
	}

	void GambleBot::ResetGambleItem()
	{  	
		m_current_gambleitem_uid = 0;
		m_needed_source_items = std::queue<GambleItem>();
	}

	// executed after gambling action finished
	bool GambleBot::TryTargetItemToInventory()
	{	
		// wait until we could simulate the button to transfer the results into the inventory
   		if (!TrySimulateButtonClick(LabButtonCode::Ok)) {
			return false;
		}

		// item should be in inventory now	
		SetGambleItem(m_current_gambleitem_uid);

		// m_nextGambleAction is the action that was just done
		GambleAction current_action = m_next_gamble_action;
		 		
		bool found_prefix = false, found_suffix = false;

		switch (current_action)
		{
		case GambleAction::ADD_PREFIX:
			if (CheckRarePrefix(m_gamble_item.GetItemInfo())) 
			{
				m_do_prefix_gamble = false;
				m_do_prefix_gamble_temp = false;
				found_prefix = true;
			}
			break;
		case GambleAction::ADD_SUFFIX:
			if (CheckRareSuffix(m_gamble_item.GetItemInfo()))
			{ 
				m_do_suffix_gamble = false;
				m_do_suffix_gamble_temp = false;
				found_suffix = true;
			}
			break;
		case GambleAction::ADD_PREFIX_AND_SUFFIX:
			if (CheckRarePrefix(m_gamble_item.GetItemInfo()))
			{
				m_do_prefix_gamble = false;
				m_do_prefix_gamble_temp = false;
				found_prefix = true;
			}
			if (CheckRareSuffix(m_gamble_item.GetItemInfo()))
			{
				m_do_suffix_gamble = false;
				m_do_suffix_gamble_temp = false;
				found_suffix = true;   	 
			}
			break;	
		}

		if (found_prefix && found_suffix)
		{
			m_buddy->NotifySound(NotifyType::Information);
			if (m_buddy->NotificationPopupAllowed())
			{
				std::string msg = "Found rare fixes: " + m_gamble_item.GetCleanPrefixName() + " of " + m_gamble_item.GetCleanSuffixName();
				m_buddy->OpenMessageBoxAsync(msg, GetName(), NotifyType::Warning);
			}
		}
		else if (found_prefix)
		{
			m_buddy->NotifySound(NotifyType::Information);
			if (m_buddy->NotificationPopupAllowed())
			{
				std::string msg = "Found rare prefix  " + m_gamble_item.GetCleanPrefixName();
				m_buddy->OpenMessageBoxAsync(msg, GetName(), NotifyType::Warning);
			}
		}
		else if (found_suffix)
		{
			m_buddy->NotifySound(NotifyType::Information);
			if (m_buddy->NotificationPopupAllowed())
			{
				std::string msg = "Found rare suffix  " + m_gamble_item.GetCleanSuffixName();
				m_buddy->OpenMessageBoxAsync(msg, GetName(), NotifyType::Warning);
			}
		}  	
		return true;
	 }

	bool GambleBot::TryDoGambleAction()
	{
		if (!m_gamble_timer.IsReady()) {
			return false;
		}

		if (!m_needed_source_items.empty())
		{  
			if (!m_action_timer.IsReady()) {
				return false;
			}

			GambleItem needed_item = m_needed_source_items.front();
			m_needed_source_items.pop();

			CItemInfo* item = FindGambleItemFromInventory(needed_item);
			if (!item)
			{
				Reset();
				SetGambleBotState(GambleBotState::STANDBY);
				return false;
			}

			OSR_API->InvenToSourceItem(item, 1, false);
			if (needed_item == GambleItem::SOURCE_ITEM) {
				m_gamble_item.UpdateItemInfo();
			}

			m_action_timer.Reset();
			return false;
		}
		else
		{
			if (!TrySimulateButtonClick(LabButtonCode::Send)) {
				return false;
			}

			m_gamble_timer.Reset();
		} 
	
		return true;
	}

	CItemInfo* GambleBot::FindGambleItemFromInventory(GambleItem gambleitemkind)
	{
		CItemInfo* gambleitem = nullptr;

		switch (gambleitemkind)
		{
		case GambleItem::SG_ADV_PREFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Adv_Weapon_SG_Card);
			if (!gambleitem) {
				gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Advance_Weapon_Super_Gamble_Card);
			}
			break;
		case GambleItem::SG_ADV_SUFFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Adv_Weapon_SG_Card);
			if (!gambleitem) {
				gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Advance_Weapon_Super_Gamble_Card);
			}
			break;
		case GambleItem::SG_STD_PREFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Std_Weapon_SG_Card);
			if (!gambleitem) {
				gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Std_Weapon_Super_Gamble_Card);
			}
			break;
		case GambleItem::SG_STD_SUFFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Std_Weapon_SG_Card);
			if (!gambleitem) {
				gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Std_Weapon_Super_Gamble_Card);
			}
			break;
		case GambleItem::INIT_PREFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Gamble_Initialization_Card);
			if (!gambleitem) {
				gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Prefix_Gamble_Initialization_Card_2);
			}
			break;
		case GambleItem::INIT_SUFFIX:
			gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Gamble_Initialization_Card);
			if (!gambleitem) {
				gambleitem = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Suffix_Gamble_Initialization_Card_2);
			}
			break;
		case GambleItem::SOURCE_ITEM:
			gambleitem = m_gamble_item.GetItemInfo();
			break;
		}	

		return gambleitem;
	}
  	 

	GambleAction GambleBot::DetermineNextAction()
	{
		UpdateTotalGambleItemAmount();

		m_do_prefix_gamble = m_do_prefix_gamble_temp;
		m_do_suffix_gamble = m_do_suffix_gamble_temp;
									   
		if (!m_gamble_item.GetItemInfo()) {
			return GambleAction::NONE;
		}

		if (!m_do_prefix_gamble && !m_do_suffix_gamble) {
			return GambleAction::NONE;
		}

		bool remove_prefix = false;
		bool remove_suffix = false;
		bool add_prefix = false;
		bool add_suffix = false;

		if (m_do_prefix_gamble)
		{
			// Check if we need to remove prefix first
			if (m_gamble_item.GetItemInfo()->m_pRefPrefixRareInfo)
			{
				if (m_amount_removal_Prefix > 0) {
					remove_prefix = true;
				}
				else  // missing gamble items
				{
					remove_prefix = false;
					m_do_prefix_gamble = false;
					m_do_prefix_gamble_temp = false;
				} 			
			}

			if (!m_gamble_item.GetItemInfo()->m_pRefPrefixRareInfo)
			{
				if ((m_is_advanced_weapon) ? m_amount_SG_ADV_Prefix > 0 : m_amount_SG_STD_Prefix > 0) {
					add_prefix = true;
				}
				else  // missing gamble items
				{
					add_prefix = false;
					m_do_prefix_gamble = false;
					m_do_prefix_gamble_temp = false;
				} 			
			} 		
		}

		if (m_do_suffix_gamble)
		{
			// Check if we need to remove prefix first
			if (m_gamble_item.GetItemInfo()->m_pRefSuffixRareInfo)
			{
				if (m_amount_removal_Suffix > 0) {
					remove_suffix = true;
				}
				else  // missing gamble items
				{	
					remove_suffix = false;
					m_do_suffix_gamble = false;
					m_do_suffix_gamble_temp = false;
				}
			}

			if (!m_gamble_item.GetItemInfo()->m_pRefSuffixRareInfo)
			{
				if ((m_is_advanced_weapon) ? m_amount_SG_ADV_Suffix > 0 : m_amount_SG_STD_Suffix > 0)	{
					add_suffix = true;
				}
				else  // missing gamble items
				{	
					add_suffix = false;
					m_do_suffix_gamble = false;
					m_do_suffix_gamble_temp = false;
				}			
			}
		}
	
		if (add_prefix && add_suffix) {			
			return GambleAction::ADD_PREFIX_AND_SUFFIX;
		}

		if (remove_prefix && remove_suffix)	{		
			return GambleAction::REMOVE_PREFIX_AND_SUFFIX;
		}												  

		if (add_prefix && !add_suffix) {	 		
			return GambleAction::ADD_PREFIX;
		}

		if (remove_prefix && !remove_suffix) {		
			return GambleAction::REMOVE_PREFIX;
		}

		if (!add_prefix && add_suffix) {  		
			return GambleAction::ADD_SUFFIX;
		}

		if (!remove_prefix && remove_suffix) {  		
			return GambleAction::REMOVE_SUFFIX;
		}  
	
		if (!remove_prefix && !remove_suffix && !add_prefix && !add_suffix) {	  		
			return GambleAction::NONE;
		}

		return GambleAction::NONE;
	}

	void GambleBot::AddNeededSourceItems(GambleAction action)
	{
		m_needed_source_items = std::queue<GambleItem>();

		switch (action)
		{
		case GambleAction::NONE:
			break;
		case GambleAction::ADD_PREFIX:			
			m_needed_source_items.push((m_is_advanced_weapon) ? GambleItem::SG_ADV_PREFIX : GambleItem::SG_STD_PREFIX);
			m_needed_source_items.push(GambleItem::SOURCE_ITEM);
			break;
		case GambleAction::ADD_SUFFIX:
			m_needed_source_items.push(GambleItem::SOURCE_ITEM);
			m_needed_source_items.push((m_is_advanced_weapon) ? GambleItem::SG_ADV_SUFFIX : GambleItem::SG_STD_SUFFIX);
			break;
		case GambleAction::ADD_PREFIX_AND_SUFFIX:
			m_needed_source_items.push((m_is_advanced_weapon) ? GambleItem::SG_ADV_PREFIX : GambleItem::SG_STD_PREFIX);
			m_needed_source_items.push(GambleItem::SOURCE_ITEM);
			m_needed_source_items.push((m_is_advanced_weapon) ? GambleItem::SG_ADV_SUFFIX : GambleItem::SG_STD_SUFFIX);
			break;
		case GambleAction::REMOVE_PREFIX:
			m_needed_source_items.push(GambleItem::INIT_PREFIX);
			m_needed_source_items.push(GambleItem::SOURCE_ITEM);
			break;
		case GambleAction::REMOVE_SUFFIX:
			m_needed_source_items.push(GambleItem::SOURCE_ITEM);
			m_needed_source_items.push(GambleItem::INIT_SUFFIX);
			break;
		case GambleAction::REMOVE_PREFIX_AND_SUFFIX:	 
			m_needed_source_items.push(GambleItem::INIT_PREFIX);
			m_needed_source_items.push(GambleItem::SOURCE_ITEM);
			m_needed_source_items.push(GambleItem::INIT_SUFFIX);
			break; 
		}
	}

	void GambleBot::Reset()
	{
		//if (TrySimulateButtonClick(LabButtonCode::Cancel))
		{
			SetGambleItem(m_current_gambleitem_uid);
			SetGambleBotState(GambleBotState::STANDBY);
			m_next_gamble_action = DetermineNextAction();
			m_waiting_for_answer = false;
		}
	}

	FeatureType GambleBot::GetType() const
	{
		return FeatureType::GambleBot;
	}

	void GambleBot::OnEnable()
	{
		const BuddyFeatureBase* enchantBot = m_buddy->GetFeatureByType(FeatureType::EnchantBot);
		if (enchantBot && enchantBot->IsEnabled()) 
		{
			MessageBeep(MB_ICONWARNING);
			Enable(false);
		}
	}
}