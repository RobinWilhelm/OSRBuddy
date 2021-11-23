#pragma once
#include "BuddyFeatureBase.h"

#include "OSRBuddyDefine.h"
#include "BuddyTimer.h"
#include "ImComboBox.h"

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

	void ActivateAutoFlip(bool on);
	void ActivateAutoAmmo(bool on);
	void ActivateAutoStealthcard(bool on);

	void UpdateCharmsComboBox();
	bool CheckCharmItemIsAvailable(uint32_t itemnumber);

private:
	void OnMessageBoxClose(int result);
	CItemInfo* FindStealthCardInInventory();  	  

	void TickWhisperWarner();
	void TickAutoFlip();
	void TickBossWarner();
	void TickAutoStealthcard();
	void TickAutoAmmo();
	void TickAutoRabbit();
	void TickAutoCharm();

private:
	bool m_whisperwarner_active;
	bool m_whisperwarner_closeall;

	bool m_autocharms_active;
	
	std::vector<ImGui::ComboItem> m_combo_items;
	ImGui::ComboItem m_selected_combo_item;

	bool m_use_ammobox;
	bool m_use_stealthcard;
	bool m_use_rabbit;

	bool m_awaiting_server_ok_ammobox;
	bool m_awaiting_server_ok_rabbit;
	bool m_awaiting_server_ok_stealthcard;

	bool m_whisperwarner_snooze_enabled;
	std::chrono::milliseconds m_ignore_whisperwarn_time;
	std::atomic<bool> m_whisper_popup_open;
	
	BuddyTimer m_whisper_timer;
	BuddyTimer m_bosscheck_timer;
	BuddyTimer m_autoitems_timer;
	BuddyTimer m_update_charms_timer;

	bool m_autoflip;
	bool m_bosswarner;
	bool m_boss_popup_open;
};