#include "osrb_pch.h"
#include "InventoryManager.h"
#include "imgui/imgui.h"
#include "OSRAPI.h"
#include "OSRBuddy.h"
#include "SDK/AtumApplication.h"

#include "SDK/AtumProtocol.h"
#include "SDK/AtumError.h"

#define CAPSULE_OPEN_REATTACK 300ms
#define CAPSULE_OPEN_REATTACK_VARIANCE 300ms

#define ITEM_DELETE_REATTACK 400ms
#define ITEM_DELETE_REATTACK_VARIANCE 500ms

#define ITEM_SELL_REATTACK 250ms
#define ITEM_SELL_REATTACK_VARIANCE 100ms

namespace Features
{
	InventoryManager::InventoryManager(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
	{
		m_clean_inventory = false;
		m_only_clean_while_overheat = false;
		m_only_clean_while_stopped = false;
		m_open_watermelongift = true;
		m_open_spicapsule = false;
		m_open_fantasyglobemineralcapsule = true;
		m_open_mineralcapsule = true;
		m_open_wpcapsule = true;
		m_open_soccer_ball_capsule = true;
		m_open_sp_mineral_caps = false;

		m_delete_items = false;
		m_delete_items_maxlevel = 20;
		m_delete_weapons = false;
		m_delete_engines = false;
		m_delete_radars = false;
		m_delete_marks = true;
		m_delete_cpus = false;
#ifdef HALLOWEEN_EVENT
		m_open_halloween_capsule = true;
#else
		m_open_halloween_capsule = false;
#endif
#ifdef CHRISTMAS_EVENT
		m_delete_christmas_event_items = true;
		m_open_blue_gift = true;
		m_open_red_gift = true;
		m_open_lost_snowman_article = true;
		m_open_mystery_capsule = true;
		m_open_xmas_box = true;
		m_open_christmas_gift = true;
		m_open_christmas_gift_x = true;
		m_open_christmas_gift_m = true;
		m_open_christmas_gift_a = true;
		m_open_christmas_gift_s = true;
#else
		m_delete_christmas_event_items = false;
		m_open_blue_gift = false;
		m_open_red_gift = false;
		m_open_lost_snowman_article = false;
		m_open_mystery_capsule = false;
		m_open_xmas_box = false;
		m_open_christmas_gift = false;
		m_open_christmas_gift_x = false;
		m_open_christmas_gift_m = false;
		m_open_christmas_gift_a = false;
		m_open_christmas_gift_s = false;
#endif // CHRISTMAS_EVENT
		m_awaiting_delete_ok = false;
		m_in_sell_building = false;
		m_sold_item = 0;
		m_deleted_item = 0;
		m_open_capsules = true;
		m_awaiting_sell_ok = false;
		m_item_selection_dirty = true;
		m_selected_item_count = 0;
		m_selling_items = false;
		m_open_vanillaicecream_capsule = false;

		m_inventory_action_timer = BuddyTimer(400ms);
	}

	InventoryManager::~InventoryManager()
	{
	}

	FeatureType InventoryManager::GetType() const
	{
		return FeatureType::InventoryManager;
	}

	std::string InventoryManager::GetName() const
	{
		return "InventoryManager";
	}

	void InventoryManager::Tick()
	{
		if (!IsEnabled()) {
			return;
		}

		TickItemSell();
		TickInventoryCleaning();
	}

	void InventoryManager::RenderImGui()
	{
		DrawEnableCheckBox();
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::Text("Only perform actions when:");
		ImGui::Separator();
		ImGui::Checkbox("Gear is b-stopped", &m_only_clean_while_stopped);
		ImGui::SameLine();
		ImGui::Checkbox("Standard weapon is overheated", &m_only_clean_while_overheat);
		ImGui::NewLine();
		ImGui::BeginColumns("IMColumns", 2, ImGuiColumnsFlags_NoResize);
		{
			ImGui::SetColumnWidth(0, 400);
			ImGui::BeginChild("IMColumn1", ImVec2(), false);
			{
				//ImGui::Separator();
				ImGui::Text("Automatic Capsule Opening");
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Will automatically open the below specified items.");
				}
				ImGui::Separator();
				ImGui::Checkbox("Auto open capsules", &m_open_capsules);
				ImGui::NewLine();

				ImGui::BeginColumns("CapsuleOpeningColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
				{		
					ImGui::Checkbox("Watermelon Gifts", &m_open_watermelongift);
					ImGui::Checkbox("SPI Capsules", &m_open_spicapsule);
					ImGui::Checkbox("FG Mineral Capsule", &m_open_fantasyglobemineralcapsule);
					ImGui::Checkbox("Vanilla Ice Cream", &m_open_vanillaicecream_capsule);
					ImGui::Checkbox("Mineral Capsules", &m_open_mineralcapsule);
					ImGui::Checkbox("Warpoint Capsules", &m_open_wpcapsule);
					ImGui::Checkbox("Mystery Capsule", &m_open_mystery_capsule);
					ImGui::Checkbox("SP Mineral Caps", &m_open_sp_mineral_caps);
				}
				ImGui::NextColumn();
				{
#ifdef SUMMER_EVENT
					ImGui::Checkbox("Soccer Ball Capsule", &m_open_soccer_ball_capsule);
#endif
#ifdef HALLOWEEN_EVENT
					ImGui::Checkbox("Halloween Capsule", &m_open_halloween_capsule);
					ImGui::Checkbox("Halloween Staff Box", &m_open_halloween_staff_box);
#endif
#ifdef CHRISTMAS_EVENT
					ImGui::Checkbox("Blue gift", &m_open_blue_gift);
					ImGui::Checkbox("Red gift", &m_open_red_gift);
					ImGui::Checkbox("Lost Snowman Article", &m_open_lost_snowman_article);
					ImGui::Checkbox("Xmas Box", &m_open_xmas_box);
					ImGui::Checkbox("Christmas gift", &m_open_christmas_gift);
					ImGui::Checkbox("Christmas gift X", &m_open_christmas_gift_x);
					ImGui::Checkbox("Christmas gift M", &m_open_christmas_gift_m);
					ImGui::Checkbox("Christmas gift A", &m_open_christmas_gift_a);
					ImGui::Checkbox("Christmas gift S", &m_open_christmas_gift_s);	 
#endif
				}
				ImGui::EndColumns();
			}
			ImGui::EndChild();
		}
		ImGui::NextColumn();
		{
			ImGui::BeginChild("IMColumn2", ImVec2(), false);
			{
				//ImGui::Separator();
				ImGui::Text("Easy item removal");
				ImGui::Separator();
				ImGui::NewLine();
				if (ImGui::SliderInt("Max Level", &m_delete_items_maxlevel, 1, 123)) {
					m_item_selection_dirty = true;
				}
				ImGui::BeginColumns("ItemsDeletionColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
				{
					if (ImGui::Checkbox("Weapons", &m_delete_weapons)) {
						m_item_selection_dirty = true;
					}
					if (ImGui::Checkbox("Radars", &m_delete_radars)) {
						m_item_selection_dirty = true;
					}
					if (ImGui::Checkbox("Engines", &m_delete_engines)) {
						m_item_selection_dirty = true;
					}
				}
				ImGui::NextColumn();
				{
					if (ImGui::Checkbox("CPUs", &m_delete_cpus)) {
						m_item_selection_dirty = true;
					}
					if (ImGui::Checkbox("Marks", &m_delete_marks)) {
						m_item_selection_dirty = true;
					}
#ifdef CHRISTMAS_EVENT
					if (ImGui::Checkbox("Christmas Event items", &m_delete_christmas_event_items)) {
						m_item_selection_dirty = true;
					}
					if (ImGui::IsItemHovered()) {
						ImGui::SetTooltip("Christmas Wreath (1); Random mark capsule; Santa_golden_Telescope; Light_as_a_Snowflake; Working_Speed_of_Santa; Power_of_a_Reindeer; Blizzard; Hot_Chocolate");
					}
#endif
				}
				ImGui::EndColumns();
				ImGui::NewLine();
				ImGui::Text("Items matching the selection:");
				ImGui::SameLine();
				ImGui::Text(std::to_string(GetSelectedItemAmount()).c_str());
				ImGui::NewLine();
				ImGui::Separator();
				ImGui::NewLine();
				ImGui::Checkbox("Auto delete items###enableItemsDeletion", &m_delete_items);
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Delete items from inventory based on selection.\nWill never delete enchanted or currently equipped items!");
				}
				ImGui::BeginDisabledMode(!m_in_sell_building);
				{
					if (!m_selling_items)
					{
						if (ImGui::Button("Start Autoselling")) {
							m_selling_items = true;
						}
					}
					else
					{
						if (ImGui::Button("Stop Autoselling")) {
							m_selling_items = false;
						}
					}
				}
				ImGui::EndDisabledMode();
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Sell items from inventory based on selection.\nWill never delete enchanted or currently equipped items!\nCharacter needs to be in a sellshop to use!");
				}
			}
			ImGui::EndChild();
		}
		ImGui::EndColumns();
	}

