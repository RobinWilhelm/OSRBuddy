#include "EnchantBot.h"
#include "OSRBuddy.h"
#include "OSRImGuiMenu.h" 
#include "Utility.h"

#include "OsrItemInfo.h"
#include "OSRAPI.h"


EnchantBot::EnchantBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_state = EnchantBotState::STANDBY;
	ResetEnchantList(m_currentEnchants);
	ResetEnchantList(m_wantedEnchants);
}

EnchantBot::~EnchantBot()
{
}

void EnchantBot::Tick()
{
	UpdateCheckTime(OSR_API->GetElapsedTime());

	if (!IsEnabled()) {
		return;
	}

	bool character_in_laboratory = (OSR_API->GetCurrentyBuildingKind() == BUILDINGKIND_LABORATORY);
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
				SetEnchantItem(selected->pItem->UniqueNumber);
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
				// item should be in inventory now, set the current enchant item again					
				SetEnchantItem(m_currentEnchantItemUID);				
				m_next_action = EnchantAction::Add_EnchantItem;
				if (!m_auto_enchant) {
					SetEnchantBotState(EnchantBotState::STANDBY);
				}

				if (EnchantFinished())
				{
					Notify(NotifyType::ENCHANTING_FINISHED);
					SetEnchantBotState(EnchantBotState::STANDBY);
				}
				int postEnch = m_enchant_item.GetItemInfo()->m_nEnchantNumber;
				if (m_preEnch >= 5) {
					if (postEnch <= m_preEnch)
					{
						m_enchantStats[m_preEnch - 5][0] += 1;
						m_enchantStats[m_preEnch - 5][1] += 1;
					}
					else
					{
						m_enchantStats[m_preEnch - 5][0] += 1;
					}
				}
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

	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	if (GetEnchantBotState() == EnchantBotState::NOT_IN_LABORATORY) {
		ImGui::Text("You are not at the laboratory! Bot wont work!");
	}

	ImGui::BeginGroupPanel("Item Selection", ImVec2(500, 100));
	{
		if (ImGui::Button("Select New"))
		{
			ResetCurrentEnchantItem();
			m_selectNewEnchantItem = true;
			SetEnchantBotState(EnchantBotState::STANDBY);
		}
		ImGui::SameLine();
		if (!m_currentEnchantItemUID || m_selectNewEnchantItem) {
			ImGui::Text("waiting for selection...");
		}
		else {
			DrawEnchantItemText();
		}
	}
	ImGui::EndGroupPanel();
	ImGui::BeginGroupPanel("Settings", ImVec2(300, 400));
	{
		ImGui::Spacing();
		DrawSettings();
		ImGui::Spacing();
	}
	ImGui::EndGroupPanel();
	ImGui::SameLine();	   
						  	
	int current_idx = 0;
	ImGui::BeginGroupPanel("Current Enchants", ImVec2(140, 100));
	{
		ImGui::SameLine();
		ImGui::PushItemWidth(110);
		ImGui::EnchantList("##current_enchants", &current_idx, m_currentEnchants, 13);
		ImGui::PopItemWidth();
	}
	ImGui::EndGroupPanel();		  
}

const char* EnchantBot::GetName() const
{
	return "EnchantBot";
}

std::string EnchantBot::GetRatio(int i, int j)
{
	std::string ratio = std::to_string(i) + "-" + std::to_string(j);
	std::string percentage = "/";
	if (i != 0)
	{
		if (j == 0) {
			percentage = "100%%";
		}
		else if (i == j) {
			percentage = "0%%";
		}
		else
		{
			float x = (1 - (float)j / (float)i) * 100;
			std::string pCalc = Utility::to_string_with_precision<float>(x, 1);
			percentage = pCalc + "%%";
		}
	}
	return ratio + ", " + percentage;
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
	m_currentEnchantItemUID = 0; 
	ResetEnchantList(m_currentEnchants);
}

void EnchantBot::UpdateCheckTime(float elapsedTime)
{
	if (m_enchantCheckTime > 0.0f)
	{
		m_enchantCheckTime -= elapsedTime * 1000;
		if (m_enchantCheckTime < 0.0f) {
			m_enchantCheckTime = 0.0f;
		}
	}

	if (m_internalActionCheckTime > 0.0f)
	{
		m_internalActionCheckTime -= elapsedTime * 1000;
		if (m_internalActionCheckTime < 0.0f) {
			m_internalActionCheckTime = 0.0f;
		}
	}
}

