#include "Miscellaneous.h"
#include "imgui/imgui.h" 
#include "OSRAPI.h";
#include "OSRBuddy.h"
#include "SDK/AtumApplication.h"

#define WHISPER_WARNING_TIME 10s
#define CAPSULE_OPEN_REATTACK 200ms
#define ITEM_DELETE_REATTACK 400ms
#define WHIPSER_SNOOZE_TIME 2min
#define ITEM_SELL_REATTACK 210ms

Miscellaneous::Miscellaneous(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_whisperwarner_active = false;	
	m_whisperwarner_snooze_enabled = true;

	m_inv_action_check_time = 0ms;
	m_clean_inventory = false;
	m_only_clean_while_overheat = false;
	m_only_clean_while_stopped = false;
	m_open_watermelongift = true;
	m_open_spicapsule = false;
	m_open_fantasyglobemineralcapsule = true;
	m_open_mineralcapsule = true;
	m_open_wpcapsule = false;
	m_open_soccer_ball_capsule = true;
	m_delete_items = false;
	m_delete_items_maxlevel = 20;
	m_delete_weapons = true;
	m_delete_engines = false;
	m_delete_radars = true;
	m_delete_marks = true;
	m_delete_cpus = true;
	m_awaiting_delete_ok = false;
	m_in_sell_building = false;
	m_sold_item = 0;
	m_deleted_item = 0;
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
	if (m_inv_action_check_time > 0ms) {
		m_inv_action_check_time -= std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
	}
	if (m_inv_action_check_time < 0ms) {
		m_inv_action_check_time = 0ms;
	}
		   
	TickAutoFlip();
	TickItemSell();
	TickWhisperWarner();
	TickInventoryCleaning();
}

void Miscellaneous::RenderImGui()
{
	ImGui::NewLine();
	ImGui::BeginColumns("MiscColumns", 2, ImGuiColumnsFlags_NoResize);
	{
		ImGui::BeginChild("MiscColumn1", ImVec2(), false);
		{
			ImGui::Separator();
			ImGui::Text("Whisperwarner");
			ImGui::Separator();
			ImGui::Checkbox("Active", &m_whisperwarner_active);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Will notify the user whenever there is a new / unread whisper message.");
			}
			ImGui::Checkbox("Snooze enabled", &m_whisperwarner_snooze_enabled);
			ImGui::Checkbox("Close all features when getting whispered.", &m_whisperwarner_closeall);  	

			ImGui::Separator();
			ImGui::NewLine();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::BeginDisabledMode(OSR_API->GetPlayerGearType() != GearType::AGear);
			{
				ImGui::Checkbox("Autoflip", &m_autoflip);
			}
			ImGui::EndDisabledMode();
		}
		ImGui::EndChild();
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("MiscColumn2", ImVec2(), false);
		{
			ImGui::Separator();
			ImGui::Text("Inventory Cleaning");
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("This works for all gears. Grindbot does not have to be enabled for this to work.");
			}
			ImGui::Separator();

			ImGui::Checkbox("Active", &m_clean_inventory);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Will automatically open the below specified items.");
			}
			ImGui::SameLine();
			ImGui::Checkbox("Stopped", &m_only_clean_while_stopped);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Only clean inventory while gear is stopped.");
			}
			ImGui::SameLine();
			ImGui::Checkbox("Overheated", &m_only_clean_while_overheat);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Only clean inventory standard weapon is overheated.");
			}

			ImGui::NewLine();
			ImGui::BeginColumns("InventoryCleaningColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
			{
				ImGui::Checkbox("Watermelon Gifts", &m_open_watermelongift);
				ImGui::Checkbox("SPI Capsules", &m_open_spicapsule);
				ImGui::Checkbox("Fantasy Globe MC", &m_open_fantasyglobemineralcapsule);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Mineral Capsules", &m_open_mineralcapsule);
				ImGui::Checkbox("WP Capsules", &m_open_wpcapsule);
				ImGui::Checkbox("Soccer Ball Capsule", &m_open_soccer_ball_capsule);
			}
			ImGui::EndColumns();
			ImGui::NewLine();
			ImGui::Text("Item Deletion");
			ImGui::Separator();
			ImGui::Checkbox("Active###deleteItemsActivation", &m_delete_items);
			ImGui::SliderInt("Max Level", &m_delete_items_maxlevel, 1, 100);
			ImGui::Checkbox("Weapons", &m_delete_weapons);
			ImGui::Checkbox("Radars", &m_delete_radars);
			ImGui::Checkbox("Engines", &m_delete_engines);
			ImGui::Checkbox("CPUs", &m_delete_cpus);
			ImGui::Checkbox("Marks", &m_delete_marks); 

			ImGui::NewLine();
			ImGui::BeginDisabledMode(!m_in_sell_building);
			{
				if (!m_selling_items) 
				{
					if (ImGui::Button("Start selling")) {
						m_selling_items = true;
					}
				}
				else
				{
					if (ImGui::Button("Stop selling")) {
						m_selling_items = false;
					}
				}
			}
			ImGui::EndDisabledMode();
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Sell all items that match the above criteria.\nCharacter needs to be in a sellshop.");
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndColumns();
}

