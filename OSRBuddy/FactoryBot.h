#pragma once
#include "BuddyFeatureBase.h"	

enum class FactoryBotState {
	NOT_IN_FACTORY = 0,
	STANDBY,
	CRAFT
};

struct Ingredient {
	std::string name;
	int amount
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
	void SetRecipe(std::string name);
	bool DoCrafting();
	void DoStackedCrafting();

private:

	FactoryBotState m_state;
	int m_wanted_amount;
	int m_max_amount;
	bool m_open_instant;

	bool m_selected_recipie;
	bool m_stackable;

	vector<Ingredient> m_transformedRecipie;
};

