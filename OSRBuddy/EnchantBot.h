#pragma once
#include "BuddyFeatureBase.h"					   
#include "SDK/ObjectDefine.h"	// INVEN_DISPLAY_INFO
#include "OSRBuddyDefine.h"
#include "OSRAPI.h"

#include "OsrItemInfo.h"

#define ENCHANTBOT_MIN_TIME_BETWEEN_ENCHANTS (1500)
#define ENCHANTBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION (400)	// button clicks and item movement

#define COLOR_ENCHANTITEM_GT_100 (ImColor(0x00, 0xFF, 0x00).Value) // green
#define COLOR_ENCHANTITEM_LT_100 (ImColor(0xFF, 0xBB, 0x33).Value) // orange
#define COLOR_ENCHANTITEM_EQ_0	(ImColor(0xFF, 0x00, 0x00).Value) // red

#define COST_ENCHANT_SINGLE 2800

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
 
struct EnchantStatistics
{
	int m_enchantStats[6][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

	int	m_used_enchprots_e1;
	int	m_used_enchprots_e5;
	int	m_used_chancecards_8;
	int	m_used_enchantcards;
	int	m_used_speedcards;

	int	m_cost_enchprots_e1;
	int	m_cost_enchprots_e5;
	int	m_cost_chancecards_8;
	int	m_cost_enchantcards;
	int	m_cost_speedcards;
	int	m_cost_total;
};

class EnchantBot : public BuddyFeatureBase
{
public:
	EnchantBot(OSRBuddyMain* buddy);
	~EnchantBot();

	// Geerbt über BuddyFeatureBase
	virtual void Tick() override;
	virtual void RenderImGui() override;
	virtual std::string GetName() const override;
	virtual FeatureType GetType() const override;
	virtual void OnEnable() override;

private:	   	
	EnchantBotState GetEnchantBotState();
	void SetEnchantBotState(EnchantBotState);
	void ResetCurrentEnchantItem();
	void ResetLab();
	void UpdateEnchantStats();

	void UpdateCheckTime(float elapsedTime);
	bool InternalActionCheckTimeReady();
	bool EnchantCheckTimeReady();
	void ResetInternalActionCheckTime(bool random = false);
	void ResetEnchantCheckTime(bool random = false);

	bool IsValidEnchantItem(ITEM_BASE* enchantItem);
	void SetEnchantItem(UID64_t uid);
	  
	void RenderSettings();
	void RenderEnchantItemText();
	void RenderEnchantButtons();
	void RenderColoredEnchantItemAmount(int amount);
	void RenderStatisticsPopup();
	void RenderSuccessPercentage(int enchstep, int total_tries, int fails);

	void ResetEnchantList(EnchantListType& enchantlist);
	void AddEnchantToList(EnchantItemType enchanttype, EnchantListType& enchantlist);

	bool DoEnchantAction(EnchantAction action);
	CItemInfo* GetEnchantItemFromInventory(EnchantItemType enchantitem, EnchantItemKind itemkind, GearType geartype);
	void UpdateEnchantItemAmount();
	void UpdateTotalCost();

	bool TrySimulateButtonClick(LabButtonCode button);
	bool TryTargetItemToInventory();

	bool EnchantFinished();	   
	EnchantAction GetNextAction();

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

	int						m_previous_enchantnum;

	// current amount of item in the inventory
	int						m_amount_enchprot_e1;
	int						m_amount_enchprot_e5;
	int						m_amount_chancecard_8;

	// true if the item is in the lab source window
	bool					m_using_enchprot_e1;
	bool					m_using_enchprot_e5;
	bool					m_using_chancecard_8;
	bool					m_using_speedcard;

	EnchantStatistics       m_statisticsSession;
	EnchantStatistics		m_statisticsWeapon;

	// for buffering
	std::string				m_cost_total_string;
	std::string				m_cost_enchprots_e1_string;
	std::string				m_cost_enchprots_e5_string;
	std::string				m_cost_chancecards_8_string;
	std::string				m_cost_enchantcards_string;
	std::string				m_cost_speedcards_string;

	//for buffering of overall stats:
	std::string				m_cost_total_string_W;
	std::string				m_cost_enchprots_e1_string_W;
	std::string				m_cost_enchprots_e5_string_W;
	std::string				m_cost_chancecards_8_string_W;
	std::string				m_cost_enchantcards_string_W;
	std::string				m_cost_speedcards_string_W;
};