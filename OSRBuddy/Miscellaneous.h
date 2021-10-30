#pragma once
#include "BuddyFeatureBase.h"
#include <chrono>
#include <atomic>
#include "OSRBuddyDefine.h"
#include "BuddyTimer.h"

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
	void TickInventoryCleaning();
	void TickCapsuleOpening();
	bool TickItemDelete();
	bool TryOpenCapsule(ItemNumber capsule);
	void TickItemSell();
	void TickAutoFlip();
	void TickBossWarner();
	void TickAutoStealthcard();
	void TickAutoAmmo();

	bool TryUseAmmunitionBox();

private:
	bool m_whisperwarner_active;
	bool m_whisperwarner_closeall;

	bool m_use_ammobox;
	bool m_use_stealthcard;
	

	bool m_awaiting_server_ok_ammobox;
	bool m_whisperwarner_snooze_enabled;
	std::chrono::milliseconds m_ignore_whisperwarn_time;
	std::atomic<bool> m_whisper_popup_open;
	
	BuddyTimer m_inventory_action_timer;
	BuddyTimer m_whisper_timer;
	BuddyTimer m_itemsell_timer;
	BuddyTimer m_bosscheck_timer;
	BuddyTimer m_autoitems_timer;

	bool m_autoflip;
	bool m_bosswarner;
	bool m_boss_popup_open;

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

	bool m_awaiting_delete_ok;
	long long m_deleted_item;

	bool m_selling_items;
	bool m_awaiting_sell_ok;
	bool m_in_sell_building;
	long long m_sold_item;
};