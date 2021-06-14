#include "GambleBot.h"

#include "SDK/AtumApplication.h"
#include "OSRBuddy.h"
#include "OSRAPI.h"
#include "OSRBuddyDefine.h"
#include "OSRImGuiMenu.h" 



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
}

GambleBot::~GambleBot()
{

}

void GambleBot::Tick()
{	
	UpdateCheckTime(OSR_API->GetElapsedTime());

	if (!IsEnabled()) {
		return;
	}

	INVEN_DISPLAY_INFO* selected = nullptr;	
	bool character_in_laboratory = (OSR_API->GetCurrentyBuildingKind() == BUILDINGKIND_LABORATORY);
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
				DrawFullWeaponName();
			}
		}
		ImGui::EndGroup();
	

		ImGui::NewLine();

		ImGui::BeginColumns("GambleBotColumns", 2, ImGuiColumnsFlags_NoResize);
		{
			ImGui::SetColumnWidth(0, 430);
			ImGui::BeginChild("KitBotCol1", ImVec2(), false);
			{ 				
				ImGui::Separator();
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
					ImGui::Separator();
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

					ImGui::Checkbox("Automatic Gambling", &m_auto_gamble); 
					if (ImGui::IsItemHovered()) {
						ImGui::SetTooltip("Will keep gambling until fix is found or there are no more gamble items");
					}
					if (ImGui::Button("Gamble"))
					{
						if (m_state == GambleBotState::STANDBY && GambleCheckTimeReady()) {
							SetGambleBotState(GambleBotState::GAMBLING);
						}
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

			ImGui::PushStyleColor(ImGuiCol_Text, OSRImGuiMenu::TranslateAceCharToColor('e').Value);
			ImGui::ComboEx("Prob/Damage", reinterpret_cast<int*>(&m_prefix_selection.ProbDamage), items, 3, -1, false);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Best: Navas, Agareth, Asmodi, Kobal, Warrior\nGood: Navas, Agareth, Asmodi, Kobal, Warrior, Hound, Proson, Aloken, Tobit");
			}
			ImGui::PopStyleColor();

			ImGui::PushStyleColor(ImGuiCol_Text, OSRImGuiMenu::TranslateAceCharToColor('c').Value);
			ImGui::ComboEx("Prob/Reattack", reinterpret_cast<int*>(&m_prefix_selection.ProbReattack), items, 3, -1, false);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Best: Legend, Bio\nGood: Legend, Bio, Attack, Silence, Meteo");
			}
			ImGui::PopStyleColor();

			ImGui::PushStyleColor(ImGuiCol_Text, OSRImGuiMenu::TranslateAceCharToColor('r').Value);
			ImGui::ComboEx("Reattack/Damage", reinterpret_cast<int*>(&m_prefix_selection.ReattackDamage), items, 3, -1, false);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Best: Max, Squire\nGood: Max, Squire, Major, Rukieper");
			}
			ImGui::PopStyleColor();

			ImGui::PushStyleColor(ImGuiCol_Text, OSRImGuiMenu::TranslateAceCharToColor('y').Value);
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

		ImGui::PushStyleColor(ImGuiCol_Text, OSRImGuiMenu::TranslateAceCharToColor('e').Value);	   
		ImGui::ComboEx("Prob/Damage##Suffix", reinterpret_cast<int*>(&m_suffix_selection.ProbDamage), items, 3, -1, false);
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Best: Navas, Agareth, Asmodi, Kobal, Warrior\nGood: Navas, Agareth, Asmodi, Kobal, Warrior, Hound, Proson, Aloken, Tobit");
		}	  
		ImGui::PopStyleColor();

		ImGui::PushStyleColor(ImGuiCol_Text, OSRImGuiMenu::TranslateAceCharToColor('c').Value);
		ImGui::ComboEx("Prob/Reattack##Suffix", reinterpret_cast<int*>(&m_suffix_selection.ProbReattack), items, 3, -1, false);
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Best: Legend, Bio\nGood: Legend, Bio, Attack, Silence, Meteo");
		}
		ImGui::PopStyleColor();

		ImGui::PushStyleColor(ImGuiCol_Text, OSRImGuiMenu::TranslateAceCharToColor('r').Value);
		ImGui::ComboEx("Reattack/Damage##Suffix", reinterpret_cast<int*>(&m_suffix_selection.ReattackDamage), items, 3, -1, false);
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Best: Max, Squire\nGood: Max, Squire, Major, Rukieper");
		}
		ImGui::PopStyleColor();
		ImGui::PopItemWidth();
	}
	ImGui::EndChild(); 
}

