#pragma once
#include "BuddyFeatureBase.h"
#include <chrono>
#include <atomic>
#include "OSRBuddyDefine.h"
			

class CItemInfo;

class Miscellaneous : public BuddyFeatureBase
{
public:
	Miscellaneous(OSRBuddyMain* buddy);
	~Miscellaneous();

	// Geerbt über BuddyFeatureBase
	virtual FeatureType GetType() const override;
	virtual std::string GetName() const override;
	virtual void Tick() override;
	virtual void RenderImGui() override;
	virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
	virtual bool OnWritePacket(unsigned short msgtype, byte* packet) override;

	void ActivateInventoryCleaning(bool active);
	bool TrySendSellItem(CItemInfo* item, int count);

private:
	void OnMessageBoxClose(int result);
	CItemInfo* GetNextItemForDelete();	
	CItemInfo* FindStealthCardInInventory();  	  

	void TickWhisperWarner();
	bool InventoryActionCheckTimeReady();
	void ResetInventoryActionCheckTime();
	void TickInventoryCleaning();
	bool TickItemDelete();
	bool TryOpenCapsule(ItemNumber capsule);
	void TickItemSell();

private:
	bool m_whisperwarner_active;
	bool m_whisperwarner_closeall;

	bool m_use_ammobox; //todo

	bool m_whisperwarner_snooze_enabled;
	std::chrono::milliseconds m_ignore_whisperwarn_time;
	std::chrono::milliseconds m_last_whisperwarn;
	std::atomic<bool> m_popup_open;
	
	bool m_autoflip;

	std::chrono::milliseconds m_inv_action_check_time;
	bool m_clean_inventory;
	bool m_only_clean_while_stopped;
	bool m_only_clean_while_overheat;

	bool m_open_watermelongift;
	bool m_open_spicapsule;
	bool m_open_fantasyglobemineralcapsule;
	bool m_open_mineralcapsule;
	bool m_open_wpcapsule;
	bool m_open_soccer_ball_capsule;
	bool m_delete_items;
	bool m_delete_weapons;
	bool m_delete_engines;
	bool m_delete_radars;
	bool m_delete_marks;
	bool m_delete_cpus;
	int m_delete_items_maxlevel;

	bool m_awaiting_delete_ok;
	long long m_deleted_item;

	bool m_selling_items;
	std::chrono::milliseconds m_last_itemsell;
	bool m_awaiting_sell_ok;
	bool m_in_sell_building;
	long long m_sold_item;
};