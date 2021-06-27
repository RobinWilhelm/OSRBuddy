#pragma once
#include "BuddyFeatureBase.h"
#include <vector>
#include <string>		  
#include "SDK/ObjectDefine.h"	// INVEN_DISPLAY_INFO
#include "OSRAPI.h"
#include "EnchantBot.h"


#include "OsrItemInfo.h"

#ifdef RELEASE_SETHIA
#define GAMBLEBOT_MIN_TIME_BETWEEN_GAMBLES (1500)           // minimum time between to complete gamble actions (add/remove fix) 
#define GAMBLEBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION (600)	// button clicks and item movement
#else
#define GAMBLEBOT_MIN_TIME_BETWEEN_GAMBLES (1500)           // minimum time between to complete gamble actions (add/remove fix) 
#define GAMBLEBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION (400)	// button clicks and item movement
#endif // RELEASE_SETHIA

#define COLOR_GAMBLEITEM_GT_100 (ImColor(0x00, 0xFF, 0x00).Value) // green
#define COLOR_GAMBLEITEM_LT_100 (ImColor(0xFF, 0xBB, 0x33).Value) // orange
#define COLOR_GAMBLEITEM_EQ_0	(ImColor(0xFF, 0x00, 0x00).Value) // red

class CItemInfo;

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

struct FixSelection
{
	bool		AllNonGreen;
	int			Pierce;
	int			ProbDamage;
	int			ProbReattack;
	int			ReattackDamage;
	int			Any;
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
	void DrawFullWeaponName();
	void DrawColoredGambleItemAmount(int amount);

	void SetGambleBotState(GambleBotState state);
	GambleBotState GetGambleBotState();

	void SetGambleItem(UID64_t uid);
	void ResetGambleItem();

	bool TryTargetItemToInventory();			   
	void UpdateCheckTime(float elapsedTime);
	bool GambleCheckTimeReady();
	bool InternalActionCheckTimeReady();
	void ResetGambleCheckTime(bool random = true);
	void ResetInternalActionCheckTime(bool random = true);
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

	float					m_gamble_check_time;			// time between two complete gambles	
	float					m_internal_action_check_time;	// time between two button clicks and item movement   	
	   
	int						m_amount_SG_ADV_Prefix;
	int						m_amount_SG_ADV_Suffix;
	int						m_amount_SG_STD_Prefix;
	int						m_amount_SG_STD_Suffix;
	int						m_amount_removal_Prefix;
	int						m_amount_removal_Suffix;	   
											
	FixSelection			m_suffix_selection;
	FixSelection			m_prefix_selection;		

	EnchantStatistics		m_statisticsWeapon;
};

