#include "osrb_pch.h"
#include "FactoryBot.h"
#include "Utility.h"
#include "PersistingTools.h"

namespace Features
{
	FactoryBot::FactoryBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
	{	 		
		LoadRecipes();
		m_action_timer = BuddyTimer(FACTORYBOT_ACTION_TIME_BASE, FACTORYBOT_ACTION_VARIANCE);
	}

	FactoryBot::~FactoryBot()
	{
	}

	FeatureType FactoryBot::GetType() const
	{
		return FeatureType::FactoryBot;
	}

	std::string FactoryBot::GetName() const
	{
		return "FactoryBot";
	}

	void FactoryBot::Tick()
	{
		if (!IsEnabled()) {
			return;
		}

		bool character_in_laboratory = (OSR_API->GetCurrentBuildingKind() == BUILDINGKIND_FACTORY);
		if (!character_in_laboratory && m_state != FactoryBot2State::DISABLED)
		{
			SetState(FactoryBot2State::DISABLED);
		}

		switch (m_state)
		{
		case Features::FactoryBot2State::DISABLED:
			if (character_in_laboratory)
			{
				SetState(FactoryBot2State::STANDBY);
			}
			break;
		case Features::FactoryBot2State::STANDBY:
			break;
		case Features::FactoryBot2State::CRAFT:
			if (m_waiting_for_server)
			{
				if (TrySimulateButtonClick(LabButtonCode::Ok))
				{
					m_waiting_for_server = false;
					if (!m_auto_craft)
					{
						SetState(FactoryBot2State::STANDBY);
					}
				}	 				
			}
			else
			{
				if (m_action_timer.IsReady())
				{
					if (m_ingredient_walker < GetSelectedRecipe().ingredients.size())
					{
						const auto& nextingredient = GetSelectedRecipe().ingredients[m_ingredient_walker];
						CItemInfo* nextitem = OSR_API->FindItemInInventoryByItemNum(nextingredient.itemnumber);
						if (!nextitem || nextitem->CurrentCount < nextingredient.amount)
						{
							SetState(FactoryBot2State::STANDBY);
							return;
						}

						OSR_API->InvenToSourceItem(nextitem, nextingredient.amount, true);
						m_action_timer.Reset();
						m_ingredient_walker++;
					}
					else
					{
						TrySimulateButtonClick(LabButtonCode::Send);
						m_ingredient_walker = 0;
						m_waiting_for_server = true;
					}
				}
			}
			break;
		default:
			break;
		}

	}

