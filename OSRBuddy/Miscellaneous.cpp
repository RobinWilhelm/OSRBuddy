#include "osrb_pch.h"
#include "Miscellaneous.h"

#include "imgui/imgui.h"

#include "OSRAPI.h"
#include "OSRBuddy.h"
#include "IOPacketManager.h"
#include "VMTHook.h"
#include "PatternManager.h"

#include "SDK/AtumApplication.h"
#include "SDK/WeaponMissleData.h"
#include "SDK/WeaponRocketData.h"


#define WHISPER_WARNING_TIME 10s
#define WHISPER_SNOOZE_TIME 2min		  
   
#define AUTO_ITEM_REATTACK 400ms
#define BOSS_CHECK_REATTACK 1s
#define UPDATE_CHARM_COMBO_REATTACK 250ms


namespace Features
{
	static Miscellaneous* g_pMiscellaneous = nullptr;
	static std::unordered_map<INT, bool> rollingEnemies;

	Miscellaneous::Miscellaneous(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
	{
		g_pMiscellaneous = this;

		m_whisperwarner_active = false;
		m_whisperwarner_snooze_enabled = true;
		m_whisper_popup_open = false;

		m_autocharms_active = false;
		m_combo_items.clear();

		m_use_ammobox = false;
		m_use_stealthcard = false;
		m_use_rabbit = false;

		m_awaiting_server_ok_ammobox = false;
		m_awaiting_server_ok_rabbit = false;
		m_awaiting_server_ok_stealthcard = false;

		m_autoflip = false;
		m_bosswarner = false;
		m_boss_popup_open = false;
		m_enemy_hit_in_roll = false;
		//m_cant_evade_missles = false;


		m_bosscheck_timer = BuddyTimer(BOSS_CHECK_REATTACK);
		m_autoitems_timer = BuddyTimer(AUTO_ITEM_REATTACK);
		m_update_charms_timer = BuddyTimer(UPDATE_CHARM_COMBO_REATTACK);
		m_selected_combo_item = ImGui::ComboItem();

		m_searcheye_timer = BuddyTimer(3s);
		m_gm_timer = BuddyTimer(1s);

		m_vkc_toggle = 226; // <
		m_vkc_description = Utility::VirtualKeyCodeToString(m_vkc_toggle);
		m_wait_for_hotkey = false;

		InitHooks();
	}

	Miscellaneous::~Miscellaneous()
	{
		ShutdownHooks();
	}

	FeatureType Miscellaneous::GetType() const
	{
		return FeatureType::Miscellaneous;
	}

	std::string Miscellaneous::GetName() const
	{
		return "Misc";
	}

	void Miscellaneous::Tick()
	{
		if (!IsEnabled()) {
			return;
		}

		TickAutoFlip();
		TickWhisperWarner();
		TickBossWarner();
		TickGMWarner();
		TickNoOverheat();

		if (m_autoitems_timer.IsReady())
		{
			TickAutoStealthcard();
			TickAutoAmmo();
			TickAutoRabbit();
			TickAutoCharm();
			TickVisibility();
			m_autoitems_timer.Reset();
		}
	}

	void Miscellaneous::RenderImGui()
	{
		DrawEnableCheckBox();
		ImGui::NewLine();

		ImGui::BeginColumns("MiscColumns", 2, ImGuiColumnsFlags_NoResize);
		{
			ImGui::BeginChild("MiscColumn1", ImVec2(), false);
			{
				ImGui::Separator();
				ImGui::BeginDisabledMode(OSR_API->GetPlayerGearType() != GearType::AGear);
				{
					ImGui::Checkbox("Autoflip", &m_autoflip);
				}
				ImGui::EndDisabledMode();
				ImGui::Checkbox("Boss Warner", &m_bosswarner);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Will notify player when a boss is present in the area.");
				}
				ImGui::Checkbox("Auto Ammobox", &m_use_ammobox);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Automatic refill of ammunition when empty.");
				}
				ImGui::Checkbox("Auto Stealthcards", &m_use_stealthcard);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Makes sure you always have a stealthcard active.");
				}
				ImGui::Checkbox("Auto Rabbits", &m_use_rabbit);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Automatic use of rabbit necklaces.");
				}
				ImGui::Checkbox("Auto Search Eyes (experimental)", &m_use_searcheye);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Automatic use of search eyes.");
				}
				ImGui::Checkbox("Force Visiblity (experimental)", &m_force_visibility);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Forces all enemy players and staff members to be visible to you.");
				}
				ImGui::Checkbox("No Primary Weapon Overheat", &m_no_overheat_primary);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Your primary weapon wont overheat.");
				}
				ImGui::Checkbox("No Booster Overheat", &m_no_overheat_booster);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Endless boosting.");
				}
				/*
				ImGui::Checkbox("Enemys cant evade missles", &m_cant_evade_missles);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Missles will retarget enemies after they rolled");
				}
				*/
				ImGui::NewLine();
				ImGui::Separator();

				ImGui::Checkbox("Hit Enemys in Roll", &m_enemy_hit_in_roll);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Enemy rolls will be useless.");
				}

				ImGui::Text("Start / Stop hotkey:");
				ImGui::SameLine();
				if (!m_wait_for_hotkey)
				{
					ImGui::Text(m_vkc_description.c_str());
					ImGui::SameLine();
					if (ImGui::Button("Select New"))
					{
						m_wait_for_hotkey = true;
					}
				}
				else
				{
					ImGui::Text("Waiting for keypress...");
				}


				ImGui::NewLine();
				ImGui::Separator();

				CShuttleChild* shuttleChild = OSR_API->GetAtumApplication()->m_pShuttleChild;
				ImGui::SliderFloat("Primary reattack", &shuttleChild->m_paramFactor.pfm_REATTACKTIME_01, -1, 1, "%.2f");
				ImGui::SliderFloat("Secondary reattack", &shuttleChild->m_paramFactor.pfm_REATTACKTIME_02, -1, 1, "%.2f");
			}

			ImGui::EndChild();
		}
		ImGui::NextColumn();
		{
			ImGui::BeginChild("MiscColumn2", ImVec2(), false);
			{
				ImGui::Separator();
				ImGui::Text("Whisperwarner");
				ImGui::Separator();
				ImGui::Checkbox("Active###whisperwarner", &m_whisperwarner_active);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Will notify the user whenever there is a new / unread whisper message.");
				}
				ImGui::Checkbox("Snooze enabled", &m_whisperwarner_snooze_enabled);
				ImGui::Checkbox("Close all features when getting whispered.", &m_whisperwarner_closeall);

				ImGui::NewLine();
				ImGui::Separator();
				ImGui::Text("Auto Charms");
				ImGui::Separator();
				ImGui::Checkbox("Active###charms", &m_autocharms_active);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Will automatically use the selected charm.");
				}
				if (ImGui::VectorCombo("Select charm:", m_combo_items, m_selected_combo_item, ImGuiComboFlags_None))
				{
					if (m_update_charms_timer.IsReady())
					{
						UpdateCharmsComboBox();
						m_update_charms_timer.Reset();
					}
				}

				ImGui::NewLine();
				ImGui::Separator();
				ImGui::Text("GM Warner (experimental)");
				ImGui::Separator();
				ImGui::Checkbox("Active###GMwarner", &m_gmwarner_active);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Will try to detect online Staff members and show them in a list below.\nIMPORTANT: Only works as a formation lead.");
				}
				ImGui::Text("Detected Staff Members:");
				uint64_t fiveMinutesAgo = GetTickCount64() - 1000 * 60 * 5;
				for (auto gm : m_online_gms)
				{
					if(gm.second > fiveMinutesAgo)
						ImGui::Text("%s", gm.first.c_str());
				}

				ImGui::SameLine();
			}
			ImGui::EndChild();
		}
		ImGui::EndColumns();
	}

	bool Miscellaneous::OnReadPacket(unsigned short msgtype, byte* packet)
	{
		switch (msgtype)
		{
		case T_IC_PARTY_RECOMMENDATION_MEMBER_OK:	// 추천 인원
		{
			MSG_IC_PARTY_RECOMMENDATION_MEMBER_OK* pMsg = (MSG_IC_PARTY_RECOMMENDATION_MEMBER_OK*)packet;
			SRECOMMENDATION_MEMBER_INFO* pListInfo = (SRECOMMENDATION_MEMBER_INFO*)((char*)pMsg + sizeof(MSG_IC_PARTY_RECOMMENDATION_MEMBER_OK));
			int i;
			for (i = 0; i < pMsg->Count; i++)
			{
				if (OSR_API->IsStaffMember(pListInfo->CharacterName))
				{
					m_online_gms[std::string(pListInfo->CharacterName, strlen(pListInfo->CharacterName))] = GetTickCount64();
				}
				pListInfo++;
			}
		}
		}
		return false;
	}

	int Miscellaneous::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_KEYUP:
			if (m_wait_for_hotkey)
			{
				m_vkc_toggle = TO_UINT(wParam);
				m_vkc_description = Utility::VirtualKeyCodeToString(m_vkc_toggle);
				m_wait_for_hotkey = false;
			}
			else
			{
				if (TO_UINT(wParam) == m_vkc_toggle /* && !m_buddy->GetMenu()->IsOpen()*/)
				{
					m_enemy_hit_in_roll = !m_enemy_hit_in_roll;
					return 1;
				}
			}
		}
		return 0;
	}

	void Miscellaneous::ActivateAutoFlip(bool on)
	{
		m_autoflip = on;
	}

	void Miscellaneous::ActivateAutoAmmo(bool on)
	{
		m_use_ammobox = on;
	}

	void Miscellaneous::ActivateAutoStealthcard(bool on)
	{
		m_use_stealthcard = on;
	}

	void Miscellaneous::UpdateCharmsComboBox()
	{
		CStoreData* storedata = OSR_API->GetAtumApplication()->m_pShuttleChild->m_pStoreData;
		if (!storedata) {
			return;
		}

		m_combo_items.clear();
		CMapItemInventoryIterator it = storedata->m_mapItemUniqueNumber.begin();
		while (it != storedata->m_mapItemUniqueNumber.end())
		{
			if (it->second->m_pItemInfo->Kind == ITEMKIND_ACCESSORY_TIMELIMIT)
			{
				if (!CheckCharmItemIsAvailable(it->second->ItemNum))
				{
					ImGui::ComboItem citem(it->second->ItemNum, it->second->ItemInfo->ItemName, SIZE_MAX_ITEM_NAME);
					m_combo_items.push_back(citem);
				}
			}
			it++;
		}
	}

	bool Miscellaneous::CheckCharmItemIsAvailable(uint32_t itemnumber)
	{
		for (auto& item : m_combo_items)
		{
			if (item.GetKey() == itemnumber) {
				return true;
			}
		}
		return false;
	}

	bool Miscellaneous::InitHooks()
	{
		/*
		if (m_OnSendFieldSocketBattleAttackEvasionhook) {
			return false;
		}

		PatternInfo pinfo = PatternManager::Get(OffsetIdentifier::CWSlowData__SendFieldSocketBattleAttackEvasion);
		m_OnSendFieldSocketBattleAttackEvasionhook = std::make_unique<TrampolineHook<SendFieldSocketBattleAttackEvasionType>>(pinfo.address, (byte*)Miscellaneous::OnSendFieldSocketBattleAttackEvasion_Hooked, pinfo.trampoline_length);

		m_orig_OnSendFieldSocketBattleAttackEvasionMessage = m_OnSendFieldSocketBattleAttackEvasionhook->GetOriginal();
		if (!m_OnSendFieldSocketBattleAttackEvasionhook->Hook()) {
			return false;
		}
		*/

		if (m_OnMissleCheckWeaponCollisionhook) {
			return false;
		}

		PatternInfo pinfo = PatternManager::Get(OffsetIdentifier::CWeaponMissileData__CheckWeaponCollision);
		m_OnMissleCheckWeaponCollisionhook = std::make_unique<TrampolineHook<CheckWeaponCollisionType>>(pinfo.address, (byte*)Miscellaneous::OnMissileCheckWeaponCollision_Hooked, pinfo.trampoline_length);

		m_orig_OnMissleCheckWeaponCollisionMessage = m_OnMissleCheckWeaponCollisionhook->GetOriginal();
		if (!m_OnMissleCheckWeaponCollisionhook->Hook()) {
			return false;
		}

		if (m_OnRocketCheckWeaponCollisionhook) {
			return false;
		}

		pinfo = PatternManager::Get(OffsetIdentifier::CWeaponRocketData__CheckWeaponCollision);
		m_OnRocketCheckWeaponCollisionhook = std::make_unique<TrampolineHook<CheckWeaponCollisionType>>(pinfo.address, (byte*)Miscellaneous::OnRocketCheckWeaponCollision_Hooked, pinfo.trampoline_length);

		m_orig_OnRocketCheckWeaponCollisionMessage = m_OnRocketCheckWeaponCollisionhook->GetOriginal();
		if (!m_OnRocketCheckWeaponCollisionhook->Hook()) {
			return false;
		}

		if (m_OnCheckTargetByBombhook) {
			return false;
		}

		pinfo = PatternManager::Get(OffsetIdentifier::CWeaponMissileData__CheckTargetByBomb);
		m_OnCheckTargetByBombhook = std::make_unique<TrampolineHook<CheckTargetByBombType>>(pinfo.address, (byte*)Miscellaneous::OnCheckTargetByBomb_Hooked, pinfo.trampoline_length);

		m_orig_OnCheckTargetByBombMessage = m_OnCheckTargetByBombhook->GetOriginal();
		if (!m_OnCheckTargetByBombhook->Hook()) {
			return false;
		}

		return true;
	}

	void Miscellaneous::ShutdownHooks()
	{
		/*
		if (m_OnSendFieldSocketBattleAttackEvasionhook)
		{
			m_OnSendFieldSocketBattleAttackEvasionhook->Unhook();
			Sleep(100);
			m_OnSendFieldSocketBattleAttackEvasionhook.reset();
		}
		*/

		if (m_OnMissleCheckWeaponCollisionhook)
		{
			m_OnMissleCheckWeaponCollisionhook->Unhook();
			Sleep(100);
			m_OnMissleCheckWeaponCollisionhook.reset();
		}

		if (m_OnRocketCheckWeaponCollisionhook)
		{
			m_OnRocketCheckWeaponCollisionhook->Unhook();
			Sleep(100);
			m_OnRocketCheckWeaponCollisionhook.reset();
		}

		if (m_OnCheckTargetByBombhook)
		{
			m_OnCheckTargetByBombhook->Unhook();
			Sleep(100);
			m_OnCheckTargetByBombhook.reset();
		}
	}

	/*
	void __fastcall Miscellaneous::OnSendFieldSocketBattleAttackEvasion_Hooked(CWSlowData* ecx, void* edx, DWORD nTargetIndex, DWORD nItemIndex, DWORD nClientIndex, DWORD nItemNum)
	{
		PUSHCPUSTATE
		if (g_pMiscellaneous->IsEnabled() && g_pMiscellaneous->m_cant_evade_missles)
		{
			POPCPUSTATE
			return;
		}
		POPCPUSTATE
		g_pMiscellaneous->m_orig_OnSendFieldSocketBattleAttackEvasionMessage(ecx, nTargetIndex, nItemIndex, nClientIndex, nItemNum);
	}
	*/

	void __fastcall Miscellaneous::OnMissileCheckWeaponCollision_Hooked(CWeaponMissileData* ecx, void* edx, CItemData* pTargetItem)
	{
		PUSHCPUSTATE
		CEnemyData* enemy = nullptr;
		bool enemyRolling = false;

		CSceneData* scene = OSR_API->GetSceneData();
		if (g_pMiscellaneous->m_enemy_hit_in_roll && ecx->m_nTargetIndex != 0)
		{
			auto enemyIt = scene->m_mapEnemyList.find(ecx->m_nTargetIndex);
			if (enemyIt != scene->m_mapEnemyList.end())
			{
				enemy = enemyIt->second;
				enemyRolling = enemy->m_bRollStart;
				enemy->m_bRollStart = FALSE;
			}
		}
		POPCPUSTATE
		g_pMiscellaneous->m_orig_OnMissleCheckWeaponCollisionMessage(ecx, pTargetItem);
		   	
		if (enemy){
			enemy->m_bRollStart = enemyRolling;
		}
	}

	void __fastcall Miscellaneous::OnRocketCheckWeaponCollision_Hooked(CWeaponRocketData* ecx, void* edx, CItemData* pTargetItem)
	{
		PUSHCPUSTATE
		CEnemyData* enemy = nullptr;
		bool enemyRolling = false;

		CSceneData* scene = OSR_API->GetSceneData();
		if (g_pMiscellaneous->m_enemy_hit_in_roll && ecx->m_nTargetIndex != 0)
		{
			auto enemyIt = scene->m_mapEnemyList.find(ecx->m_nTargetIndex);
			if (enemyIt != scene->m_mapEnemyList.end())
			{
				enemy = enemyIt->second;
				enemyRolling = enemy->m_bRollStart;
				enemy->m_bRollStart = FALSE;
			}
		}
		POPCPUSTATE
		g_pMiscellaneous->m_orig_OnRocketCheckWeaponCollisionMessage(ecx, pTargetItem);

		if (enemy) {
			enemy->m_bRollStart = enemyRolling;
		}
	}

	void __fastcall Miscellaneous::OnCheckTargetByBomb_Hooked(CWeaponMissileData* ecx, void* edx)
	{
		PUSHCPUSTATE
		CSceneData* scene = OSR_API->GetSceneData(); 
		bool buffer = g_pMiscellaneous->m_enemy_hit_in_roll;
		if (buffer)
		{
			for(auto enemy : scene->m_mapEnemyList)
			{
				rollingEnemies[enemy.first] = enemy.second->m_bRollStart;
				enemy.second->m_bRollStart = FALSE;
			}
		}
		POPCPUSTATE

		g_pMiscellaneous->m_orig_OnCheckTargetByBombMessage(ecx);

		PUSHCPUSTATE
		if (buffer)
		{
			for (auto enemy : rollingEnemies) 
			{
				auto enemyIt = scene->m_mapEnemyList.find(enemy.first);
				if (enemyIt != scene->m_mapEnemyList.end()) {
					scene->m_mapEnemyList[enemy.first]->m_bRollStart = enemy.second;
				}
			}
		}
		POPCPUSTATE
	}

	void Miscellaneous::OnMessageBoxClose(int result)
	{
		if (m_whisper_popup_open && result == 1) // ok button
		{
			// set all messages as read 
			CINFGameMainChat* chat = OSR_API->GetINFGameMainChat();
			if (chat)
			{
				for (auto whisperchat : chat->m_vectorINFiGameMainWisperChatPtr)
				{
					whisperchat->m_bNewMassage = false;
				}
			}

			if (m_whisperwarner_snooze_enabled)
			{
				auto currenttime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
				m_whisper_timer.Reset(WHISPER_SNOOZE_TIME);
			}
			m_whisper_popup_open = false;
		}

		if (m_boss_popup_open && result == 1)
		{
			m_boss_popup_open = false;
		}
	}

	CItemInfo* Miscellaneous::FindStealthCardInInventory()
	{
		CItemInfo* sc = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Starter_Mini_Stealth_Card);
		if (!sc) {
			sc = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Mini_Stealth_Card);
			if (!sc) {
				sc = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Stealth_Card_30m);
				if (!sc) {
					sc = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Stealth_Card_2h);
				}
			}
		}

		return sc;
	}

	void Miscellaneous::TickWhisperWarner()
	{
		if (m_whisperwarner_active && m_whisper_timer.IsReady())
		{
			CINFGameMainChat* chat = OSR_API->GetINFGameMainChat();
			if (chat)
			{
				std::vector<string> whisperer;
				for (auto whisperchat : chat->m_vectorINFiGameMainWisperChatPtr)
				{
					if (whisperchat->m_bNewMassage)
					{
						whisperer.push_back(std::string(whisperchat->m_szWisperCharacterName));
					}
				}

				if (whisperer.size() > 0)
				{
					m_buddy->NotifySound(NotifyType::Warning);
					if (!m_whisper_popup_open && m_buddy->NotificationPopupAllowed())
					{
						std::string msg;
						bool first = true;
						for (auto wp : whisperer)
						{
							if (!first) {
								msg += ", ";
							}
							msg += wp;
						}
						msg += (first) ? " has whispered you!" : " have whispered you!";
						m_buddy->OpenMessageBoxAsync(msg, "Whisper Warning!", NotifyType::Warning, std::bind(&Miscellaneous::OnMessageBoxClose, this, std::placeholders::_1));
						m_whisper_popup_open = true;
					}
					m_whisper_timer.Reset(WHISPER_WARNING_TIME);

					if (m_whisperwarner_closeall) {
						m_buddy->DisableAllFeatures();
					}
				}
			}
		}
	}

	void Miscellaneous::TickAutoFlip()
	{
		if (m_autoflip && OSR_API->IsLanded() && OSR_API->GetAtumApplication()->m_pShuttleChild->m_vUp.y < 0) {
			OSR_API->GetAtumApplication()->m_pShuttleChild->m_vUp.y *= -1;
		}
	}

	void Miscellaneous::TickBossWarner()
	{
		if (m_bosswarner && m_bosscheck_timer.IsReady())
		{
			// search all mobs
			for (auto& monster : OSR_API->GetSceneData()->m_mapMonsterList)
			{
				if (!OSR_API->IsGoodBossMonster(monster.second)) {
					continue;
				}

				m_buddy->NotifySound(NotifyType::Information);

				if (!m_boss_popup_open && m_buddy->NotificationPopupAllowed())
				{
					std::string msg = std::string(monster.second->m_pMonsterInfo->MonsterName) + " just appeared.";
					m_buddy->OpenMessageBoxAsync(msg, "Boss Notifcation", NotifyType::Information);
					m_boss_popup_open = true;
				}
			}
			m_bosscheck_timer.Reset();
		}
	}

	void Miscellaneous::TickAutoStealthcard()
	{
		if (m_use_stealthcard && !OSR_API->IsStealthCardActive())
		{
			CItemInfo* stealthcard = FindStealthCardInInventory();
			if (stealthcard)
				OSR_API->TrySendUseItem(stealthcard);
		}
	}

	void Miscellaneous::TickAutoAmmo()
	{
		if (m_use_ammobox && (OSR_API->GetPrimaryWeaponAmmo() == 0 || OSR_API->GetSecondaryWeaponAmmo() == 0))
		{
			CItemInfo* ammobox = OSR_API->FindItemInInventoryByItemNum(ItemNumber::AmmunitionRechargeBox);
			if (ammobox)
				OSR_API->TrySendUseItem(ammobox);
		}
	}

	void Miscellaneous::TickAutoRabbit()
	{
		if (m_use_rabbit && !OSR_API->IsActiveItem(ItemNumber::Rabbit_Necklace))
		{
			CItemInfo* rabbit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Rabbit_Necklace);
			if (rabbit)
				OSR_API->TrySendUseItem(rabbit);
		}
	}

	void Miscellaneous::TickAutoCharm()
	{
		if (m_autocharms_active && m_selected_combo_item.GetKey() != 0)
		{
			CItemInfo* item = OSR_API->FindItemInInventoryByItemNum(m_selected_combo_item.GetKey(), true);
			if (item)
			{
				auto equipped_item = OSR_API->GetEquippedItem(TO_ENUM(EQUIP_POS, item->ItemInfo->Position));
				if (equipped_item)
				{
					if (equipped_item->ItemNum != m_selected_combo_item.GetKey()) {
						OSR_API->TryEquipItem(item);
					}
				}
				else
				{
					OSR_API->TryEquipItem(item);
				}
			}
			else
			{
				// when no more selected charms are available, turn off and set selected charm to inital values
				m_autocharms_active = false;
				m_selected_combo_item = ImGui::ComboItem();
			}
		}
	}

	void Miscellaneous::TickVisibility()
	{
		auto scenedata = OSR_API->GetSceneData();
		if (scenedata)
		{
			CItemInfo* searcheyes = nullptr;
			auto it = scenedata->m_mapEnemyList.begin();
			while (it != scenedata->m_mapEnemyList.end())
			{
				CEnemyData* enemy = it->second;
				if (enemy->m_nAlphaValue == 0)
				{
					if (m_use_searcheye && m_searcheye_timer.IsReady() && !m_buddy->GetPacketManager()->UseItemWaitingOk(TO_INT(ItemNumber::Search_Eye)))
					{
						// do NOT use search eyes to detect a GM
						if (!COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_OPERATION | RACE_GAMEMASTER))
						{
							if (!searcheyes)
							{
								searcheyes = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Search_Eye);
							}
							if (searcheyes && searcheyes->CurrentCount > 0)
							{
								OSR_API->SendUseItem(searcheyes);
								m_searcheye_timer.Reset();
							}
						}
					}

					if (m_force_visibility)
					{
						enemy->m_bySkillStateFlag = CL_SKILL_NONE;
						enemy->m_nAlphaValue = 135; // set alpha value to that of invisible teammates
					}
				}
				it++;
			}
		}
	}

	void Miscellaneous::TickGMWarner()
	{
		if (m_gmwarner_active && m_gm_timer.IsReady())
		{
			auto scenedata = OSR_API->GetSceneData();
			if (scenedata)
			{
				auto it = scenedata->m_mapEnemyList.begin();
				while (it != scenedata->m_mapEnemyList.end())
				{
					CEnemyData* enemy = it->second;
					if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_OPERATION | RACE_GAMEMASTER))
					{
						m_online_gms[std::string(enemy->m_infoCharacter.CharacterInfo.CharacterName)] = GetTickCount64();
					}
					it++;
				}

				OSR_API->RqInvitePartyInfo();
			}
			m_gm_timer.Reset();
		}
	}

	void Miscellaneous::TickNoOverheat()
	{
		if (m_no_overheat_primary)
		{
			CWeaponItemInfo* weapon = OSR_API->GetAtumApplication()->m_pShuttleChild->m_pPrimaryWeapon;
			ITEM* weaponItem = weapon->m_pItemInfo->ItemInfo;
			float overheattime = (weaponItem->Time * (1.0f + (IS_PRIMARY_WEAPON(weaponItem->Kind) ? weapon->m_pCharacterParamFactor->pfm_TIME_01 : weapon->m_pCharacterParamFactor->pfm_TIME_02)) / 1000.0f);
			weapon->m_fOverHeatCheckTime = overheattime;
		}

		if (m_no_overheat_booster)
		{
			CShuttleChild* shuttle = OSR_API->GetAtumApplication()->m_pShuttleChild;
			shuttle->m_fCurrentBURN = shuttle->m_fBURN;
		}
	}
}