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
	if (GetGambleBotState() != GambleBotState::NOT_IN_LABORATORY && !character_in_laboratory) {
		SetGambleBotState(GambleBotState::NOT_IN_LABORATORY);
		ResetCurrentWeapon();
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
		if (m_selectNewWeapon)
		{
			selected = OSR_API->GetSelectedItem();
			if (selected && selected != m_lastSelectedItem && IS_WEAPON(selected->pItem->Kind)) {
				m_lastSelectedItemInfo = OSR_API->FindItemInInventoryByUniqueNumber(selected->pItem->UniqueNumber);
				SetGambleItem(m_lastSelectedItemInfo);
				m_nextGambleAction = DetermineNextAction();
				m_selectNewWeapon = false;
			}
		}
		break;

	case GambleBotState::GAMBLING:
		if (m_waiting_for_answer) // maybe rework this into recieved packet code
		{
			CItemInfo* targetitem = OSR_API->FindItemFromTarget(m_currentGambleItemUID);
			if (targetitem && TryTargetItemToInventory())
			{
				m_nextGambleAction = DetermineNextAction();
				if (!m_auto_gamble) {
					SetGambleBotState(GambleBotState::STANDBY);
				}
				m_waiting_for_answer = false;
			}
		}
		else if (TryGamble()) {
			m_waiting_for_answer = true;
		}
		break;
	}

}

void GambleBot::RenderImGui()
{			
	if (!DrawEnableCheckBox()) {
		//return;
	}

	/*
	if (ImGui::FancyCheckbox("Active", &m_enabled))
	{ 
		// dont allow the GambleBot to be turned on if the EnchantBot is aktive right now
		if (m_enabled)
		{
			const BuddyFeatureBase* enchantBot = m_buddy->GetFeatureByType(FeatureType::EnchantBot);
			//if (enchantBot && enchantBot->IsActive()) {
			//	m_active = false;
			//}
		}
		// begin drawing in next frame
		return;
	}
	*/
 
	ImGui::Dummy(ImVec2(0.0f, 20.0f));
		    	 

	if (m_state == GambleBotState::NOT_IN_LABORATORY) {
		ImGui::Text("You are not at the laboratory! Bot wont work!");
	}

	ImGui::BeginGroupPanel("Settings", ImVec2(400,400));
	ImGui::Spacing();
	DrawSettings();
	ImGui::Spacing();
	ImGui::EndGroupPanel();
	ImGui::SameLine();

	ImGui::BeginGroup();
	ImGui::BeginGroupPanel("Gambleitems Overview", ImVec2(400, 400));
	ImGui::Spacing();
	ImGui::BeginGroupPanel("Prefix", ImVec2(190, 400));
	ImGui::Text("Supergamble Advanced");
	ImGui::SameLine();
	DrawColoredGambleItemAmount(m_amount_SG_ADV_Prefix);

	ImGui::Text("Supergamble Standard");
	ImGui::SameLine();
	DrawColoredGambleItemAmount(m_amount_SG_STD_Prefix);

	ImGui::Text("Removal cards");
	ImGui::SameLine();
	DrawColoredGambleItemAmount(m_amount_removal_Prefix);
	ImGui::Dummy(ImVec2(0, 3));
	ImGui::EndGroupPanel();	

	ImGui::BeginGroupPanel("Suffix", ImVec2(190, 400));
	ImGui::Text("Supergamble Advanced");
	ImGui::SameLine();
	DrawColoredGambleItemAmount(m_amount_SG_ADV_Suffix);

	ImGui::Text("Supergamble Standard");
	ImGui::SameLine();
	DrawColoredGambleItemAmount(m_amount_SG_STD_Suffix);

	ImGui::Text("Removal cards");
	ImGui::SameLine();
	DrawColoredGambleItemAmount(m_amount_removal_Suffix);
	ImGui::Dummy(ImVec2(0, 3));
	ImGui::EndGroupPanel();
	ImGui::Spacing();
	ImGui::EndGroupPanel();
	   	
	ImGui::BeginGroupPanel("Control", ImVec2(400, 400));   	
	ImGui::Text("Next gamble action:");
	ImGui::SameLine();
	ImGui::Text(GetGambleActionString(m_nextGambleAction));
	ImGui::Spacing();

	ImGui::Checkbox("Automatic", &m_auto_gamble);
	if (ImGui::FancyButton("Gamble"))
	{
		if (m_state == GambleBotState::STANDBY && GambleCheckTimeReady()) {
			SetGambleBotState(GambleBotState::GAMBLING);
		}
	}

	ImGui::Spacing();
	ImGui::EndGroupPanel();
	ImGui::EndGroup();
}