	void FactoryBot::RenderImGui()
	{
		DrawEnableCheckBox();
		ImGui::NewLine();
		ImGui::BeginDisabledMode(m_state == FactoryBot2State::DISABLED || !IsEnabled());
		{				
			ImGui::BeginColumns("FactoryBot2Columns", 3, ImGuiColumnsFlags_NoResize);
			{ 
				ImGui::SetColumnWidth(0, 175);
				ImGui::SetColumnWidth(1, 350);
				
				ImGui::BeginChild("ItemSelectionColumn");
				{	  					
					// render mixitems list
					ImGui::Text("Items:");
					ImGui::Separator();
					
					if (ImGui::Button("Reload Recipes")) {
						LoadRecipes();
					}
					if (ImGui::ListBoxHeader("##mixitemslist", ImVec2(160, 320)))
					{
						for (uint32_t i = 0; i < m_mixitems.size(); i++)
						{
							bool selected_idx = (i == m_item_list_selected);
							std::string name = Utility::string_format("%s##%d", m_mixitems[i].itemname.GetCleanText(), m_mixitems[i].itemnum);

							ImGui::PushStyleColor(ImGuiCol_Text, m_mixitems[i].itemname.GetColor().Value);
							if (ImGui::Selectable(name.c_str(), &selected_idx, ImGuiSelectableFlags_None) && m_state != FactoryBot2State::CRAFT)
							{
								SetSelectItem(i);
							}
							ImGui::PopStyleColor();
						}
						ImGui::ListBoxFooter();
					}					  
				}
				ImGui::EndChild(); 								
			}
			ImGui::NextColumn();
			{	   				
				ImGui::BeginChild("SelectionInformationColumn");
				{
					ImGui::Text("Selection Information:");
					ImGui::Separator();

					ImGui::BeginGroup();
					//ImGui::BeginChild("RecipeIngredientsList", ImVec2(250, 0));
					{
						ImGui::Text("Target item:");
						ImGui::SameLine();
						GetSelectedItem().itemname.RenderImGui();

						/*
						ImGui::Text("Stackable:");
						ImGui::SameLine();
						ImGui::Text(GetSelectedItem().stackable ? "Yes" : "No"); 
						ImGui::NewLine(); 											 				
						*/

						if (ImGui::BeginComboLeftSidedText("Select recipe:", m_selected_recipe_text.c_str(), ImGuiComboFlags_None))
						{
							if (m_mixitems.size() > 0)
							{ 	
								for (uint32_t i = 0; i < GetSelectedItem().recipes.size(); i++)
								{
									bool selected_idx = (i == m_recipe_list_selected);
									std::string id = Utility::string_format("Recipe %d: Chance %d%%", i + 1, GetSelectedRecipe().chance); 							
									if (ImGui::Selectable(id.c_str(), &selected_idx) && m_state != FactoryBot2State::CRAFT)
									{
										m_selected_recipe_text = id;
										m_recipe_list_selected = i;
										m_ingredient_walker = 0;
									}
								}
							}
							ImGui::EndCombo();
						}
						ImGui::Text("Cost:");
						ImGui::SameLine();
						ImGui::Text(std::to_string(GetSelectedRecipe().cost).c_str());
					}
					//ImGui::EndChild();
					ImGui::EndGroup();
					ImGui::NewLine();
					ImGui::BeginGroup();
					//ImGui::BeginChild("RecipeIngredientsList", ImVec2(0, 0));
					{
						// render ingredients list
						ImGui::BeginColumns("Ingredientcolumns", 3, ImGuiColumnsFlags_NoResize);
						{
							ImGui::SetColumnWidth(0, 200);
							ImGui::SetColumnWidth(1, 60);
							ImGui::Text("Ingredient");
							ImGui::NextColumn();
							ImGui::Text("Needed");
							ImGui::NextColumn();
							ImGui::Text("Inventory");
							ImGui::SeparatorEx(ImGuiSeparatorFlags_SpanAllColumns | ImGuiSeparatorFlags_Horizontal);
							ImGui::NextColumn();

							for (uint32_t i = 0; i < GetSelectedRecipe().ingredients.size(); i++)
							{
								GetSelectedRecipe().ingredients[i].itemname.RenderImGui();
								ImGui::NextColumn();

								std::string amount = std::to_string(GetSelectedRecipe().ingredients[i].amount);
								ImGui::Text(amount.c_str());
								ImGui::NextColumn();

								std::string inventory = std::to_string(OSR_API->GetInventoryItemCount(GetSelectedRecipe().ingredients[i].itemnumber));
								ImGui::Text(inventory.c_str());
								ImGui::NextColumn();
							}
						}
						ImGui::EndColumns();
					}
					//ImGui::EndChild();
					ImGui::EndGroup();
				}
				ImGui::EndChild();
				
			}
			ImGui::NextColumn();
			{
				
				ImGui::BeginChild("ControlColumn");
				{
					ImGui::Text("Control:");
					ImGui::Separator();

					ImGui::Text("State:");
					ImGui::SameLine();
					switch (m_state)
					{
					case Features::FactoryBot2State::DISABLED:
						ImGui::Text("Disabled");
						break;
					case Features::FactoryBot2State::STANDBY:
						ImGui::Text("Standby");
						break;
					case Features::FactoryBot2State::CRAFT:
						ImGui::Text("Crafting");
						break;
					default:
						break;
					}
					
					if(ImGui::Button("Craft") && !m_no_recipes_found)
					{
						SetState(FactoryBot2State::CRAFT);
					}
					ImGui::SameLine();
					ImGui::Checkbox("Auto", &m_auto_craft);
				}
				ImGui::EndChild();
				
			}
			ImGui::EndColumns();
		}
		ImGui::EndDisabledMode();
	}

	void FactoryBot::SetState(FactoryBot2State state)
	{
		if (!m_no_recipes_found)
		{
			m_state = state;
		}
	}

	void FactoryBot::LoadRecipes()
	{
		m_mixitems.clear();
		m_state = FactoryBot2State::DISABLED;
		m_buddy->GetPersistingTools()->GetAllRecipes(m_mixitems);
		if (m_mixitems.size() > 0)
		{
			m_no_recipes_found = false;
		}
		else
		{
			MixItem dummyitem;
			dummyitem.itemname = "No recipes available.";

			Recipe dummyrecipe;
			dummyrecipe.chance = 0;

			Ingredient dummyingredient;
			dummyingredient.itemname = "Nothing";
			dummyingredient.amount = 1337;

			dummyrecipe.ingredients.push_back(dummyingredient);
			dummyitem.recipes.push_back(dummyrecipe);

			m_mixitems.push_back(dummyitem);

			m_no_recipes_found = true;
		}
		SetSelectItem(0);
	}

	void FactoryBot::SetSelectItem(uint32_t list_idx)
	{
		m_item_list_selected = list_idx;
		m_recipe_list_selected = 0;

		// prefill recipe combo
		m_selected_recipe_text = Utility::string_format("Recipe %d: Chance %d%%", 1, GetSelectedRecipe().chance);
		m_ingredient_walker = 0;
	}

	const MixItem& FactoryBot::GetSelectedItem()
	{
		return m_mixitems[m_item_list_selected];
	}

	const Recipe& FactoryBot::GetSelectedRecipe()
	{
		return GetSelectedItem().recipes[m_recipe_list_selected];
	}

	bool FactoryBot::TrySimulateButtonClick(LabButtonCode button)
	{
		if (m_action_timer.IsReady())
		{
			OSR_API->OnButtonClick((int)button, true);
			m_action_timer.Reset();
			return true;
		}
		else 
		{
			return false;
		}
	}
}