bool Miscellaneous::OnReadPacket(unsigned short msgtype, byte* packet)
{
	switch (msgtype)
	{
	case T_FC_STORE_UPDATE_ITEM_COUNT:
	{
		MSG_FC_STORE_UPDATE_ITEM_COUNT* msg = (MSG_FC_STORE_UPDATE_ITEM_COUNT*)packet;
		if (msg->ItemUpdateType == IUT_GENERAL && msg->ItemUniqueNumber == m_deleted_item) 
		{
			m_deleted_item = 0;
			m_awaiting_delete_ok = false;
		}

		if (msg->ItemUpdateType == IUT_SHOP && msg->ItemUniqueNumber == m_sold_item) 
		{
			m_sold_item = 0;
			m_awaiting_sell_ok = false;
		}
	}
	break;
	case T_FC_STORE_DELETE_ITEM:
	{
		MSG_FC_STORE_DELETE_ITEM* msg = (MSG_FC_STORE_DELETE_ITEM*)packet;
		if (msg->ItemDeletionType == IUT_GENERAL && msg->ItemUniqueNumber == m_deleted_item)
		{
			m_deleted_item = 0;
			m_awaiting_delete_ok = false;
		}

		if (msg->ItemDeletionType == IUT_SHOP && msg->ItemUniqueNumber == m_sold_item)
		{
			m_sold_item = 0;
			m_awaiting_sell_ok = false;
		}
	}  
	break;
	case T_ERROR:
		MSG_ERROR* msg = (MSG_ERROR*)packet;
		if (msg->MsgType == T_FC_SHOP_SELL_ITEM)
		{

		}
		break;
	}  
	return false;
}

bool Miscellaneous::OnWritePacket(unsigned short msgtype, byte* packet)
{
	switch (msgtype)
	{
	case T_FC_ITEM_THROW_AWAY_ITEM:
		{	  			
			MSG_FC_ITEM_THROW_AWAY_ITEM* msg = (MSG_FC_ITEM_THROW_AWAY_ITEM*)packet;
			m_deleted_item = msg->ItemUniqueNumber;
			m_awaiting_delete_ok = true;
		}
		break;
	case T_FC_SHOP_SELL_ITEM:
		{
			MSG_FC_SHOP_SELL_ITEM* msg = (MSG_FC_SHOP_SELL_ITEM*)packet;
			m_sold_item = msg->ItemUniqueNumber;
			m_awaiting_sell_ok = true;
		}
		break;
	}
	return false;
}

void Miscellaneous::ActivateInventoryCleaning(bool active)
{
	m_clean_inventory = active;
}

bool Miscellaneous::TrySendSellItem(CItemInfo* item, int count)
{
	if (item && count <= item->CurrentCount && !m_awaiting_sell_ok && m_in_sell_building)
	{	 		
		MSG_FC_SHOP_SELL_ITEM sMsg;
		memset(&sMsg, 0x00, sizeof(sMsg));
		char buffer[SIZE_MAX_PACKET];

		if (IS_COUNTABLE_ITEM(item->Kind)) {
			sMsg.Amount = count;
		}
		else {
			sMsg.Amount = 1;
		}
		sMsg.ItemKind = item->Kind;
		sMsg.ItemUniqueNumber = item->UniqueNumber;
		sMsg.BuildingIndex = OSR_API->GetCurrentBuilding().BuildingIndex;
		int nType = T_FC_SHOP_SELL_ITEM;
		memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
		memcpy(buffer + SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
		return OSR_API->WritePacket(reinterpret_cast<byte*>(buffer), SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
	} 
	return false;
}

void Miscellaneous::OnMessageBoxClose(int result)
{
	if (result == 1) // ok button
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
			m_ignore_whisperwarn_time = currenttime + WHIPSER_SNOOZE_TIME;
		}
	}	  
	m_popup_open = false;
}


