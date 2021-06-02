#pragma once
#include "BuddyFeatureBase.h"
#include <chrono>
#include <atomic>

class Miscellaneous : public BuddyFeatureBase
{
public:
	Miscellaneous(OSRBuddyMain* buddy);
	~Miscellaneous();

	// Geerbt über BuddyFeatureBase
	virtual FeatureType GetType() const override;
	virtual const char* GetName() const override;
	virtual void Tick() override;
	virtual void RenderImGui() override;

	void OnMessageBoxClose(int result);

private:
	bool m_whisperwarner_active;
	std::chrono::milliseconds m_last_whisperwarn;
	std::atomic<bool> m_popup_open;
};