bool EnchantBot::InternalActionCheckTimeReady()
{
	return m_internalActionCheckTime == 0.0f;
}

bool EnchantBot::EnchantCheckTimeReady()
{
	return m_enchantCheckTime == 0.0f;
}

void EnchantBot::ResetInternalActionCheckTime(bool random)
{
	if (random) {
		m_internalActionCheckTime = static_cast<float>(ENCHANTBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION + m_buddy->GetRandInt32(0, 300));
	}
	else {
		m_internalActionCheckTime = static_cast<float>(ENCHANTBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION);
	}
}

void EnchantBot::ResetEnchantCheckTime(bool random)
{
	if (random) {
		m_enchantCheckTime = static_cast<float>(ENCHANTBOT_MIN_TIME_BETWEEN_ENCHANTS + m_buddy->GetRandInt32(0, 700));
	}
	else {
		m_enchantCheckTime = static_cast<float>ENCHANTBOT_MIN_TIME_BETWEEN_ENCHANTS;
	}
}

bool EnchantBot::IsValidEnchantItem(ITEM_BASE* enchantItem)
{
	return (IS_WEAPON(enchantItem->Kind) || enchantItem->Kind == ITEMKIND_DEFENSE);
}

void EnchantBot::SetEnchantItem(UID64_t uid)
{
	if (uid == 0) {
		return;
	}

	m_next_action = EnchantAction::Add_EnchantItem;
	m_enchant_item = OsrItemInfo(uid);
	if (!m_enchant_item.IsArmor() && !m_enchant_item.IsWeapon()) 
	{
		m_currentEnchantItemUID = 0;
		return;
	}  		
	
	m_currentEnchantItemUID = uid;

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

	ResetEnchantList(m_currentEnchants);
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
				AddEnchantToList(EnchantItemType::Accuracy, m_currentEnchants);
				break;
			case static_cast<BYTE>(Desparam::AdvancedQuickFire) :
			case static_cast<BYTE>(Desparam::StandardQuickFire) :
				AddEnchantToList(EnchantItemType::Reattack, m_currentEnchants);
				break;
			case static_cast<BYTE>(Desparam::AdvancedAttack) :
			case static_cast<BYTE>(Desparam::StandardAttack) :
				AddEnchantToList(EnchantItemType::MinMax, m_currentEnchants);
				break;
			case static_cast<BYTE>(Desparam::StandardOverheating) :
				AddEnchantToList(EnchantItemType::Overheating, m_currentEnchants);
				break;
			case static_cast<BYTE>(Desparam::AdvancedRange) :
			case static_cast<BYTE>(Desparam::StandardRange) :
				AddEnchantToList(EnchantItemType::Range, m_currentEnchants);
				break;
			case static_cast<BYTE>(Desparam::AdvancedTime) :
			case static_cast<BYTE>(Desparam::StandardTime) :
				AddEnchantToList(EnchantItemType::Time, m_currentEnchants);
				break;
			case static_cast<BYTE>(Desparam::StandardWeight) :
				AddEnchantToList(EnchantItemType::Weight, m_currentEnchants);
				break;
			case static_cast<BYTE>(Desparam::AdvancedSpeed) :
				AddEnchantToList(EnchantItemType::Speed, m_currentEnchants);
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
				AddEnchantToList(EnchantItemType::Shield, m_currentEnchants);
				break;
			case static_cast<BYTE>(Desparam::Energy) :
				AddEnchantToList(EnchantItemType::Energy, m_currentEnchants);
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
	return;
}
  