CItemInfo* Miscellaneous::GetNextItemForDelete()
{
	for (auto mapentry : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pStoreData->m_mapItemUniqueNumber)
	{
		CItemInfo* iteminfo = mapentry.second;

		if ((m_delete_weapons && IS_WEAPON(iteminfo->Kind)) ||
			(m_delete_marks && iteminfo->Kind == ITEMKIND_MARK) ||
			(m_delete_cpus && iteminfo->Kind == ITEMKIND_COMPUTER) ||
			(m_delete_radars && iteminfo->Kind == ITEMKIND_RADAR) ||
			(m_delete_engines && iteminfo->Kind == ITEMKIND_SUPPORT))
		{
			// skip all enchanted items
			if (iteminfo->m_nEnchantNumber > 0) {
				continue;
			}

			// skip all equipped items
			bool is_equipped_item = false;
			auto invenextend = OSR_API->GetAtumApplication()->m_pInterface->m_pGameMain->m_pInven;
			for (int i = 0; i < MAX_EQUIP_POS; i++)
			{
				if (invenextend->m_pWearDisplayInfo[i] && invenextend->m_pWearDisplayInfo[i]->pItem->UniqueNumber == iteminfo->UniqueNumber)
				{
					is_equipped_item = true;
					break;
				}
			}
			if (is_equipped_item) {
				continue;
			}

			// skip all items under the specified level
			if (iteminfo->ItemInfo->ReqMinLevel > m_delete_items_maxlevel) {
				continue;
			}
	
			return iteminfo;
		}
	}
	return nullptr;
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
	auto currenttime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	if (currenttime < m_ignore_whisperwarn_time) {
		return;
	}

	if (m_whisperwarner_active && (currenttime - m_last_whisperwarn) >= WHISPER_WARNING_TIME)
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
				if (!m_popup_open && m_buddy->NotificationPopupAllowed())
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
					m_popup_open = true;
				}
				m_last_whisperwarn = currenttime;

				if (m_whisperwarner_closeall) {
					m_buddy->DisableAllFeatures();
				}
			}
		}
	}
}

bool Miscellaneous::InventoryActionCheckTimeReady()
{
	return m_inv_action_check_time <= 0ms;
}

void Miscellaneous::ResetInventoryActionCheckTime()
{
	m_inv_action_check_time = CAPSULE_OPEN_REATTACK + std::chrono::milliseconds(m_buddy->GetRandInt32(0, 300));
}

void Miscellaneous::TickInventoryCleaning()
{
	if (m_clean_inventory && 
		(!m_only_clean_while_stopped || OSR_API->GetAtumApplication()->m_pShuttleChild->m_bUnitStop) && 
		(!m_only_clean_while_overheat || OSR_API->GetPrimaryWeapon()->m_bOverHeat))
	{
		if (InventoryActionCheckTimeReady())
		{
			// first try to delete items to make space
			if (TickItemDelete()) {
				return;
			}

			if (OSR_API->IsInventoryFull()) {
				return;
			}
			
			if (m_open_mineralcapsule && TryOpenCapsule(ItemNumber::Mineral_Capsule)) {
				return;
			}

			if (m_open_fantasyglobemineralcapsule && TryOpenCapsule(ItemNumber::Fantasy_Globe_Mineral_Capsule)) {
				return;
			}

			if (m_open_watermelongift && TryOpenCapsule(ItemNumber::Square_Watermelon_Gift)) {
				return;
			}  

			if (m_open_soccer_ball_capsule && TryOpenCapsule(ItemNumber::Soccer_Ball_Capsule)) {
				return;
			}
			  
			if (m_open_wpcapsule)
			{
				if (TryOpenCapsule(ItemNumber::WP_Capsule_100)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_500)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_1000)) {
					return;
				}
			}

			if (m_open_spicapsule && TryOpenCapsule(ItemNumber::SPI_capsule)) {
				return;
			}
		}
	}
}

bool Miscellaneous::TickItemDelete()
{
	if (m_delete_items && !m_awaiting_delete_ok)
	{
		CItemInfo* iteminfo = GetNextItemForDelete();
		if (iteminfo)
		{ 
			// delete item
			OSR_API->DeleteItem(iteminfo, iteminfo->CurrentCount);	 			
			m_inv_action_check_time = ITEM_DELETE_REATTACK + std::chrono::milliseconds(m_buddy->GetRandInt32(0, 500));
			return true;
		}		
	}			 
	return false;
}

bool Miscellaneous::TryOpenCapsule(ItemNumber capsule)
{
	CItemInfo* item = OSR_API->FindItemInInventoryByItemNum(capsule);
	if (item)
	{
		OSR_API->SendUseItem(item);
		ResetInventoryActionCheckTime();
		return true;
	}
	return false;
}

void Miscellaneous::TickItemSell()
{	
	// check if player is in a building where it is possible to sell items
	if (OSR_API->IsInBuilding() && (IS_ITEM_SHOP_TYPE(OSR_API->GetCurrentBuilding().BuildingKind) || IS_WARPOINT_SHOP_TYPE(OSR_API->GetCurrentBuilding().BuildingKind))) {  				
		m_in_sell_building = true;
	}
	else 
	{
		m_in_sell_building = false;
		m_selling_items = false;
	}	

	if (m_selling_items)
	{
		auto current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		if (current - m_last_itemsell > ITEM_SELL_REATTACK)
		{
			CItemInfo* item = GetNextItemForDelete();
			if (!item) // no more items to sell
			{
				m_selling_items = false;
				return;
			}

			if (TrySendSellItem(item, item->CurrentCount)) {
				m_last_itemsell = current;
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
