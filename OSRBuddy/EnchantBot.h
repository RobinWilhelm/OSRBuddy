#pragma once
#include "BuddyFeatureBase.h"					   
#include "SDK/ObjectDefine.h"	// INVEN_DISPLAY_INFO
#include "OSRBuddyDefine.h"
#include "OSRAPI.h"

#include "OsrItemInfo.h"


class CItemInfo;
			    
enum class EnchantItemKind
{
	Weapon_advanced = 0,
	Weapon_standard,
	Armor,
};

enum class EnchantBotState
{
	NOT_IN_LABORATORY = 0,
	STANDBY,
	ENCHANT_SINGLE,
};


enum class EnchantAction
{
	Add_EnchantItem = 0,
	Add_EnchantCard,
	Add_ProtectCard,
	Add_PercentageCard,
	Use_OkButton,
};

enum class NotifyType
{
	MISSING_ITEM = 0,
	ENCHANTING_FINISHED,
};


class EnchantBot : public BuddyFeatureBase
{
public:
	EnchantBot(OSRBuddyMain* buddy);
	~EnchantBot();

	// Geerbt über BuddyFeatureBase
	virtual void Tick() override;
	virtual void RenderImGui() override;
	virtual const char* GetName() const override;
	virtual FeatureType GetType() const override;
	virtual void OnEnable() override;

private:
	std::string GetRatio(int i, int j);
	EnchantBotState GetEnchantBotState();
	void SetEnchantBotState(EnchantBotState);
	void ResetCurrentEnchantItem();

	void UpdateCheckTime(float elapsedTime);
	bool InternalActionCheckTimeReady();
	bool EnchantCheckTimeReady();
	void ResetInternalActionCheckTime(bool random = true);
	void ResetEnchantCheckTime(bool random = true);		   	

	bool IsValidEnchantItem(ITEM_BASE* enchantItem);
	void SetEnchantItem(UID64_t uid);
	  
	void DrawSettings();
	void DrawEnchantItemText();
	void DrawEnchantButtons();

	void ResetEnchantList(EnchantListType& enchantlist);
	void AddEnchantToList(EnchantItemType enchanttype, EnchantListType& enchantlist);

	bool DoEnchantAction(EnchantAction action);
	CItemInfo* GetEnchantItemFromInventory(EnchantItemType enchantitem, EnchantItemKind itemkind, GearType geartype);
	
	bool TrySimulateButtonClick(LabButtonCode button);
	bool TryTargetItemToInventory();

	bool EnchantFinished();	   
	EnchantAction GetNextAction();

	void Notify(NotifyType type);

private:
	EnchantBotState			m_state;
	bool					m_auto_enchant;
	bool					m_optimiseEnchanting;
	bool					m_withLuckyCard;

	INVEN_DISPLAY_INFO*		m_lastSelectedItem;		
	UID64_t					m_currentEnchantItemUID;
	bool					m_selectNewEnchantItem;
	EnchantItemKind			m_enchantTargetKind;
	OsrItemInfo				m_enchant_item;		

	float					m_enchantCheckTime;
	float					m_internalActionCheckTime;	// button clicks and item movement 
	EnchantAction			m_next_action;
	bool					m_waiting_for_answer;

	EnchantListType			m_currentEnchants;
	EnchantListType			m_wantedEnchants;

	bool					m_notify_sound;
	bool					m_notify_messagebox;
	int						m_preEnch;
	int                     m_enchantStats[6][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} }; 
};