void EnchantBot::DrawSettings()
{	
	int wanted_idx = 0;		  
	ImGui::BeginGroupPanel("Wanted Enchants", ImVec2(260, 100));
	{
		ImGui::BeginGroup();
		{
			ImGui::SameLine();
			ImGui::PushItemWidth(110);
			ImGui::EnchantList("##wanted_enchants", &wanted_idx, m_wantedEnchants, 13);
			ImGui::PopItemWidth();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		{
			DrawEnchantButtons();
		}
		ImGui::EndGroup();
	}
	ImGui::EndGroupPanel();
	ImGui::SameLine();	   
	ImGui::BeginGroup();
	{		
		// use e1 prots for e6 and e7
		ImGui::Checkbox("Optimise Enchants", &m_optimiseEnchanting);
		ImGui::Checkbox("Use Chance Cards", &m_withLuckyCard);
		ImGui::Checkbox("Automatic Enchanting", &m_auto_enchant); 	
		if (ImGui::Button("Enchant"))
		{
			if (m_state == EnchantBotState::STANDBY && EnchantCheckTimeReady()) {
				SetEnchantBotState(EnchantBotState::ENCHANT_SINGLE);
			}
		} 	
		ImGui::Dummy(ImVec2(0, 10));
		ImGui::BeginGroupPanel("Run View", ImVec2(200, 100));
		{
			for (int i = 0; i < 6; i++)
			{
				if (i != 5)
				{
					std::string enchstep = "e" + std::to_string(i + 5) + "-" + std::to_string(i + 6) + ":";
					ImGui::Text(enchstep.c_str());
					ImGui::SameLine();
					std::string ratio = GetRatio(m_enchantStats[i][0], m_enchantStats[i][1]);
					ImGui::Text(ratio.c_str());
				}
				else
				{
					std::string enchstep = "e" + std::to_string(i + 5) + ": ";
					ImGui::Text(enchstep.c_str());
					ImGui::SameLine();
					ImGui::Text(std::to_string(m_enchantStats[i][0]).c_str());
				}
			}
		}
		ImGui::EndGroupPanel();
	}
	ImGui::EndGroup();		
}

void EnchantBot::DrawEnchantItemText()
{  
	OSRImGuiMenu::DrawOsrItemName(m_enchant_item);
}

void EnchantBot::DrawEnchantButtons()
{ 
	ImGui::Dummy(ImVec2(0, 5));

	int wantend_enchant_count = m_wantedEnchants.size();	  
					   
	if ((m_currentEnchantItemUID != 0 && m_enchant_item.IsWeapon()) || m_currentEnchantItemUID == 0)
	{
		if (ImGui::Button("Reattack Card", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			AddEnchantToList(EnchantItemType::Reattack, m_wantedEnchants);
		}
		if (ImGui::Button("Accuracy Card", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			AddEnchantToList(EnchantItemType::Accuracy, m_wantedEnchants);
		}
		if (ImGui::Button("Attack Card", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			AddEnchantToList(EnchantItemType::MinMax, m_wantedEnchants);
		}
		if ((m_currentEnchantItemUID != 0 && IS_SECONDARY_WEAPON_1(m_enchant_item.GetItemInfo()->Kind)) || !m_currentEnchantItemUID == 0)
		{
			if (ImGui::Button("Speed Card", ImVec2(100, 20)) && wantend_enchant_count < 13) {
				AddEnchantToList(EnchantItemType::Speed, m_wantedEnchants);
			}
		}		
		
		if (ImGui::Button("Weight Card", ImVec2(100, 20)) && wantend_enchant_count <= 13) {
			AddEnchantToList(EnchantItemType::Weight, m_wantedEnchants);
		}
		if (ImGui::Button("Range Card", ImVec2(100, 20)) && wantend_enchant_count <= 13) {
			AddEnchantToList(EnchantItemType::Range, m_wantedEnchants);
		}
		if (ImGui::Button("Time Card", ImVec2(100, 20)) && wantend_enchant_count <= 13) {
			AddEnchantToList(EnchantItemType::Time, m_wantedEnchants);
		}
		
	}
	else if ((m_currentEnchantItemUID != 0 && m_enchant_item.IsArmor()) || m_currentEnchantItemUID == 0)
	{
		if (ImGui::Button("Shield Card", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			AddEnchantToList(EnchantItemType::Shield, m_wantedEnchants);
		}
		if (ImGui::Button("Energy Card", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			AddEnchantToList(EnchantItemType::Energy, m_wantedEnchants);
		}
		if (ImGui::Button("Energy/Shield Card", ImVec2(100, 20)) && wantend_enchant_count < 13) {
			AddEnchantToList(EnchantItemType::EnergyShield, m_wantedEnchants);
		}
	}  	

	ImGui::Dummy(ImVec2(0, 5));
	if (ImGui::Button("Reset",ImVec2(100, 20))) {
		ResetEnchantList(m_wantedEnchants);
	}
}

void EnchantBot::ResetEnchantList(EnchantListType& enchantlist)
{
	enchantlist.clear();
	AddEnchantToList(EnchantItemType::None, enchantlist);	// dummy enchant
}
	
void EnchantBot::AddEnchantToList(EnchantItemType enchanttype, EnchantListType& enchantlist)
{
	if (enchantlist.size() == 1 && enchantlist[0].first == EnchantItemType::None) {
		enchantlist.clear();
	}

	int enchantnum = enchantlist.size() + 1;
	EnchantTextPair etp;
	etp.first = enchanttype;

	switch (enchanttype)
	{
	case EnchantItemType::Accuracy:
		etp.second = "E:" + std::to_string(enchantnum) + " Accuracy";
		break;
	case EnchantItemType::Reattack:
		etp.second = "E:" + std::to_string(enchantnum) + " Reattack";
		break;
	case EnchantItemType::MinMax:
		etp.second = "E:" + std::to_string(enchantnum) + " Min/Max";
		break;
	case EnchantItemType::Speed:
		etp.second = "E:" + std::to_string(enchantnum) + " Speed";
		break;
	case EnchantItemType::Overheating:
		etp.second = "E:" + std::to_string(enchantnum) + " OVerheat";
		break;
	case EnchantItemType::Range:
		etp.second = "E:" + std::to_string(enchantnum) + " Range";
		break;
	case EnchantItemType::Time:
		etp.second = "E:" + std::to_string(enchantnum) + " Time";
		break;
	case EnchantItemType::Weight:
		etp.second = "E:" + std::to_string(enchantnum) + " Weight";
		break;
	case EnchantItemType::Shield:
		etp.second = "E:" + std::to_string(enchantnum) + " Shield";
		break;
	case EnchantItemType::Energy:
		etp.second = "E:" + std::to_string(enchantnum) + " Energy";
		break;
	case EnchantItemType::EnergyShield:
		etp.second = "E:" + std::to_string(enchantnum) + " Energy/Shield";
		break;
	case EnchantItemType::None:
		etp.second = "None";
		break;
	default:
		break;
	} 	
	enchantlist.push_back(etp);
}

bool EnchantBot::DoEnchantAction(EnchantAction action)
{
	if (!InternalActionCheckTimeReady()) {
		return false;
	}
	else {
		ResetInternalActionCheckTime(true);
	}

	if (m_currentEnchantItemUID == 0) {
		return false;
	}

	if (m_wantedEnchants.size() <= m_enchant_item.GetItemInfo()->m_nEnchantNumber) { // should never happen at this place, but you never know xD
		return false;
	}
		   
	CItemInfo* enchantitem = nullptr;

	// move items to source, step by step
	switch (action)
	{	
	case EnchantAction::Add_EnchantItem:
		// Enchanting should have a minimum time between each complete enchants, independetly from the time between the single enchant actions
		if (!EnchantCheckTimeReady()) {
			return false;
		}
		ResetEnchantCheckTime();
		// first item will be the item to be enchanted
		enchantitem = m_enchant_item.GetItemInfo();
		break;

	case EnchantAction::Add_EnchantCard:
		enchantitem = GetEnchantItemFromInventory(m_wantedEnchants.at(m_enchant_item.GetItemInfo()->m_nEnchantNumber).first, m_enchantTargetKind, OSR_API->GetPlayerGearType());
		break;
	case EnchantAction::Add_ProtectCard: 
		if (m_enchant_item.GetItemInfo()->m_nEnchantNumber < 5) { // no need to add an enchant protect card
			return true;
		}

		if (m_optimiseEnchanting)
		{
			if (m_enchant_item.GetItemInfo()->m_nEnchantNumber == 5 || m_enchant_item.GetItemInfo()->m_nEnchantNumber == 6) {
				enchantitem = GetEnchantItemFromInventory(EnchantItemType::EnchantProtectE1, m_enchantTargetKind, OSR_API->GetPlayerGearType());
			}
			else {
				enchantitem = GetEnchantItemFromInventory(EnchantItemType::EnchantProtectE5, m_enchantTargetKind, OSR_API->GetPlayerGearType());
			}
		}
		else {  			
			enchantitem = GetEnchantItemFromInventory(EnchantItemType::EnchantProtectE5, m_enchantTargetKind, OSR_API->GetPlayerGearType());
		}
		break;
	case EnchantAction::Add_PercentageCard: // next and optional item is an enchant chance card
		if (m_enchant_item.GetItemInfo()->m_nEnchantNumber == 10)
		{
			enchantitem = GetEnchantItemFromInventory(EnchantItemType::EnchantChance8P, m_enchantTargetKind, OSR_API->GetPlayerGearType());
		}
		else {
			return true;
		}
		break;	 
	case EnchantAction::Use_OkButton:
		m_preEnch = m_enchant_item.GetItemInfo()->m_nEnchantNumber;
		OSR_API->OnButtonClick(TO_INT(LabButtonCode::Send));
		m_waiting_for_answer = true;
		return true;
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
		Notify(NotifyType::MISSING_ITEM);
		SetEnchantBotState(EnchantBotState::STANDBY); 	
		return false;
	}  	
}

CItemInfo* EnchantBot::GetEnchantItemFromInventory(EnchantItemType enchantitem, EnchantItemKind itemkind, GearType geartype)
{
	CItemInfo* item = nullptr;

	switch (enchantitem)
	{
	case EnchantItemType::None:
		return nullptr;
	case EnchantItemType::EnchantProtectE1:
		return OSR_API->FindItemInInventoryByItemNum(ItemNumber::BasicItemProtectCard);
	case EnchantItemType::EnchantProtectE5:
		item = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantItemProtectCard);
		if (!item) {
			item = OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantItemProtectCard2);
		}	
		return item;
	case EnchantItemType::EnchantChance3P:
		return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance3PercentCard);
	case EnchantItemType::EnchantChance5P:
		return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance5PercentCard);
	case EnchantItemType::EnchantChance8P:
		return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnchantChance8PercentCard);
	} 

	switch (itemkind)
	{
	case EnchantItemKind::Armor: 		
		switch (enchantitem)
		{
		case EnchantItemType::Shield:
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
		case EnchantItemType::Energy:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnergyCard);
		case EnchantItemType::EnergyShield:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::EnergyShieldCard);
		default:
			return nullptr;
		}
	case EnchantItemKind::Weapon_advanced:
		switch (enchantitem)
		{
		case EnchantItemType::Accuracy:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedProbabilityCard);
		case EnchantItemType::Reattack:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedQuickFireCard);
		case EnchantItemType::MinMax:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedAttackCard);
		case EnchantItemType::Speed:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedSpeedCard);
		case EnchantItemType::Range:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedRangeCard);
		case EnchantItemType::Weight:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::AdvancedWeightCard);
		default:
			return nullptr;
		}
	case EnchantItemKind::Weapon_standard:
		switch (enchantitem)
		{
		case EnchantItemType::Accuracy:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardProbabilityCard);
		case EnchantItemType::Reattack:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardQuickFireCard);
		case EnchantItemType::MinMax:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardAttackCard);
		case EnchantItemType::Overheating:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardOverheatingCard);
		case EnchantItemType::Range:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardRangeCard);
		case EnchantItemType::Time:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardTimeCard);
		case EnchantItemType::Weight:
			return OSR_API->FindItemInInventoryByItemNum(ItemNumber::StandardWeightCard);
		default:
			return nullptr;
		}
	}
	return nullptr;
}



