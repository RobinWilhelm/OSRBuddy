#pragma once
#include "BuddyFeatureBase.h"	
#include "CookBook.h"
#include "OSRBuddyDefine.h"
#include "BuddyTimer.h"

#ifdef RELEASE_SETHIA
#define FACTORYBOT_TIME_BASE 2000ms           // minimum time between to complete gamble actions (add/remove fix) 
#define FACTORYBOT_TIME_VARIANCE 500ms

#define FACTORYBOT_ACTION_TIME_BASE 300ms	// button clicks and item movement
#define FACTORYBOT_ACTION_VARIANCE 500ms	
#else  	
#define FACTORYBOT_TIME_BASE 2000ms           // minimum time between to complete gamble actions (add/remove fix) 
#define FACTORYBOT_TIME_VARIANCE 500ms

#define FACTORYBOT_ACTION_TIME_BASE 300ms	// button clicks and item movement
#define FACTORYBOT_ACTION_VARIANCE 500ms	  
#endif // RELEASE_SETHIA

namespace Features
{
	enum class FactoryBotState {
		NOT_IN_FACTORY = 0,
		STANDBY,
		CRAFT
	};

	class FactoryBot : public BuddyFeatureBase
	{
	public:
		FactoryBot(OSRBuddyMain* buddy);
		~FactoryBot();

		// Geerbt über BuddyFeatureBase
		virtual void Tick() override;
		virtual void RenderImGui() override;
		virtual std::string GetName() const override;
		virtual FeatureType GetType() const override;
		virtual void OnEnable() override;

	private:
		FactoryBotState GetFactoryBotState();
		void SetFactoryBotState(FactoryBotState);
		void SetRecipe(int id);
		bool DoCrafting(int walk);
		void DoStackedCrafting();
		bool TrySimulateOkButton(LabButtonCode code);

		void CalculateFreeInventorySpace();
		void CalculateMaxCraftableFromRessources();
		void UpdateTotalGambleItemAmount();
		int  GetTotalInventoryAmount(int id);
		void SetMaxAmount();

	private:

		FactoryBotState m_state;
		int m_wanted_amount;
		int m_selected_amount;
		int m_free_invent_space;
		int m_max_from_ressources;
		int m_max_amount;
		bool m_open_instant;

		BuddyTimer m_craft_timer;
		BuddyTimer m_action_timer;
		bool	m_waiting_for_answer;

		bool m_selected_recipie;
		bool m_stackable;

		int m_sizeholder;
		int m_walker;
		int m_crafted;

		CookBook m_cook_book;
		Recipe m_chosen_recipie;
		std::vector<Ingredient> m_ingredients_for_recipie;
		std::map<int, int> m_ressources_in_inventory;

	};
}
