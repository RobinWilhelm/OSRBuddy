#pragma once
#include "BuddyFeatureBase.h"
#include <chrono>
#include <atomic>

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

private:
	bool m_whisperwarner_active;
	bool m_whisperwarner_closeall;
	
	bool use_stealthcard;
	bool use_rabbitnecklace;
	bool use_ammobox;

	std::chrono::milliseconds m_last_whisperwarn;
	std::atomic<bool> m_popup_open;
};