void GambleBot::DrawFullWeaponName()
{
	OSRImGuiMenu::DrawOsrItemName(m_gamble_item);
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

	m_is_advanced_weapon = IS_SECONDARY_WEAPON_1(m_gamble_item.GetItemInfo()->Kind);
	m_current_gambleitem_uid = uid;
}

bool GambleBot::TrySimulateButtonClick(LabButtonCode button)
{
	if (InternalActionCheckTimeReady()) 
	{
		OSR_API->OnButtonClick((int)button);
		ResetInternalActionCheckTime(true);
		return true;
	}
	else {
		return false;
	}  	
}

void GambleBot::UpdateCheckTime(float elapsedTime)
{
	if (m_gamble_check_time > 0.0f)
	{
		m_gamble_check_time -= elapsedTime * 1000;
		if (m_gamble_check_time < 0.0f) {
			m_gamble_check_time = 0.0f;
		}
	}

	if (m_internal_action_check_time > 0.0f)
	{
		m_internal_action_check_time -= elapsedTime * 1000;
		if (m_internal_action_check_time < 0.0f) {
			m_internal_action_check_time = 0.0f;
		}
	} 
}

bool GambleBot::GambleCheckTimeReady()
{
	return m_gamble_check_time == 0.0f;
}

bool GambleBot::InternalActionCheckTimeReady()
{
	return m_internal_action_check_time == 0.0f;
}

void GambleBot::ResetGambleCheckTime(bool random)
{	
	if (random) {
		m_gamble_check_time = static_cast<float>(GAMBLEBOT_MIN_TIME_BETWEEN_GAMBLES + m_buddy->GetRandInt32(0, 700));
	}
	else {
		m_gamble_check_time = static_cast<float>GAMBLEBOT_MIN_TIME_BETWEEN_GAMBLES;
	}	
}