const char* GambleBot::GetName()  const
{
	return  "GambleBot";
}

void GambleBot::DrawSettings()
{  
	ImGui::Text("Gamble Item: ");
	DrawFullWeaponName();

	if (ImGui::FancyButton("Select New")) {
		ResetCurrentWeapon();
		m_selectNewWeapon = true;
	}  	
	const char* items[] = { "None", "Good", "Best" };

	ImGui::BeginGroupPanel("Prefix Options", ImVec2(200, 400));		

	if (ImGui::FancyCheckbox("Gambling active", &m_doPrefixGambleTemp)) 
	{
		if (m_state == GambleBotState::STANDBY) {
			m_nextGambleAction = DetermineNextAction();
		}
	}
	ImGui::Dummy(ImVec2(0, 10));
	ImGui::Text("Stop autogamble at:");	
	ImGui::FancyCheckbox("Any non-green Fix", &m_PrefixSelection.AllNonGreen);
	ImGui::Dummy(ImVec2(0, 10));
	ImGui::PushItemWidth(100);	 	
	ImGui::FancyCombo("Any Fix",			reinterpret_cast<int*>(&m_PrefixSelection.Any), items, 3, -1, false);
	ImGui::FancyCombo("Prob/Damage",		reinterpret_cast<int*>(&m_PrefixSelection.ProbDamage), items, 3, -1, false);
	ImGui::FancyCombo("Prob/Reattack",		reinterpret_cast<int*>(&m_PrefixSelection.ProbReattack), items, 3, -1, false);
	ImGui::FancyCombo("Reattack/Damage",	reinterpret_cast<int*>(&m_PrefixSelection.ReattackDamage), items, 3, -1, false);
	ImGui::FancyCombo("Pierce",				reinterpret_cast<int*>(&m_PrefixSelection.Pierce), items, 3, -1, false);
	ImGui::PopItemWidth();	  
	ImGui::Dummy(ImVec2(0, 3));
	ImGui::EndGroupPanel();

	ImGui::SameLine();

	ImGui::BeginGroupPanel("Suffix Options", ImVec2(200, 400));

	if (ImGui::FancyCheckbox("Gambling active##Suffix", &m_doSuffixGambleTemp)) 
	{
		if (m_state == GambleBotState::STANDBY) {
			DetermineNextAction();
		}
	}
	ImGui::Dummy(ImVec2(0, 10));
	ImGui::Text("Stop autogamble at:");	  
	ImGui::FancyCheckbox("Any non-green Fix##Suffix", &m_SuffixSelection.AllNonGreen);
	ImGui::Dummy(ImVec2(0, 10));
	ImGui::PushItemWidth(100);
	ImGui::FancyCombo("Any Fix##Suffix",			reinterpret_cast<int*>(&m_SuffixSelection.Any), items, 3, -1, false);
	ImGui::FancyCombo("Prob/Damage##Suffix",		reinterpret_cast<int*>(&m_SuffixSelection.ProbDamage), items, 3, -1, false);
	ImGui::FancyCombo("Prob/Reattack##Suffix",		reinterpret_cast<int*>(&m_SuffixSelection.ProbReattack), items, 3, -1, false);
	ImGui::FancyCombo("Reattack/Damage##Suffix",	reinterpret_cast<int*>(&m_SuffixSelection.ReattackDamage), items, 3, -1, false);
	ImGui::PopItemWidth(); 
	ImGui::Dummy(ImVec2(0, 3));
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel("When selected Fix has been found", ImVec2(400, 0));
	ImGui::FancyCheckbox("Play sound", &m_notfiySound);
	ImGui::FancyCheckbox("Messagebox", &m_notfiyMB);
	ImGui::Dummy(ImVec2(0, 3));
	ImGui::EndGroupPanel();	  
}

void GambleBot::DrawFullWeaponName()
{
	if (!m_currentGambleItem) {
		if (m_selectNewWeapon) {
			ImGui::Text("waiting for selection...");
		}
		return;
	}

	if (!m_prefixName.empty()) {
		ImGui::PushStyleColor(ImGuiCol_Text, m_prefixColor.Value);
		ImGui::Text(m_prefixName.c_str());
		ImGui::SameLine();
		ImGui::PopStyleColor();
	}

	ImGui::Text(m_weaponName.c_str());

	if (!m_suffixName.empty()) {
		ImGui::PushStyleColor(ImGuiCol_Text, m_suffixColor.Value);
		ImGui::SameLine();
		ImGui::Text(m_suffixName.c_str()); 		
		ImGui::PopStyleColor();
	}	
}

