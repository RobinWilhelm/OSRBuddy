#pragma once
#include "BuddyFeatureBase.h"					   
#include "SDK/ObjectDefine.h"	// INVEN_DISPLAY_INFO
#include "OSRBuddyDefine.h"
#include "OSRAPI.h"
#include "Structs.h"

#include "PersistingTools.h"
#include "OsrItemInfo.h"
#include "BuddyTimer.h"
#include "imgui/imgui_addition.h"

#ifdef RELEASE_SETHIA
#define ENCHANT_TIME_BASE 2200ms		
#define ENCHANT_TIME_VARIANCE 1000ms

#define ENCHANT_ACTION_TIME_BASE 400ms	// button clicks and item movement
#define ENCHANT_ACTION_TIME_VARIANCE 500ms	
#else
#define ENCHANT_TIME_BASE 1500ms		
#define ENCHANT_TIME_VARIANCE 1000ms

#define ENCHANT_ACTION_TIME_BASE 200ms	// button clicks and item movement
#define ENCHANT_ACTION_TIME_VARIANCE 300ms	
#endif // RELEASE_SETHIA
						 
#define COLOR_ENCHANTITEM_GT_100 (ImColor(0x00, 0xFF, 0x00).Value) // green
#define COLOR_ENCHANTITEM_LT_100 (ImColor(0xFF, 0xBB, 0x33).Value) // orange
#define COLOR_ENCHANTITEM_EQ_0	(ImColor(0xFF, 0x00, 0x00).Value) // red

class CItemInfo;

namespace Features
{
	enum class EnchantCard : uint32_t
	{
		None,
		Accuracy,
		Reattack,
		MinMax,
		Speed,
		Overheating,
		Range,
		Time,
		Weight,
		Shield,
		Energy,
		EnergyShield,
	};

	enum class EnchantProtect : uint32_t
	{
		None,
		E1,
		E5,
	};

	enum class EnchantChance : uint32_t
	{
		None,
		Percent_3,
		Percent_5,
		Percent_8,
	};

	struct EnchantInformation
	{
		EnchantInformation()
		{
			enchant = EnchantCard::None;
			protect = EnchantProtect::None;
			chance = EnchantChance::None;
		}

		EnchantCard enchant;
		EnchantProtect protect;
		EnchantChance chance;
	};

	using EnchantInfoList = std::vector<EnchantInformation>;

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



	struct EnchantCardsAmount
	{
		int accuracy;
		int reattack;
		int	damage;
		int	speed;
		int overheat;
		int range;
		int time;
		int weight;
		int shield;
		int energy;
		int energyshield;
	};

	struct EnchantCostBuffer
	{
		std::string	m_cost_total;
		std::string	m_cost_enchprots_e1;
		std::string	m_cost_enchprots_e5;
		std::string	m_cost_chancecards_3;
		std::string	m_cost_chancecards_5;
		std::string	m_cost_chancecards_8;
		std::string	m_cost_enchantcards;
		std::string	m_cost_speedcards;
		std::string	m_cost_energyshieldcards;
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
		void UpdateInventoryEnchantCards();

		bool IsValidEnchantItem(ITEM_BASE* enchantItem);
		void SetNewEnchantItem(UID64_t uid);

		void RenderSettings();
		void RenderEnchantButtons();
		void RenderColoredEnchantItemAmount(int amount);
		void RenderStatisticsPopup();
		void RenderSuccessPercentage(int enchstep, int total_tries, int fails);

		void ResetEnchantList(ImGui::ListVector& enchantlist);
		void InsertEnchantList(ImGui::ListVector& enchantlist, EnchantCard enchanttype);
		void RemoveEnchantEntry(uint32_t enchantindex);
		void RebuildWantedEnchantDisplayList();
		void RebuildCurrentEnchantDisplayList();

		bool DoEnchantAction(EnchantAction action);
		static CItemInfo* GetEnchantItemFromInventory(EnchantCard enchantitem, EnchantItemKind itemkind, GearType geartype);
		static CItemInfo* GetEnchantItemFromInventory(EnchantProtect enchantitem);
		static CItemInfo* GetEnchantItemFromInventory(EnchantChance enchantitem);
		void UpdateEnchantItemAmount();
		void UpdateTotalCost();

		bool TrySimulateButtonClick(LabButtonCode button);
		bool TryTargetItemToInventory();

		bool EnchantFinished();
		EnchantAction GetNextAction();
		void AddLastEnchantToStatistic(const EnchantInformation& enchantinfo);

		static std::string GetEnchantItemText(EnchantCard enchantcard);
		static std::string GetEnchantItemText(EnchantChance enchantchance);
		static std::string GetEnchantItemText(EnchantProtect enchantprotect);

		void SetOptimizedEnchantSettings(bool optimized);

		void StartEnchantResultLog();
		void StopEnchantResultLog();

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

		ImGui::ListVector		m_currentEnchantDisplayList;
		ImGui::ListVector		m_wantedEnchantDisplayList;
		EnchantInfoList			m_wantedEnchantInfo;

		int						m_wanted_enchants_sel_idx;

		uint32_t				m_previous_enchantnum;

		EnchantCardsAmount		m_inventory_enchantcards;

		// current amount of item in the inventory
		uint32_t				m_amount_enchprot_e1;
		uint32_t				m_amount_enchprot_e5;
		uint32_t				m_amount_chancecard_3;
		uint32_t				m_amount_chancecard_5;
		uint32_t				m_amount_chancecard_8;

		// true if the item is in the lab source window
		bool					m_using_enchprot_e1;
		bool					m_using_enchprot_e5;
		bool					m_using_chancecard_8;
		bool					m_using_speedcard;
		bool					m_using_energyshieldcard;

		LaboratoryStatsPersistingPtr	m_item_persisting;
		ItemLabStatistics       m_statisticsSession;
		ItemLabStatistics		m_statisticsWeapon;

		bool					m_statistics_popup_open;

		// for buffering strings that change semi often
		EnchantCostBuffer		m_cost_session;
		EnchantCostBuffer		m_cost_weapon;

		// log enchant result for randomness breaker
		bool					m_er_log_active;
		nlohmann::json			m_er_log_json;
		EnchantResultPersistingPtr	m_er_persisting;
		float					m_total_entropy;
	};
}