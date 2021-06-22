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

	void ActivateInventoryCleaning(bool active);

private:
	void OnMessageBoxClose(int result);

	CItemInfo* FindStealthCardInInventory();  	  

	void TickWhisperWarner();
	bool InventoryActionCheckTimeReady();
	void ResetInventoryActionCheckTime();
	void TickInventoryCleaning();
	bool TryOpenCapsule(ItemNumber capsule);

private:
	bool m_whisperwarner_active;
	bool m_whisperwarner_closeall;

	bool m_use_ammobox; //todo

	std::chrono::milliseconds m_ignore_whisperwarn_time;
	std::chrono::milliseconds m_last_whisperwarn;
	std::atomic<bool> m_popup_open;


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
};