void GambleBot::DrawColoredGambleItemAmount(int amount)
{
	if (amount >= 100) 
	{
		ImGui::PushStyleColor(ImGuiCol_Text, COLOR_GAMBLEITEM_GT_100);
		ImGui::SameLine();
		ImGui::Text(std::to_string(amount).c_str());
		ImGui::PopStyleColor();
		
	}
	else if (amount > 0 && amount < 100) 
	{
		ImGui::PushStyleColor(ImGuiCol_Text, COLOR_GAMBLEITEM_LT_100);
		ImGui::SameLine();
		ImGui::Text(std::to_string(amount).c_str());
		ImGui::PopStyleColor();
	}
	else if (amount == 0) 
	{
		ImGui::PushStyleColor(ImGuiCol_Text, COLOR_GAMBLEITEM_EQ_0);
		ImGui::SameLine();
		ImGui::Text(std::to_string(amount).c_str());
		ImGui::PopStyleColor();
	}
}
  						 
void GambleBot::SetGambleBotState(GambleBotState state)
{	 
	m_state = state;
}

GambleBotState GambleBot::GetGambleBotState()
{
	return m_state;
}

void GambleBot::ReturnToPreviousGambleBotState()
{
	GambleBotState buf = m_state;
	m_state = m_prev_state;
	m_prev_state = buf;
}

