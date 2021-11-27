#pragma once
#include "BuddyFeatureBase.h"
#include "imgui/imgui_addition.h"
#include "AceColouredString.h"
#include "Structs.h"			  

#define FACTORYBOT_ACTION_TIME_BASE 300ms	// button clicks and item movement
#define FACTORYBOT_ACTION_VARIANCE 500ms	

namespace Features
{
	enum class FactoryBot2State 
	{
		DISABLED = 0,
		STANDBY,
		CRAFT
	};

	class FactoryBot : public BuddyFeatureBase
	{
	public:
		FactoryBot(OSRBuddyMain* buddy);
		~FactoryBot();

		// Inherited via BuddyFeatureBase
		virtual FeatureType GetType() const override;
		virtual std::string GetName() const override;
		virtual void Tick() override;
		virtual void RenderImGui() override;

		void SetState(FactoryBot2State state);
		uint32_t GetInventoryItemAmount(uint32_t itemnum);
		void LoadRecipes();
		
		void SetSelectItem(uint32_t list_idx);
		const MixItem& GetSelectedItem();				// returns currently selected item in the list
		const Recipe& GetSelectedRecipe();

		bool TrySimulateButtonClick(LabButtonCode button);

	private:
		FactoryBot2State		m_state;
		bool					m_auto_craft;
		bool					m_waiting_for_server;
		uint32_t				m_ingredient_walker;
		BuddyTimer				m_action_timer;

		MixItemList				m_mixitems;				// all current elements in the itemlist	and recipelist
		uint32_t				m_item_list_selected;	// the selected item in the itemlist
		uint32_t				m_recipe_list_selected;	// the selected recipe from the recipelist
		bool					m_no_recipes_found;

		std::string				m_selected_recipe_text;
	};
}