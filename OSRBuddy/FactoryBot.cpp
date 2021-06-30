#include "FactoryBot.h"
#include "OSRBuddy.h"
#include "OSRImGuiMenu.h" 
#include "OSRAPI.h"
#include "Recipies.h"

FactoryBot::FactoryBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_state = FactoryBotState::STANDBY;
}

FactoryBot::~FactoryBot()
{
}

void FactoryBot::Tick()
{
	if (!IsEnabled()) {
		return;
	}
	bool character_in_factory = (OSR_API->GetCurrentBuildingKind() == BUILDINGKIND_FACTORY);

	switch (GetFactoryBotState())
	{
	case FactoryBotState::NOT_IN_FACTORY:
		if (character_in_factory) {
			SetFactoryBotState(FactoryBotState::STANDBY);
		}
		break;

	case FactoryBotState::STANDBY:
		break;
	case FactoryBotState::CRAFT:
		int i = 0;
		while (i <= m_wanted_amount) {
			if (DoCrafting()) 
			{
				i++;
			}
			else
			{
				SetFactoryBotState(FactoryBotState::STANDBY);
				break;
			}
		}
	}
}


void FactoryBot::RenderImGui()
{
	if (!DrawEnableCheckBox()) {
		//return;
	}
	ImGui::NewLine();
	ImGui::BeginDisabledMode(m_state == FactoryBotState::NOT_IN_FACTORY || !IsEnabled());
	{
		ImGui::BeginGroup();
		const char* items[] = { "Vanilla Ice Cream" };
		static const char* current_item = NULL;

		if (ImGui::BeginCombo("##recipie", current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				m_selected_recipie = (current_item == items[n]);
				if (ImGui::Selectable(items[n], m_selected_recipie))
				{
					current_item = items[n];
					if (m_selected_recipie) 
					{
						SetRecipie(std::to_string(current_item));
						ImGui::SetItemDefaultFocus();
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::EndGroup();
		ImGui::BeginDisabledMode(m_selected_recipie) 
		{
			ImGui::BeginGroup();
			ImGui::SliderInt();
			ImGui::EndGroup();
		}

	}
}


void FactoryBot::SetRecipe(std::string name) {
	m_transformedRecipie.clear();
	if (name == "Vanilla Ice Cream") {
		VanillaIceCream vic;
		for (int i = 0; i < vic.amounts.size(); i++) {
			Ingredient ingredient = Ingredient();
			ingredient.name = vic.ingreds(i);
			ingredient.amount = vic.amounts[i];
			m_transformedRecipie.push_back(ingredient);
		}
	}
}
bool FactoryBot::DoCrafting()
{
	return false;
}


std::string FactoryBot::GetName() const
{
	return std::string();
}

FeatureType FactoryBot::GetType() const
{
	return FeatureType::FactoryBot;
}

void FactoryBot::OnEnable()
{

}

FactoryBotState FactoryBot::GetFactoryBotState()
{
	return m_state;
}

void FactoryBot::SetFactoryBotState(FactoryBotState state)
{
	m_state = state;
}