void GambleBot::ResetInternalActionCheckTime(bool random)
{
	if (random) {
		m_internal_action_check_time = static_cast<float>(GAMBLEBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION + m_buddy->GetRandInt32(0, 300));
	}
	else {
		m_internal_action_check_time = static_cast<float>GAMBLEBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION;
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
	
	switch ((m_prefix_selection.Any == 0) ? m_prefix_selection.ProbDamage : m_prefix_selection.Any) 
	{
		case FIXSELECTION_ONLY_GOOD:
			if (FixIsInList(prefixcode, g_GoodProbDamagePrefixList, IM_ARRAYSIZE(g_GoodProbDamagePrefixList))) {
				return true;
			}
			break;
		case FIXSELECTION_ONLY_BEST:
			if (FixIsInList(prefixcode, g_BestProbDamagePrefixList, IM_ARRAYSIZE(g_BestProbDamagePrefixList))) {
				return true;
			}
			break;
	}

	switch ((m_prefix_selection.Any == 0) ? m_prefix_selection.Pierce : m_prefix_selection.Any)
	{
	case FIXSELECTION_ONLY_GOOD:
		if (FixIsInList(prefixcode, g_GoodPiercePrefixList, IM_ARRAYSIZE(g_GoodPiercePrefixList))) {
			return true;
		}
		break;
	case FIXSELECTION_ONLY_BEST:
		if (FixIsInList(prefixcode, g_BestPiercePrefixList, IM_ARRAYSIZE(g_BestPiercePrefixList))) {
			return true;
		}
		break;
	}

	switch ((m_prefix_selection.Any == 0) ? m_prefix_selection.ProbReattack : m_prefix_selection.Any)
	{
	case FIXSELECTION_ONLY_GOOD:
		if (FixIsInList(prefixcode, g_GoodProbReattackPrefixList, IM_ARRAYSIZE(g_GoodProbReattackPrefixList))) {
			return true;
		}
		break;
	case FIXSELECTION_ONLY_BEST:
		if (FixIsInList(prefixcode, g_BestProbReattackPrefixList, IM_ARRAYSIZE(g_BestProbReattackPrefixList))) {
			return true;
		}
		break;
	}

	switch ((m_prefix_selection.Any == 0) ? m_prefix_selection.ReattackDamage : m_prefix_selection.Any)
	{
	case FIXSELECTION_ONLY_GOOD:
		if (FixIsInList(prefixcode, g_GoodReattackDamagePrefixList, IM_ARRAYSIZE(g_GoodReattackDamagePrefixList))) {
			return true;
		}
		break;
	case FIXSELECTION_ONLY_BEST:
		if (FixIsInList(prefixcode, g_BestReattackDamagePrefixList, IM_ARRAYSIZE(g_BestReattackDamagePrefixList))) {
			return true;
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

	switch ((m_suffix_selection.Any == 0) ? m_suffix_selection.ProbDamage : m_suffix_selection.Any)
	{
	case FIXSELECTION_ONLY_GOOD:
		if (FixIsInList(suffixcode, g_GoodProbDamageSuffixList, IM_ARRAYSIZE(g_GoodProbDamageSuffixList))) {
			return true;
		}
		break;
	case FIXSELECTION_ONLY_BEST:
		if (FixIsInList(suffixcode, g_BestProbDamageSuffixList, IM_ARRAYSIZE(g_BestProbDamageSuffixList))) {
			return true;
		}
		break;
	}

	switch ((m_suffix_selection.Any == 0) ? m_suffix_selection.ProbReattack : m_suffix_selection.Any)
	{
	case FIXSELECTION_ONLY_GOOD:
		if (FixIsInList(suffixcode, g_GoodProbReattackSuffixList, IM_ARRAYSIZE(g_GoodProbReattackSuffixList))) {
			return true;
		}
		break;
	case FIXSELECTION_ONLY_BEST:
		if (FixIsInList(suffixcode, g_BestProbReattackSuffixList, IM_ARRAYSIZE(g_BestProbReattackSuffixList))) {
			return true;
		}
		break;
	}

	switch ((m_suffix_selection.Any == 0) ? m_suffix_selection.ReattackDamage : m_suffix_selection.Any)
	{
	case FIXSELECTION_ONLY_GOOD:
		if (FixIsInList(suffixcode, g_GoodReattackDamageSuffixList, IM_ARRAYSIZE(g_GoodReattackDamageSuffixList))) {
			return true;
		}
		break;
	case FIXSELECTION_ONLY_BEST:
		if (FixIsInList(suffixcode, g_BestReattackDamageSuffixList, IM_ARRAYSIZE(g_BestReattackDamageSuffixList))) {
			return true;
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
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_ADV_PREFIX_1);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_ADV_PREFIX_2);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		break;

	case GambleItem::SG_ADV_SUFFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_ADV_SUFFIX_1);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_ADV_SUFFIX_2);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		break;

	case GambleItem::SG_STD_PREFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_STD_PREFIX_1);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_STD_PREFIX_2);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		break;

	case GambleItem::SG_STD_SUFFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_STD_SUFFIX_1);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_STD_SUFFIX_2);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		break;

	case GambleItem::INIT_PREFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(INITIALIZATION_PREFIX_1);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		gambleitem = OSR_API->FindItemInInventoryByItemNum(INITIALIZATION_PREFIX_2);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		break;
	case GambleItem::INIT_SUFFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(INITIALIZATION_SUFFIX_1);
		if (gambleitem) {
			amount += gambleitem->CurrentCount;
		}
		gambleitem = OSR_API->FindItemInInventoryByItemNum(INITIALIZATION_SUFFIX_2);
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
	if (!GambleCheckTimeReady()) {
		return false;
	}

	if (!m_needed_source_items.empty())
	{  
		if (!InternalActionCheckTimeReady()) {
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

		ResetInternalActionCheckTime(true);
		return false;
	}
	else
	{
		if (!TrySimulateButtonClick(LabButtonCode::Send)) {
			return false;
		}

		ResetGambleCheckTime(true);
	} 
	
	return true;
}

