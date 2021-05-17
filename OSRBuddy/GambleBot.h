#pragma once
#include "BuddyFeatureBase.h"
#include <vector>
#include <string>		  
#include "SDK/ObjectDefine.h"	// INVEN_DISPLAY_INFO
#include "OSRAPI.h"


class CItemInfo;

enum class GambleBotState
{
	NOT_IN_LABORATORY = 0,
	STANDBY,
	WAIT_FOR_TARGET,
	GAMBLE_SINGLE,
	GAMBLE_AUTOMATIC, 
	RESET
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
	void ReturnToPreviousGambleBotState();

	void SetGambleItem(CItemInfo* gambleItem);
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
	bool DetermineNextAction();

private:
	GambleBotState			m_state;
	GambleBotState			m_prev_state;
	INVEN_DISPLAY_INFO*		m_lastSelectedItem;
	CItemInfo*				m_lastSelectedItemInfo;
	
	std::string				m_fullItemName;
	CItemInfo*				m_currentGambleItem;
	UID64_t					m_currentGambleItemUID;	
	bool					m_selectNewWeapon;

	bool					m_doPrefixGamble;
	bool					m_doSuffixGamble;
	bool					m_doPrefixGambleTemp;
	bool					m_doSuffixGambleTemp;

	GambleAction			m_nextGambleAction;
	int						m_nextActionPrepare;
	int						m_actionsToPrepareCount;

	float					m_gambleCheckTime;	
	float					m_internalActionCheckTime;	// button clicks and item movement 
 
	bool					m_isAdvancedWeapon;
	std::string				m_weaponName;
	std::string				m_prefixName;
	std::string				m_suffixName;
	ImColor					m_prefixColor;
	ImColor					m_suffixColor;
	   
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
};