	void InventoryManager::ActivateInventoryCleaning(bool active)
	{
		m_clean_inventory = active;
	}

	bool InventoryManager::TryOpenCapsule(ItemNumber capsule)
	{
		CItemInfo* item = OSR_API->FindItemInInventoryByItemNum(capsule);
		if (item && OSR_API->TrySendUseItem(item))
		{
			m_inventory_action_timer.Reset(CAPSULE_OPEN_REATTACK, CAPSULE_OPEN_REATTACK_VARIANCE);
			return true;
		}
		return false;
	}

	bool InventoryManager::ItemInSelection(CItemInfo* item)
	{
		if ((m_delete_weapons && IS_WEAPON(item->Kind)) ||
			(m_delete_marks && item->Kind == ITEMKIND_MARK) ||
			(m_delete_cpus && item->Kind == ITEMKIND_COMPUTER) ||
			(m_delete_radars && item->Kind == ITEMKIND_RADAR) ||
			(m_delete_engines && item->Kind == ITEMKIND_SUPPORT) ||
			(m_delete_christmas_event_items && IsUselessChristmasEventItem(item)))
		{
			if(COMPARE_BIT_FLAG(item->ItemInfo->ItemAttribute, ITEM_ATTR_LEGEND_ITEM) 
				|| COMPARE_BIT_FLAG(item->ItemInfo->ItemAttribute, ITEM_ATTR_UNIQUE_ITEM)
				|| COMPARE_BIT_FLAG(item->ItemInfo->ItemAttribute, ITEM_ATTR_QUEST_ITEM))
			{
				return false;
			}

			// double check all coloured items (boss / unique / oldschool items)
			if (item->ItemInfo->ItemName[0] == '\\') {
				return false;
			}

			// skip all enchanted items
			if (item->m_nEnchantNumber > 0) {
				return false;
			}

			// skip all equipped items
			bool is_equipped_item = false;
			auto invenextend = OSR_API->GetAtumApplication()->m_pInterface->m_pGameMain->m_pInven;
			for (int i = 0; i < MAX_EQUIP_POS; i++)
			{
				if (invenextend->m_pWearDisplayInfo[i] && invenextend->m_pWearDisplayInfo[i]->pItem->UniqueNumber == item->UniqueNumber)
				{
					is_equipped_item = true;
					break;
				}
			}
			if (is_equipped_item) {
				return false;
			}

			// skip all items under the specified level
			if (item->ItemInfo->ReqMinLevel > m_delete_items_maxlevel) {
				return false;
			}

			return true;
		}
		return false;
	}