void GambleBot::SetGambleItem(CItemInfo* gambleItem)
{	
	if (gambleItem) 
	{
		if (!IS_WEAPON(gambleItem->Kind)) {
			return;
		}

		m_isAdvancedWeapon = IS_SECONDARY_WEAPON_1(gambleItem->m_pItemInfo->Kind);

		m_currentGambleItem = gambleItem;
		m_currentGambleItemUID = gambleItem->UniqueNumber;
		m_weaponName = std::string(gambleItem->m_pItemInfo->ItemName);

		// determine the prefix and suffix colors
		if (gambleItem->m_pRefPrefixRareInfo)
		{
			m_prefixName = std::string(gambleItem->m_pRefPrefixRareInfo->Name);

			if (gambleItem->m_pRefPrefixRareInfo->Name[0] == '\\')  // check if prefix has a colorcode in its name
			{
				m_prefixColor = OSRImGuiMenu::TranslateAceCharToColor(gambleItem->m_pRefPrefixRareInfo->Name[1]); 			
				m_prefixName.erase(m_prefixName.begin(), m_prefixName.begin() + 2);
				m_prefixName.erase(m_prefixName.end() - 2, m_prefixName.end());
			} 
			else
			{
				m_prefixColor = OSRImGuiMenu::TranslateAceCharToColor('g');
			}

			m_prefixName += " (" + std::to_string(gambleItem->m_pRefPrefixRareInfo->CodeNum) + ")";
		}
		else {
			m_prefixName.clear();
		}

		if (gambleItem->m_pRefSuffixRareInfo)
		{
			m_suffixName = std::string(gambleItem->m_pRefSuffixRareInfo->Name);

			if (gambleItem->m_pRefSuffixRareInfo->Name[0] == '\\')  // check if prefix has a colorcode in its name
			{
				m_suffixColor = OSRImGuiMenu::TranslateAceCharToColor(gambleItem->m_pRefSuffixRareInfo->Name[1]);
				m_suffixName.erase(m_suffixName.begin(), m_suffixName.begin() + 2);
				m_suffixName.erase(m_suffixName.end() - 2, m_suffixName.end());
			}
			else
			{
				m_suffixColor = OSRImGuiMenu::TranslateAceCharToColor('g');
			}

			m_suffixName += " (" + std::to_string(gambleItem->m_pRefSuffixRareInfo->CodeNum) + ")";
		}
		else {
			m_suffixName.clear();
		}

	}
	else 
	{
		ResetCurrentWeapon();
	}
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
	if (m_gambleCheckTime > 0.0f)
	{
		m_gambleCheckTime -= elapsedTime * 1000;
		if (m_gambleCheckTime < 0.0f) {
			m_gambleCheckTime = 0.0f;
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

bool GambleBot::GambleCheckTimeReady()
{
	return m_gambleCheckTime == 0.0f;
}

bool GambleBot::InternalActionCheckTimeReady()
{
	return m_internalActionCheckTime == 0.0f;
}

void GambleBot::ResetGambleCheckTime(bool random = true)
{	
	if (random) {
		m_gambleCheckTime = static_cast<float>(GAMBLEBOT_MIN_TIME_BETWEEN_GAMBLES + m_buddy->GetRandInt32(0, 700));
	}
	else {
		m_gambleCheckTime = static_cast<float>GAMBLEBOT_MIN_TIME_BETWEEN_GAMBLES;
	}	
}

void GambleBot::ResetInternalActionCheckTime(bool random = true)
{
	if (random) {
		m_internalActionCheckTime = static_cast<float>(GAMBLEBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION + m_buddy->GetRandInt32(0, 300));
	}
	else {
		m_internalActionCheckTime = static_cast<float>GAMBLEBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION;
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
	
	if (m_PrefixSelection.AllNonGreen && weapon->m_pRefPrefixRareInfo->Name[0] == '\\') {
		return true;
	}

	int prefixcode = weapon->m_pRefPrefixRareInfo->CodeNum;
	
	switch ((m_PrefixSelection.Any == 0) ? m_PrefixSelection.ProbDamage : m_PrefixSelection.Any) 
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

	switch ((m_PrefixSelection.Any == 0) ? m_PrefixSelection.Pierce : m_PrefixSelection.Any)
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

	switch ((m_PrefixSelection.Any == 0) ? m_PrefixSelection.ProbReattack : m_PrefixSelection.Any)
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

	switch ((m_PrefixSelection.Any == 0) ? m_PrefixSelection.ReattackDamage : m_PrefixSelection.Any)
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


	if (m_SuffixSelection.AllNonGreen && weapon->m_pRefSuffixRareInfo->Name[0] == '\\') {
		return true;
	}

	int suffixcode = weapon->m_pRefSuffixRareInfo->CodeNum;

	switch ((m_SuffixSelection.Any == 0) ? m_SuffixSelection.ProbDamage : m_SuffixSelection.Any)
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

	switch ((m_SuffixSelection.Any == 0) ? m_SuffixSelection.ProbReattack : m_SuffixSelection.Any)
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

	switch ((m_SuffixSelection.Any == 0) ? m_SuffixSelection.ReattackDamage : m_SuffixSelection.Any)
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

void GambleBot::ResetCurrentWeapon()
{  	
	m_currentGambleItem = nullptr;
	m_currentGambleItemUID = 0;
	m_prefixName.clear();
	m_suffixName.clear();
	m_weaponName.clear();
	m_prefixColor = { 0,0,0,0 };
	m_suffixColor = { 0,0,0,0 };
}

// executed after gambling action finished
bool GambleBot::TryTargetItemToInventory()
{	
	// wait until we could simulate the button to transfer the results into the inventory
   	if (!TrySimulateButtonClick(LabButtonCode::Ok)) {
		return false;
	}

	// item should be in inventory now
	CItemInfo* item = OSR_API->FindItemInInventoryByUniqueNumber(m_currentGambleItemUID);
	if (item)
	{
		SetGambleItem(item);
		m_nextActionPrepare = 0;

		// m_nextGambleAction is the action that was just done
		GambleAction current_action = m_nextGambleAction;
		 		
		switch (current_action)
		{
		case GambleAction::ADD_PREFIX:
			if (CheckRarePrefix(item)) 
			{
				m_doPrefixGamble = false;
				m_doPrefixGambleTemp = false;
				Notify();
			}
			break;
		case GambleAction::ADD_SUFFIX:
			if (CheckRareSuffix(item))
			{ 
				m_doSuffixGamble = false;
				m_doSuffixGambleTemp = false;
				Notify();
			}
			break;
		case GambleAction::ADD_PREFIX_AND_SUFFIX:
			if (CheckRarePrefix(item))
			{
				m_doPrefixGamble = false;
				m_doPrefixGambleTemp = false;
				Notify();
			}
			if (CheckRareSuffix(item))
			{
				m_doSuffixGamble = false;
				m_doSuffixGambleTemp = false;
				Notify();
			}
			break;	
		}
	}
	else
	{
		// should never happen
	}
	return true;
 }

bool GambleBot::TryGamble()
{
	if (!GambleCheckTimeReady()) {
		return false;
	} 

	if (m_nextGambleAction == GambleAction::NONE) {
		return false;
	}

	if (m_nextActionPrepare < m_actionsToPrepareCount)
	{
		if (PrepareNextGamble()) {
			m_nextActionPrepare++;
		}
		return false;
	}			
	
	if (!TrySimulateButtonClick(LabButtonCode::Send)) {
		return false;
	}

	ResetGambleCheckTime(true);
	return true;
}

CItemInfo* GambleBot::FindGambleCardItemFromInventory(GambleItem gambleitemkind)
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
	}	

	return gambleitem;
}

void GambleBot::Notify()
{
	if (m_notfiySound) {
		MessageBeep(MB_OK);
	}
	
	if (m_notfiyMB) {
		MessageBox(0, "Fix has been found!", "GambleBot", MB_SYSTEMMODAL);
	}	
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

bool GambleBot::PrepareNextGamble()
{ 	
	if (!InternalActionCheckTimeReady()) {
		return false;
	}
	else {
		ResetInternalActionCheckTime(true);
	}

	if (!m_currentGambleItem) {
		return false;
	}

	if (m_nextActionPrepare == 0)
	{
		OSR_API->InvenToSourceItem(m_currentGambleItem, 1, false);
		return true;
	} 
	
	CItemInfo* prefixitem = nullptr;
	CItemInfo* suffixitem = nullptr;

	switch (m_nextGambleAction) {
	case GambleAction::NONE:
		return false;

	case GambleAction::ADD_PREFIX:		
		prefixitem = (m_isAdvancedWeapon) ? FindGambleCardItemFromInventory(GambleItem::SG_ADV_PREFIX) : FindGambleCardItemFromInventory(GambleItem::SG_STD_PREFIX);
		if (!prefixitem) 
		{
			Reset();
			SetGambleBotState(GambleBotState::STANDBY);
			return false;	// item not found
		}

		if (m_nextActionPrepare == 1) {
			OSR_API->InvenToSourceItem(prefixitem, 1, false);
			return true;
		}		
		break;

	case GambleAction::ADD_SUFFIX:
		suffixitem = (m_isAdvancedWeapon) ? FindGambleCardItemFromInventory(GambleItem::SG_ADV_SUFFIX) : FindGambleCardItemFromInventory(GambleItem::SG_STD_SUFFIX);
		if (!suffixitem) 
		{
			Reset();
			SetGambleBotState(GambleBotState::STANDBY);
			return false;  // item not found
		}
		if (m_nextActionPrepare == 1) {
			OSR_API->InvenToSourceItem(suffixitem, 1, false);
			return true;
		}
		break;

	case GambleAction::ADD_PREFIX_AND_SUFFIX:
		prefixitem = (m_isAdvancedWeapon) ? FindGambleCardItemFromInventory(GambleItem::SG_ADV_PREFIX) : FindGambleCardItemFromInventory(GambleItem::SG_STD_PREFIX);
		suffixitem = (m_isAdvancedWeapon) ? FindGambleCardItemFromInventory(GambleItem::SG_ADV_SUFFIX) : FindGambleCardItemFromInventory(GambleItem::SG_STD_SUFFIX);
		if (!prefixitem || !suffixitem) 
		{
			Reset();
			SetGambleBotState(GambleBotState::STANDBY);
			return false;	// item not found
		}
		if (m_nextActionPrepare == 1) {
			OSR_API->InvenToSourceItem(prefixitem, 1, false);
			return true;
		}
		if (m_nextActionPrepare == 2) {
			OSR_API->InvenToSourceItem(suffixitem, 1, false);
			return true;
		}
		break;

	case GambleAction::REMOVE_PREFIX:
		prefixitem = FindGambleCardItemFromInventory(GambleItem::INIT_PREFIX);
		if (!prefixitem) 
		{
			Reset();
			SetGambleBotState(GambleBotState::STANDBY);
			return false;	// item not found
		}
		if (m_nextActionPrepare == 1) {
			OSR_API->InvenToSourceItem(prefixitem, 1, false);
			return true;
		}
		break;

	case GambleAction::REMOVE_SUFFIX:
		suffixitem = FindGambleCardItemFromInventory(GambleItem::INIT_SUFFIX);
		if (!suffixitem) 
		{
			Reset();
			SetGambleBotState(GambleBotState::STANDBY);
			return false;  // item not found
		}
		if (m_nextActionPrepare == 1) {
			OSR_API->InvenToSourceItem(suffixitem, 1, false);
			return true;
		}
		break;

	case GambleAction::REMOVE_PREFIX_AND_SUFFIX:
		prefixitem = FindGambleCardItemFromInventory(GambleItem::INIT_PREFIX);
		suffixitem = FindGambleCardItemFromInventory(GambleItem::INIT_SUFFIX);
		if (!prefixitem || !suffixitem) 
		{
			Reset();
			SetGambleBotState(GambleBotState::STANDBY);
			return false;	// item not found
		}
		if (m_nextActionPrepare == 1)
		{
			OSR_API->InvenToSourceItem(prefixitem, 1, false);
			return true;
		}
		if (m_nextActionPrepare == 2) 
		{
			OSR_API->InvenToSourceItem(suffixitem, 1, false);
			return true;
		}
		break;
	}
}

GambleAction GambleBot::DetermineNextAction()
{
	UpdateTotalGambleItemAmount();

	m_doPrefixGamble = m_doPrefixGambleTemp;
	m_doSuffixGamble = m_doSuffixGambleTemp;

	m_actionsToPrepareCount = 0;

	if (!m_currentGambleItem) {
		return GambleAction::NONE;
	}

	if (!m_doPrefixGamble && !m_doSuffixGamble) {
		return GambleAction::NONE;
	}

	bool remove_prefix = false;
	bool remove_suffix = false;
	bool add_prefix = false;
	bool add_suffix = false;

	if (m_doPrefixGamble)
	{
		// Check if we need to remove prefix first
		if (m_currentGambleItem->m_pRefPrefixRareInfo) 
		{
			if (m_amount_removal_Prefix > 0) {
				remove_prefix = true;
			}
			else  // missing gamble items
			{
				remove_prefix = false;
				m_doPrefixGamble = false;
				m_doPrefixGambleTemp = false;
			} 			
		}

		if (!m_currentGambleItem->m_pRefPrefixRareInfo) 
		{
			if ((m_isAdvancedWeapon) ? m_amount_SG_ADV_Prefix > 0 : m_amount_SG_STD_Prefix > 0) {
				add_prefix = true;
			}
			else  // missing gamble items
			{
				add_prefix = false;
				m_doPrefixGamble = false;
				m_doPrefixGambleTemp = false;
			} 			
		} 		
	}

	if (m_doSuffixGamble)
	{
		// Check if we need to remove prefix first
		if (m_currentGambleItem->m_pRefSuffixRareInfo) 
		{
			if (m_amount_removal_Suffix > 0) {
				remove_suffix = true;
			}
			else  // missing gamble items
			{	
				remove_suffix = false;
				m_doSuffixGamble = false;
				m_doSuffixGambleTemp = false;
			}
		}

		if (!m_currentGambleItem->m_pRefSuffixRareInfo) 
		{
			if ((m_isAdvancedWeapon) ? m_amount_SG_ADV_Suffix > 0 : m_amount_SG_STD_Suffix > 0)	{
				add_suffix = true;
			}
			else  // missing gamble items
			{	
				add_suffix = false;
				m_doSuffixGamble = false;
				m_doSuffixGambleTemp = false;
			}			
		}
	}
	
	if (add_prefix && add_suffix) 
	{			
		m_actionsToPrepareCount = 3;
		return GambleAction::ADD_PREFIX_AND_SUFFIX;
	}

	if (remove_prefix && remove_suffix)	
	{		
		m_actionsToPrepareCount = 3;
		return GambleAction::REMOVE_PREFIX_AND_SUFFIX;
	}												  

	if (add_prefix && !add_suffix) 
	{	 		
		m_actionsToPrepareCount = 2;
		return GambleAction::ADD_PREFIX;
	}

	if (remove_prefix && !remove_suffix) 
	{		
		m_actionsToPrepareCount = 2;
		return GambleAction::REMOVE_PREFIX;
	}

	if (!add_prefix && add_suffix) 
	{  		
		m_actionsToPrepareCount = 2;
		return GambleAction::ADD_SUFFIX;
	}

	if (!remove_prefix && remove_suffix) 
	{  		
		m_actionsToPrepareCount = 2;
		return GambleAction::REMOVE_SUFFIX;
	}  
	
	if (!remove_prefix && !remove_suffix && !add_prefix && !add_suffix) 
	{	  		
		m_actionsToPrepareCount = 0;
		return GambleAction::NONE;
	}

	return GambleAction::NONE;
}

void GambleBot::Reset()
{
	if (TrySimulateButtonClick(LabButtonCode::Cancel))
	{
		m_nextActionPrepare = 0;
		SetGambleItem(OSR_API->FindItemInInventoryByUniqueNumber(m_currentGambleItemUID));
		SetGambleBotState(GambleBotState::STANDBY);
		DetermineNextAction();
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
