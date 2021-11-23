#include "osrb_pch.h"
#include "Miscellaneous.h"

#include "imgui/imgui.h"

#include "OSRAPI.h"
#include "OSRBuddy.h"

#include "SDK/AtumApplication.h"

#define WHISPER_WARNING_TIME 10s
#define WHISPER_SNOOZE_TIME 2min		  
   
#define AUTO_ITEM_REATTACK 1s
#define BOSS_CHECK_REATTACK 1s
#define UPDATE_CHARM_COMBO_REATTACK 250ms

Miscellaneous::Miscellaneous(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_whisperwarner_active = false;	
	m_whisperwarner_snooze_enabled = true;
 
	m_bosscheck_timer = BuddyTimer(BOSS_CHECK_REATTACK);
	m_autoitems_timer = BuddyTimer(AUTO_ITEM_REATTACK);
	m_bosswarner = false;
	m_update_charms_timer = BuddyTimer(UPDATE_CHARM_COMBO_REATTACK);
	m_selected_combo_item = ImGui::ComboItem();
}

Miscellaneous::~Miscellaneous()
{
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

	if (m_autoitems_timer.IsReady())
	{
		TickAutoStealthcard();
		TickAutoAmmo();
		TickAutoRabbit();
		TickAutoCharm();
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
			ImGui::SameLine();
		}
		ImGui::EndChild();	
	}
	ImGui::EndColumns();
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
	if (m_use_stealthcard && !OSR_API->IsStealthCardActive() )
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
