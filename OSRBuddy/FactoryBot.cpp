#include "FactoryBot.h"
#include "OSRBuddy.h"
#include "OSRImGuiMenu.h" 
#include "OSRAPI.h"
#include "CookBook.h"
#include "OSRBuddyDefine.h"
#include "Utility.h"

FactoryBot::FactoryBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_state = FactoryBotState::STANDBY;
	m_wanted_amount = 0;
	m_free_invent_space = 0;
	m_max_from_ressources = 0;
	m_max_amount = 0;
	m_stackable = false;
	m_open_instant = false;
	m_waiting_for_answer = false;
	m_walker = 0;
	m_crafted = 0;
	m_cook_book = CookBook();
	m_craft_timer = BuddyTimer(FACTORYBOT_TIME_BASE, FACTORYBOT_TIME_VARIANCE);
	m_action_timer = BuddyTimer(FACTORYBOT_ACTION_TIME_BASE, FACTORYBOT_ACTION_VARIANCE);
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

	if (m_state != FactoryBotState::NOT_IN_FACTORY && !character_in_factory)
	{
		SetFactoryBotState(FactoryBotState::NOT_IN_FACTORY);
	}

	switch (GetFactoryBotState())
	{
	case FactoryBotState::NOT_IN_FACTORY:
		if (character_in_factory) {
			SetFactoryBotState(FactoryBotState::STANDBY);
		}
		break;

	case FactoryBotState::STANDBY:
		m_selected_amount = m_wanted_amount;
		CalculateFreeInventorySpace();
		SetMaxAmount();
		SetRecipe(7036910);
	case FactoryBotState::CRAFT:
		if (m_waiting_for_answer) {
			if (TrySimulateOkButton(LabButtonCode::Ok)) 
			{
				m_waiting_for_answer = false;
				m_craft_timer.Reset();
			}
		}
		else
		{
			if (m_crafted <= m_selected_amount) {
				if (DoCrafting(m_walker))
				{
					if (m_walker == m_sizeholder) {
						m_walker = 0;
						m_crafted += 1;
						m_waiting_for_answer = true;
					}
					else {
						m_walker++;
					}
				}
			}
			else
			{
				SetFactoryBotState(FactoryBotState::STANDBY);
				break;
			}
		}
		break;
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
		{
			ImGui::SliderInt("Wanted Amount", &m_wanted_amount, 0, m_max_amount);
			if (ImGui::Button("Craft"))
			{
				if (m_state == FactoryBotState::STANDBY && m_craft_timer.IsReady()) {
						SetFactoryBotState(FactoryBotState::CRAFT);
				}
			}
		}
		ImGui::EndGroup();
	}
	ImGui::EndDisabledMode();
}


void FactoryBot::SetRecipe(int id) {
	m_ingredients_for_recipie.clear();
	m_chosen_recipie = m_cook_book.getRecipie(id);
	m_ingredients_for_recipie = m_chosen_recipie.ingreds;
	m_sizeholder = m_ingredients_for_recipie.size();
	m_stackable = m_chosen_recipie.stackable;
	CalculateMaxCraftableFromRessources();
}

bool FactoryBot::DoCrafting(int walk)
{
	if (!m_action_timer.IsReady()) {
		return false;
	}
	else {
		m_action_timer.Reset();
	}

	CItemInfo* item = nullptr;

	if (walk < m_sizeholder) {
		item = OSR_API->FindItemInInventoryByItemNum(m_ingredients_for_recipie.at(walk).itemnumber);
		if (!item)
		{
			SetFactoryBotState(FactoryBotState::STANDBY);
			return false;
		}
		OSR_API->InvenToSourceItem(item, m_ingredients_for_recipie.at(walk).amount, true);
		m_action_timer.Reset();
		return true;
	}

	else
	{
		OSR_API->OnButtonClick(TO_INT(LabButtonCode::Send), true);
		return true;
	}
	return false;
}

void FactoryBot::DoStackedCrafting()
{
}

bool FactoryBot::TrySimulateOkButton(LabButtonCode button)
{
	if (m_action_timer.IsReady())
	{
		OSR_API->OnButtonClick((int)button, true);
		m_action_timer.Reset();
		return true;
	}
	else {
		return false;
	}
}
   	   
void FactoryBot::CalculateFreeInventorySpace()
{
	int maxInvent = OSR_API->GetMaxInventorySize();
	int inventoryTaken = OSR_API->GetCurrentInventorySize();
	m_free_invent_space = maxInvent - inventoryTaken - 1;
}

void FactoryBot::CalculateMaxCraftableFromRessources()
{
	UpdateTotalGambleItemAmount();
	int hold;
	for (const auto& ingred : m_ingredients_for_recipie) {
		hold = std::floor(m_ressources_in_inventory.at(ingred.itemnumber) / ingred.amount);
		if ((m_max_from_ressources == 0 && hold > 0) || hold < m_max_from_ressources)
		{
			m_max_from_ressources = hold;
		}
	}
}

void FactoryBot::UpdateTotalGambleItemAmount()
{
	m_ressources_in_inventory.clear();
	for(const auto& ingred: m_ingredients_for_recipie)
	{
		m_ressources_in_inventory.insert(std::pair<int, int>(ingred.itemnumber, GetTotalInventoryAmount(ingred.itemnumber)));
	}
}

int FactoryBot::GetTotalInventoryAmount(int id)
{
	CItemInfo* gambleitem = OSR_API->FindItemInInventoryByItemNum(id);

	return gambleitem->CurrentCount;
}

void FactoryBot::SetMaxAmount()
{
	(m_free_invent_space > m_max_from_ressources) ? m_max_amount = m_max_from_ressources : m_max_amount = m_free_invent_space;
}


std::string FactoryBot::GetName() const
{
	return "FactoryBot Pre Alpha";
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
