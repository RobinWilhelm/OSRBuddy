#pragma once
#include "BuddyFeatureBase.h"
#include "OSRBuddyDefine.h"
#include "BuddyTimer.h"

class CItemInfo;

class InventoryManager : public BuddyFeatureBase
{
public:
	InventoryManager(OSRBuddyMain* buddy);
	~InventoryManager();

	// Inherited via BuddyFeatureBase
	virtual FeatureType GetType() const override;
	virtual std::string GetName() const override;
	virtual void Tick() override;
	virtual void RenderImGui() override;

	void ActivateInventoryCleaning(bool active);
	bool TryOpenCapsule(ItemNumber capsule);
	bool ItemInSelection(CItemInfo* item);
	CItemInfo* GetNextItemForDelete();
	int GetSelectedItemAmount();

	void TickInventoryCleaning();
	void TickCapsuleOpening();
	bool TickItemDelete();
	void TickItemSell();

private:
	BuddyTimer m_inventory_action_timer;
	bool m_clean_inventory;
	bool m_only_clean_while_stopped;
	bool m_only_clean_while_overheat;

	bool m_open_capsules;
	bool m_open_watermelongift;
	bool m_open_spicapsule;
	bool m_open_fantasyglobemineralcapsule;
	bool m_open_mineralcapsule;
	bool m_open_wpcapsule;
	bool m_open_soccer_ball_capsule;
	bool m_open_vanillaicecream_capsule;
	bool m_open_halloween_capsule;

	bool m_delete_items;
	bool m_delete_weapons;
	bool m_delete_engines;
	bool m_delete_radars;
	bool m_delete_marks;
	bool m_delete_cpus;
	int m_delete_items_maxlevel;

	int m_selected_item_count;
	bool m_item_selection_dirty;

	bool m_awaiting_delete_ok;
	long long m_deleted_item;

	bool m_selling_items;
	bool m_awaiting_sell_ok;
	bool m_in_sell_building;
	long long m_sold_item;
};
