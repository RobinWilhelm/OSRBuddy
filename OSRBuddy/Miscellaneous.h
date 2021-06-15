#pragma once
#include "BuddyFeatureBase.h"
#include <chrono>
#include <atomic>
#include "OSRBuddyDefine.h"

#define CAPSULE_OPEN_REATTACK 400ms


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

	void OnMessageBoxClose(int result);

	CItemInfo* FindStealthCardInInventory();  
	void TickCleanInventory();

private:
	bool TryOpenCapsule(ItemNumber capsule);


private:
	bool m_whisperwarner_active;
	bool m_whisperwarner_closeall;

	bool m_use_ammobox; //todo

	bool m_clean_inventory;
	bool m_only_clean_while_stopped;

	bool m_open_watermelongift;
	bool m_open_spicapsule;
	bool m_open_fantasyglobemineralcapsule;
	bool m_open_mineralcapsule;
	bool m_open_wpcapsule;

	std::chrono::milliseconds m_last_whisperwarn;
	std::atomic<bool> m_popup_open;
	std::chrono::milliseconds m_last_capsule_opened;
};