CItemInfo* GambleBot::FindGambleItemFromInventory(GambleItem gambleitemkind)
{
	CItemInfo* gambleitem = nullptr;

	switch (gambleitemkind)
	{
	case GambleItem::SG_ADV_PREFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_ADV_PREFIX_1);
		if (!gambleitem) {
			gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_ADV_PREFIX_2);
		}
		break;
	case GambleItem::SG_ADV_SUFFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_ADV_SUFFIX_1);
		if (!gambleitem) {
			gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_ADV_SUFFIX_2);
		}
		break;
	case GambleItem::SG_STD_PREFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_STD_PREFIX_1);
		if (!gambleitem) {
			gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_STD_PREFIX_2);
		}
		break;
	case GambleItem::SG_STD_SUFFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_STD_SUFFIX_1);
		if (!gambleitem) {
			gambleitem = OSR_API->FindItemInInventoryByItemNum(SUPERGAMBLE_STD_SUFFIX_2);
		}
		break;
	case GambleItem::INIT_PREFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(INITIALIZATION_PREFIX_1);
		if (!gambleitem) {
			gambleitem = OSR_API->FindItemInInventoryByItemNum(INITIALIZATION_PREFIX_2);
		}
		break;
	case GambleItem::INIT_SUFFIX:
		gambleitem = OSR_API->FindItemInInventoryByItemNum(INITIALIZATION_SUFFIX_1);
		if (!gambleitem) {
			gambleitem = OSR_API->FindItemInInventoryByItemNum(INITIALIZATION_SUFFIX_2);
		}
		break;
	case GambleItem::SOURCE_ITEM:
		gambleitem = m_gamble_item.GetItemInfo();
		break;
	}	

	return gambleitem;
}
   	 
bool GambleBot::FixIsInList(int codenum, const int* fixlist, size_t arraysize)
{
	for (int i = 0; i < arraysize; i++)
	{
		if (codenum == fixlist[i]) {
			return true; 
		} 
	}
	return false;
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
	
	if (add_prefix && add_suffix) 
	{			
		return GambleAction::ADD_PREFIX_AND_SUFFIX;
	}

	if (remove_prefix && remove_suffix)	
	{		
		return GambleAction::REMOVE_PREFIX_AND_SUFFIX;
	}												  

	if (add_prefix && !add_suffix) 
	{	 		
		return GambleAction::ADD_PREFIX;
	}

	if (remove_prefix && !remove_suffix) 
	{		
		return GambleAction::REMOVE_PREFIX;
	}

	if (!add_prefix && add_suffix) 
	{  		
		return GambleAction::ADD_SUFFIX;
	}

	if (!remove_prefix && remove_suffix) 
	{  		
		return GambleAction::REMOVE_SUFFIX;
	}  
	
	if (!remove_prefix && !remove_suffix && !add_prefix && !add_suffix) 
	{	  		
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
	if (TrySimulateButtonClick(LabButtonCode::Cancel))
	{
		SetGambleItem(m_current_gambleitem_uid);
		SetGambleBotState(GambleBotState::STANDBY);
		m_next_gamble_action = DetermineNextAction();
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