bool EnchantBot::TrySimulateButtonClick(LabButtonCode button)
{
	if (InternalActionCheckTimeReady())
	{
		OSR_API->OnButtonClick(TO_INT(button));
		ResetInternalActionCheckTime(true);
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
}

bool EnchantBot::EnchantFinished()
{
	// check if all the wanted enchants are more or equal to the current enchants
	return TO_INT(m_enchant_item.GetItemInfo()->m_nEnchantNumber) >= m_wantedEnchants.size();
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

void EnchantBot::Notify(NotifyType type)
{
	switch (type)
	{
	case NotifyType::MISSING_ITEM:
		if (m_buddy->NotificationSoundAllowed()) {
			MessageBeep(MB_ICONWARNING);
		}
		if (m_buddy->NotificationPopupAllowed()) {
			MessageBox(0, "Missing items for enchant!", "EnchantBot", MB_SYSTEMMODAL);
		} 		
		break;
	case NotifyType::ENCHANTING_FINISHED:
		if (m_buddy->NotificationSoundAllowed()) {
			MessageBeep(MB_OK);
		}
		if (m_buddy->NotificationPopupAllowed()) {
			MessageBox(0, "Enchanting successfully finished", "EnchantBot", MB_SYSTEMMODAL);
		}
		break;
	default:
		break;
	}
}

FeatureType EnchantBot::GetType() const
{
	return FeatureType::EnchantBot;
}

void EnchantBot::OnEnable()
{
	const BuddyFeatureBase* gambleBot = m_buddy->GetFeatureByType(FeatureType::GambleBot);
	if (gambleBot && gambleBot->IsEnabled())
	{
		MessageBeep(MB_ICONWARNING);
		Enable(false);
	}
}