	CItemInfo* InventoryManager::GetNextItemForDelete()
	{
		for (auto mapentry : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pStoreData->m_mapItemUniqueNumber)
		{
			CItemInfo* iteminfo = mapentry.second;
			if (ItemInSelection(iteminfo)) {
				return iteminfo;
			}
		}
		return nullptr;

	}

	int InventoryManager::GetSelectedItemAmount()
	{
		if (m_item_selection_dirty)
		{
			m_selected_item_count = 0;
			for (auto mapentry : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pStoreData->m_mapItemUniqueNumber)
			{
				CItemInfo* iteminfo = mapentry.second;
				if (ItemInSelection(iteminfo)) {
					m_selected_item_count++;
				}
			}
			m_item_selection_dirty = false;
		}
		return m_selected_item_count;
	}

	void InventoryManager::TickInventoryCleaning()
	{
		if ((!m_only_clean_while_stopped || OSR_API->GetAtumApplication()->m_pShuttleChild->m_bUnitStop) &&
			(!m_only_clean_while_overheat || OSR_API->GetPrimaryWeapon()->m_bOverHeat))
		{
			if (m_inventory_action_timer.IsReady())
			{
				// first try to delete items to make space
				if (TickItemDelete()) {
					return;
				}

				TickCapsuleOpening();
			}
		}
	}

