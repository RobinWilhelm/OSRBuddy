#pragma once
#include "BuddyFeatureBase.h"					   
#include "SDK/ObjectDefine.h"	// INVEN_DISPLAY_INFO
#include "OSRBuddyDefine.h"
#include "OSRAPI.h"

#include "OsrItemInfo.h"
#include "BuddyTimer.h"

#ifdef RELEASE_SETHIA
#define ENCHANTBOT_MIN_TIME_BETWEEN_ENCHANTS (2000)
#define ENCHANTBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION (600)	// button clicks and item movement
#else
#define ENCHANT_TIME_BASE 2000ms		
#define ENCHANT_TIME_VARIANCE 1000ms

#define ENCHANT_ACTION_TIME_BASE 300ms	// button clicks and item movement
#define ENCHANT_ACTION_TIME_VARIANCE 500ms	
#endif // RELEASE_SETHIA
						 
#define COLOR_ENCHANTITEM_GT_100 (ImColor(0x00, 0xFF, 0x00).Value) // green
#define COLOR_ENCHANTITEM_LT_100 (ImColor(0xFF, 0xBB, 0x33).Value) // orange
#define COLOR_ENCHANTITEM_EQ_0	(ImColor(0xFF, 0x00, 0x00).Value) // red



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
	int m_enchantStats[6][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };	 // total_tries, fails

	int	m_used_enchprots_e1;
	int	m_used_enchprots_e5;
	int	m_used_chancecards_8;
	int	m_used_enchantcards;
	int	m_used_speedcards;
	int m_used_energyshieldcard;

	int m_used_prefixwhipes;
	int m_used_prefixcards;
	int m_used_suffixwhipes;
	int m_used_suffixcards;

	int	m_cost_enchprots_e1;
	int	m_cost_enchprots_e5;
	int	m_cost_chancecards_8;
	int	m_cost_enchantcards;
	int	m_cost_speedcards;
	int m_cost_energyshieldcard;
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
												  
	BuddyTimer				m_enchant_timer;
	BuddyTimer				m_action_timer;

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
	bool					m_using_energyshieldcard;

	EnchantStatistics       m_statisticsSession;
	EnchantStatistics		m_statisticsWeapon;

	// for buffering
	std::string				m_cost_total_string;
	std::string				m_cost_enchprots_e1_string;
	std::string				m_cost_enchprots_e5_string;
	std::string				m_cost_chancecards_8_string;
	std::string				m_cost_enchantcards_string;
	std::string				m_cost_speedcards_string;
	std::string				m_cost_energyshieldcards_string;

	//for buffering of overall stats:
	std::string				m_cost_total_string_W;
	std::string				m_cost_enchprots_e1_string_W;
	std::string				m_cost_enchprots_e5_string_W;
	std::string				m_cost_chancecards_8_string_W;
	std::string				m_cost_enchantcards_string_W;
	std::string				m_cost_speedcards_string_W;
	std::string				m_cost_energyshieldcards_string_W;
};