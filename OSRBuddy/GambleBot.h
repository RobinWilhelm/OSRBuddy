#pragma once
#include "BuddyFeatureBase.h"
#include <vector>
#include <string>		  
#include "SDK/ObjectDefine.h"	// INVEN_DISPLAY_INFO
#include "OSRAPI.h"

#include "OsrItemInfo.h"


class CItemInfo;

enum class GambleBotState
{
	NOT_IN_LABORATORY = 0,
	STANDBY,
	GAMBLING,
};

enum class GambleItem
{
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
	virtual const char* GetName() const override;				  
	virtual FeatureType GetType() const override;
	virtual void OnEnable() override;

private:
	void DrawSettings();
	void DrawFullWeaponName();
	void DrawColoredGambleItemAmount(int amount);

	void SetGambleBotState(GambleBotState state);
	GambleBotState GetGambleBotState();

	void SetGambleItem(UID64_t uid);
	void ResetCurrentWeapon();
	bool TryTargetItemToInventory();
	   
	void UpdateCheckTime(float elapsedTime);
	bool GambleCheckTimeReady();
	bool InternalActionCheckTimeReady();
	void ResetGambleCheckTime(bool random);
	void ResetInternalActionCheckTime(bool random);
	bool CheckRarePrefix(CItemInfo* weapon);
	bool CheckRareSuffix(CItemInfo* weapon);
	const char* GetGambleActionString(GambleAction);

	void UpdateTotalGambleItemAmount();
	int GetTotalInventoryAmount(GambleItem gambleItem);

	bool TrySimulateButtonClick(LabButtonCode button);
	bool TryGamble();
	CItemInfo* FindGambleCardItemFromInventory(GambleItem gambleitem);

	void Notify();
	bool FixIsInList(int codenum, const int* fixlist, size_t arraysize);

	bool PrepareNextGamble();
	GambleAction DetermineNextAction();

	void Reset();

private:
	GambleBotState			m_state;
	bool					m_auto_gamble;
	
	UID64_t					m_current_gambleitem_uid; // if this is 0 -> we dont have a valid gamble item	
	bool					m_select_new_weapon;

	bool					m_doPrefixGamble;
	bool					m_doSuffixGamble;
	bool					m_doPrefixGambleTemp;
	bool					m_doSuffixGambleTemp;

	GambleAction			m_nextGambleAction;
	int						m_nextActionPrepare;
	int						m_actionsToPrepareCount;
	bool					m_waiting_for_answer;

	float					m_gambleCheckTime;	
	float					m_internalActionCheckTime;	// button clicks and item movement 
 
	bool					m_isAdvancedWeapon;	
	   
	int						m_amount_SG_ADV_Prefix;
	int						m_amount_SG_ADV_Suffix;
	int						m_amount_SG_STD_Prefix;
	int						m_amount_SG_STD_Suffix;
	int						m_amount_removal_Prefix;
	int						m_amount_removal_Suffix;	   
	
	bool					m_notfiySound;
	bool					m_notfiyMB;

	FixSelection			m_SuffixSelection;
	FixSelection			m_PrefixSelection;		 

	OsrItemInfo				m_gamble_item;
};