	void InventoryManager::TickCapsuleOpening()
	{
		if (m_open_capsules && !OSR_API->IsInventoryFull())
		{
			if (m_open_mineralcapsule && TryOpenCapsule(ItemNumber::Mineral_Capsule)) {
				return;
			}
			if (m_open_sp_mineral_caps && TryOpenCapsule(ItemNumber::Sp_Mineral_Caps)) {
				return;
			}

			if (m_open_fantasyglobemineralcapsule && TryOpenCapsule(ItemNumber::Fantasy_Globe_Mineral_Capsule)) {
				return;
			}

			if (m_open_watermelongift && TryOpenCapsule(ItemNumber::Square_Watermelon_Gift_New)) {
				return;
			}

			if (m_open_soccer_ball_capsule && TryOpenCapsule(ItemNumber::Soccer_Ball_Capsule)) {
				return;
			}

			if (m_open_vanillaicecream_capsule && TryOpenCapsule(ItemNumber::Vanilla_Ice_Cream)) {
				return;
			}

			if (m_open_halloween_capsule && TryOpenCapsule(ItemNumber::Halloween_Capsule)) {
				return;
			}

			if (m_open_halloween_staff_box && TryOpenCapsule(ItemNumber::Halloween_Staff_Box)) {
				return;
			}

			if (m_open_blue_gift && TryOpenCapsule(ItemNumber::Blue_gift)) {
				return;
			}

			if (m_open_red_gift && TryOpenCapsule(ItemNumber::Red_gift)) {
				return;
			}

			if (m_open_lost_snowman_article && TryOpenCapsule(ItemNumber::Lost_Snowman_Article)) {
				return;
			}

			if (m_open_xmas_box && TryOpenCapsule(ItemNumber::Xmas_Box)) {
				return;
			}

			if (m_open_mystery_capsule && TryOpenCapsule(ItemNumber::Mystery_capsule)) {
				return;
			}

			if (m_open_christmas_gift && TryOpenCapsule(ItemNumber::Christmas_gift)) {
				return;
			}

			if (m_open_christmas_gift_x && TryOpenCapsule(ItemNumber::Christmas_gift_X)) {
				return;
			}

			if (m_open_christmas_gift_m && TryOpenCapsule(ItemNumber::Christmas_gift_M)) {
				return;
			}

			if (m_open_christmas_gift_a && TryOpenCapsule(ItemNumber::Christmas_gift_A)) {
				return;
			}

			if (m_open_christmas_gift_s && TryOpenCapsule(ItemNumber::Christmas_gift_S)) {
				return;
			}

			if (m_open_wpcapsule)
			{
				if (TryOpenCapsule(ItemNumber::WP_Capsule_10000)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_5000)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_2500)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_1000)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_500)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_100)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_50)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_10)) {
					return;
				}

				if (TryOpenCapsule(ItemNumber::WP_Capsule_3)) {
					return;
				}
			}

			if (m_open_spicapsule && OSR_API->GetInventorySPI() < (MAX_SPI - 200000) && TryOpenCapsule(ItemNumber::SPI_capsule)) {
				return;
			}
		}

	}

	bool InventoryManager::TickItemDelete()
	{
		if (m_delete_items && !m_awaiting_delete_ok)
		{
			CItemInfo* iteminfo = GetNextItemForDelete();
			if (iteminfo)
			{
				// delete item
				OSR_API->DeleteItem(iteminfo, 1);
				m_item_selection_dirty = true;
				m_inventory_action_timer.Reset(ITEM_DELETE_REATTACK, ITEM_DELETE_REATTACK_VARIANCE);
				return true;
			}
		}
		return false;
	}

	void InventoryManager::TickItemSell()
	{
		// check if player is in a building where it is possible to sell items
		if (OSR_API->PlayerIsInSellBuilding()) {
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
			if (m_inventory_action_timer.IsReady())
			{
				CItemInfo* item = GetNextItemForDelete();
				if (!item) // no more items to sell
				{
					m_selling_items = false;
					return;
				}

				if (OSR_API->TrySendSellItem(item, item->CurrentCount)) {
					m_inventory_action_timer.Reset(ITEM_SELL_REATTACK, ITEM_SELL_REATTACK_VARIANCE);
				}
			}
		}
	}

	bool InventoryManager::IsUselessChristmasEventItem(CItemInfo* item)
	{
		switch (TO_ENUM(ItemNumber,item->ItemNum))
		{
		case ItemNumber::Christmas_Wreath_1:
		case ItemNumber::Random_mark_capsule:
		case ItemNumber::Santa_golden_Telescope:
		case ItemNumber::Light_as_a_Snowflake:
		case ItemNumber::Working_Speed_of_Santa:
		case ItemNumber::Power_of_a_Reindeer:
		case ItemNumber::Blizzard:
		case ItemNumber::Hot_Chocolate:
			return true;
		}
		return false;
	}
}
