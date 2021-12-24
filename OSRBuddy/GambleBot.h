#pragma once
#include "BuddyFeatureBase.h"
	  
#include "SDK/ObjectDefine.h"	// INVEN_DISPLAY_INFO
#include "OSRAPI.h"
#include "BuddyTimer.h"
#include "OsrItemInfo.h"
#include "PersistingTools.h"
#include "Structs.h"

#include <vector>
#include <string>	

#ifdef RELEASE_SETHIA
#define GAMBLE_TIME_BASE 2000ms           // minimum time between to complete gamble actions (add/remove fix) 
#define GAMBLE_TIME_VARIANCE 600ms

#define GAMBLE_ACTION_TIME_BASE 400ms	// button clicks and item movement
#define GAMBLE_ACTION_VARIANCE 600ms	
#else
#define GAMBLE_TIME_BASE 1000ms           // minimum time between to complete gamble actions (add/remove fix) 
#define GAMBLE_TIME_VARIANCE 1000ms

#define GAMBLE_ACTION_TIME_BASE 400ms	// button clicks and item movement
#define GAMBLE_ACTION_VARIANCE 400ms	
#endif // RELEASE_SETHIA

#define COLOR_GAMBLEITEM_GT_100 (ImColor(0x00, 0xFF, 0x00).Value) // green
#define COLOR_GAMBLEITEM_LT_100 (ImColor(0xFF, 0xBB, 0x33).Value) // orange
#define COLOR_GAMBLEITEM_EQ_0	(ImColor(0xFF, 0x00, 0x00).Value) // red

class CItemInfo;

namespace Features
{
	enum class GambleBotState
	{
		NOT_IN_LABORATORY = 0,
		STANDBY,
		GAMBLING,
	};

	enum class GambleItem
	{
		SOURCE_ITEM,
		SG_ADV_PREFIX,
		SG_ADV_SUFFIX,
		SG_STD_PREFIX,
		SG_STD_SUFFIX,
		INIT_PREFIX,
		INIT_SUFFIX
	};

	enum class GambleAction
	{
		NONE,
		ADD_PREFIX,
		ADD_SUFFIX,
		ADD_PREFIX_AND_SUFFIX,
		REMOVE_PREFIX,
		REMOVE_SUFFIX,
		REMOVE_PREFIX_AND_SUFFIX,
	};

	enum class FixCategory
	{
		None,
		Good,
		Best,
	};

	struct FixSelection
	{
		bool AllNonGreen;
		FixCategory	Pierce;
		FixCategory	ProbDamage;
		FixCategory	ProbReattack;
		FixCategory	ReattackDamage;
		FixCategory	Any;
	};


	class GambleBot :
		public BuddyFeatureBase
	{
	public:
		GambleBot(OSRBuddyMain* buddy);
		~GambleBot();

		// Geerbt über BuddyFeatureBase
		virtual void Tick() override;
		virtual void RenderImGui() override;
		virtual std::string GetName() const override;
		virtual FeatureType GetType() const override;
		virtual void OnEnable() override;

	private:
		//bool PrepareNextGamble();
		bool TryDoGambleAction();
		GambleAction DetermineNextAction();
		void AddNeededSourceItems(GambleAction action);
		void Reset();

		void DrawSettings();
		void DrawColoredGambleItemAmount(int amount);

		void SetGambleBotState(GambleBotState state);
		GambleBotState GetGambleBotState();

		void SetGambleItem(UID64_t uid);
		void ResetGambleItem();

		bool TryTargetItemToInventory();
		bool CheckRarePrefix(CItemInfo* weapon);
		bool CheckRareSuffix(CItemInfo* weapon);
		const char* GetGambleActionString(GambleAction);
		void UpdateTotalGambleItemAmount();
		int GetTotalInventoryAmount(GambleItem gambleItem);
		bool TrySimulateButtonClick(LabButtonCode button);
		CItemInfo* FindGambleItemFromInventory(GambleItem gambleitem);

	private:
		GambleBotState			m_state;
		bool					m_auto_gamble;

		UID64_t					m_current_gambleitem_uid; // if this is 0 -> we dont have a valid gamble item	
		OsrItemInfo				m_gamble_item;
		bool					m_is_advanced_weapon;
		bool					m_select_new_weapon;

		bool					m_do_prefix_gamble;
		bool					m_do_suffix_gamble;
		bool					m_do_prefix_gamble_temp;
		bool					m_do_suffix_gamble_temp;

		bool					m_persist_prefix_whipe;
		bool					m_persist_suffix_whipe;
		bool					m_persist_prefix_card;
		bool					m_persist_suffix_card;

		GambleAction			m_next_gamble_action;
		std::queue<GambleItem>	m_needed_source_items;
		bool					m_waiting_for_answer;

		BuddyTimer				m_gamble_timer;		// time between two complete gambles	
		BuddyTimer				m_action_timer;		// time between two button clicks and item movement  

		float					m_gamble_check_time;
		float					m_internal_action_check_time;

		uint32_t				m_amount_SG_ADV_Prefix;
		uint32_t				m_amount_SG_ADV_Suffix;
		uint32_t				m_amount_SG_STD_Prefix;
		uint32_t				m_amount_SG_STD_Suffix;
		uint32_t				m_amount_removal_Prefix;
		uint32_t				m_amount_removal_Suffix;

		FixSelection			m_suffix_selection;
		FixSelection			m_prefix_selection;

		LaboratoryStatsPersistingPtr	m_item_persisting;
		ItemLabStatistics		m_statisticsWeapon;
	};
}
