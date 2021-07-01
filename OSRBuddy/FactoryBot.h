#pragma once
#include "BuddyFeatureBase.h"	
#include "CookBook.h"
#include "OSRBuddyDefine.h"

#ifdef RELEASE_SETHIA
#define ENCHANTBOT_MIN_TIME_BETWEEN_ENCHANTS (2000)
#define ENCHANTBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION (600)	// button clicks and item movement
#else
#define FACTORYBOT_MIN_TIME_BETWEEN_CRAFTS (2100)
#define FACTORYBOT_MIN_TIME_BETWEEN_INTERNAL_ACTION (700)	// button clicks and item movement
#endif // RELEASE_SETHIA

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

	void UpdateCheckTime(float elapsedTime);
	bool InternalActionCheckTimeReady();
	bool CraftCheckTimeReady();
	void ResetInternalActionCheckTime(bool random = true);
	void ResetCraftCheckTime(bool random = true);

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

	float	m_craftCheckTime;
	float   m_internalActionCheckTime;	// button clicks and item movement 
	bool	m_waiting_for_answer;

	bool m_selected_recipie;
	bool m_stackable;

	int m_sizeholder;
	int m_walker;
	int m_crafted;

	CookBook m_cook_book;
	Recipie m_chosen_recipie;
	std::vector<Ingredient> m_ingredients_for_recipie;
	std::map<int, int> m_ressources_in_inventory;

};

