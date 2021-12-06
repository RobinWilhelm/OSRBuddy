#include "osrb_pch.h"
#include "FactoryBot.h"
#include "Utility.h"
#include "PersistingTools.h"

#define RECIPE_CRAFTABLE_TEXTCOL ImColor(0x00, 0xFF, 0x00)
#define RECIPE_NOT_CRAFTABLE_TEXTCOL ImColor(0xFF, 0x00, 0x00)

namespace Features
{
	FactoryBot::FactoryBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
	{
#ifndef FACTORYBOT_USE_PEDIA_SEARCH
		// fallback to the recipe file
		LoadRecipes();
#endif // !FACTORYBOT_USE_PEDIA_SEARCH
		m_action_timer = BuddyTimer(FACTORYBOT_ACTION_TIME_BASE, FACTORYBOT_ACTION_VARIANCE);

		// add dummy item if neccessary
		if (m_mixitems.size() == 0)
		{
			m_no_recipes_found = true;
			//AddDummyItem();
			//SetSelectItem(0);
		}
		m_ongoing_request = false;
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
		if (!character_in_laboratory && m_state != FactoryBotState::DISABLED)
		{
			SetState(FactoryBotState::DISABLED);
		}

		switch (m_state)
		{
		case Features::FactoryBotState::DISABLED:
			if (character_in_laboratory)
			{
				SetState(FactoryBotState::STANDBY);
			}
			break;
		case Features::FactoryBotState::STANDBY:
			break;
		case Features::FactoryBotState::CRAFT:
			if (m_waiting_for_server)
			{
				if (TrySimulateButtonClick(LabButtonCode::Ok))
				{
					m_waiting_for_server = false;

					auto& currentRecipeInfo = GetSelectedRecipeInfo();
					currentRecipeInfo.craftable = CalculateMaxCraftableAmount(currentRecipeInfo.recipe);

					if (!m_auto_craft || !CanCraftItem(GetSelectedItem(), m_recipe_list_selected))
					{
						SetState(FactoryBotState::STANDBY);
					}
				}
			}
			else
			{
				if (m_action_timer.IsReady())
				{
					auto& currentRecipeInfo = GetSelectedRecipeInfo();
					if (m_ingredient_walker < currentRecipeInfo.recipe.ingredients.size())
					{
						const auto& nextingredient = currentRecipeInfo.recipe.ingredients[m_ingredient_walker];
						CItemInfo* nextitem = OSR_API->FindItemInInventoryByItemNum(nextingredient.itemnumber);
						if (!nextitem || nextitem->CurrentCount < nextingredient.amount)
						{
							SetState(FactoryBotState::STANDBY);
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
		ImGui::BeginDisabledMode(m_state == FactoryBotState::DISABLED || !IsEnabled());
		{
			ImGui::BeginColumns("FactoryBot2Columns", 2, ImGuiColumnsFlags_NoResize);
			{
				ImGui::SetColumnWidth(0, 250);

				ImGui::BeginChild("ItemSelectionColumn");
				{
					// render mixitems list
					ImGui::Text("Items:");
					ImGui::Separator();
#ifdef FACTORYBOT_USE_PEDIA_SEARCH
					static char textbuf[40];
					ImGui::InputText("##pediasearchtext", textbuf, 40);
					ImGui::SameLine();
					ImGui::BeginDisabledMode(m_ongoing_request);
					{
						if (ImGui::Button("Search"))
						{
							ClearRecipes();
							m_buddy->GetPediaApi()->ItemDetailRequestAsync(std::string(textbuf, 40), std::bind(&FactoryBot::ItemSearchCallback, this, std::placeholders::_1, std::placeholders::_2));
							m_ongoing_request = true;
						}
					}
					ImGui::EndDisabledMode();
#else				 					
					if (ImGui::Button("Reload Recipes")) {
						LoadRecipes();
					} 										
#endif
					if (ImGui::ListBoxHeader("##mixitemslist", ImVec2(240, 320)))
					{
						for (uint32_t i = 0; i < m_mixitems.size(); i++)
						{
							bool selected_idx = (i == m_item_list_selected);
							std::string name = Utility::string_format("%s", m_mixitems[i].itemname.GetCleanText().c_str());
							//std::string name = Utility::string_format("%s##%d", m_mixitems[i].itemname.GetCleanText(), m_mixitems[i].itemnum);
							ImGui::PushStyleColor(ImGuiCol_Text, m_mixitems[i].itemname.GetColor().Value);
							if (ImGui::Selectable(name.c_str(), &selected_idx, ImGuiSelectableFlags_None) && m_state != FactoryBotState::CRAFT)
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
					ImGui::Text("Recipe Information:");
					ImGui::Separator();

					ImGui::BeginGroup();
					//ImGui::BeginChild("RecipeIngredientsList", ImVec2(250, 0));
					{
						ImGui::Text("Target item:");
						ImGui::SameLine();
						if (!m_no_recipes_found)
						{
							GetSelectedItem().itemname.RenderImGui();
						}
						else
						{
							ImGui::Text("...");
						}

						ImGui::NewLine();
						/*
						ImGui::Text("Stackable:");
						ImGui::SameLine();
						ImGui::Text(GetSelectedItem().stackable ? "Yes" : "No");
						ImGui::NewLine();
						*/
						ImGui::Text("Select recipe:");
						if (!m_no_recipes_found)
						{
							ImGui::PushStyleColor(ImGuiCol_Text, (GetSelectedRecipeInfo().craftable > 0) ? RECIPE_CRAFTABLE_TEXTCOL.Value : RECIPE_NOT_CRAFTABLE_TEXTCOL.Value);
						}  		
						if (ImGui::BeginComboLeftSidedText("##SelectRecipeCombo", m_selected_recipe_text.c_str(), ImGuiComboFlags_None))
						{
							if (!m_no_recipes_found)
							{
								const auto& allRecipes = GetSelectedItem().recipes;
								for (uint32_t i = 0; i < allRecipes.size(); i++)
								{
									bool selected_idx = (i == m_recipe_list_selected);
									const auto& recipeInfo = allRecipes[i];

									std::string id = Utility::string_format("Recipe %d: Craftable: %d", i + 1, recipeInfo.craftable);
									ImGui::PushStyleColor(ImGuiCol_Text, (recipeInfo.craftable > 0) ? RECIPE_CRAFTABLE_TEXTCOL.Value : RECIPE_NOT_CRAFTABLE_TEXTCOL.Value);
									if (ImGui::Selectable(id.c_str(), &selected_idx) && m_state != FactoryBotState::CRAFT)
									{
										m_selected_recipe_text = id;
										m_recipe_list_selected = i;
										m_ingredient_walker = 0;
									}
									ImGui::PopStyleColor();
								}
							}
							ImGui::EndCombo();
						}
						if (!m_no_recipes_found)
						{
							ImGui::PopStyleColor();
						}
						ImGui::Text("Chance:");
						ImGui::SameLine();
						if (!m_no_recipes_found)
						{
							ImGui::Text((std::to_string(GetSelectedRecipeInfo().recipe.chance) + "%%").c_str());
						}
					}
					//ImGui::EndChild();
					ImGui::EndGroup();	 	

					ImGui::NewLine();
					if (!m_no_recipes_found)
					{
						ImGui::BeginGroup();
						//ImGui::BeginChild("RecipeIngredientsList", ImVec2(0, 0));
						{
							// render ingredients list
							ImGui::BeginColumns("Ingredientcolumns", 3, ImGuiColumnsFlags_NoResize);
							{
								ImGui::SetColumnWidth(0, 250);
								ImGui::SetColumnWidth(1, 80);
								ImGui::SetColumnWidth(1, 80);
								ImGui::Text("Ingredient");
								ImGui::NextColumn();
								ImGui::Text("Needed");
								ImGui::NextColumn();
								ImGui::Text("Inventory");
								ImGui::SeparatorEx(ImGuiSeparatorFlags_SpanAllColumns | ImGuiSeparatorFlags_Horizontal);
								ImGui::NextColumn();

								ImGui::Text("SPI");
								ImGui::NextColumn();
								ImGui::Text(std::to_string(GetSelectedRecipeInfo().recipe.cost).c_str());

								ImGui::NextColumn();

								ImGui::Text(std::to_string(OSR_API->GetInventorySPI()).c_str());
								ImGui::NextColumn();


								for (uint32_t i = 0; i < GetSelectedRecipeInfo().recipe.ingredients.size(); i++)
								{
									GetSelectedRecipeInfo().recipe.ingredients[i].itemname.RenderImGui();
									ImGui::NextColumn();

									std::string amount = std::to_string(GetSelectedRecipeInfo().recipe.ingredients[i].amount);
									ImGui::Text(amount.c_str());
									ImGui::NextColumn();

									std::string inventory = std::to_string(OSR_API->GetInventoryItemCount(GetSelectedRecipeInfo().recipe.ingredients[i].itemnumber));
									ImGui::Text(inventory.c_str());
									ImGui::NextColumn();
								}
							}
							ImGui::EndColumns();
						}
						//ImGui::EndChild();
						ImGui::EndGroup();
					}

					ImGui::NewLine();

					ImGui::Text("Control:");
					ImGui::Separator();

					ImGui::Text("Status:");
					ImGui::SameLine();
					switch (m_state)
					{
					case Features::FactoryBotState::DISABLED:
						ImGui::Text("Disabled");
						break;
					case Features::FactoryBotState::STANDBY:
						ImGui::Text("Standby");
						break;
					case Features::FactoryBotState::CRAFT:
						ImGui::Text("Crafting");
						break;
					default:
						break;
					}

					if (ImGui::Button("Mix Items") && !m_no_recipes_found)
					{
						SetState(FactoryBotState::CRAFT);
					}
					ImGui::SameLine();
					ImGui::Checkbox("Auto", &m_auto_craft);

				}
				ImGui::EndChild();

			}
			/*
			ImGui::NextColumn();
			{

				ImGui::BeginChild("ControlColumn");
				{
					ImGui::Text("Control:");
					ImGui::Separator();

					ImGui::Text("Status:");
					ImGui::SameLine();
					switch (m_state)
					{
					case Features::FactoryBotState::DISABLED:
						ImGui::Text("Disabled");
						break;
					case Features::FactoryBotState::STANDBY:
						ImGui::Text("Standby");
						break;
					case Features::FactoryBotState::CRAFT:
						ImGui::Text("Crafting");
						break;
					default:
						break;
					}
					ImGui::Checkbox("Auto", &m_auto_craft);
					if (ImGui::Button("Craft") && !m_no_recipes_found)
					{
						SetState(FactoryBotState::CRAFT);
					}
				}
				ImGui::EndChild();

			}
			*/
			ImGui::EndColumns();
		}
		ImGui::EndDisabledMode();
	}

	void FactoryBot::OnEnable()
	{
		UpdateCraftableStatusAllRecipes();
		SetSelectItem(m_item_list_selected);
	}

	void FactoryBot::SetState(FactoryBotState state)
	{
		switch (state)
		{
		case Features::FactoryBotState::DISABLED:
			Enable(false);
			m_state = state;
			break;
		case Features::FactoryBotState::STANDBY:
			m_state = state;
			break;
		case Features::FactoryBotState::CRAFT:
			if (CanCraftItem(GetSelectedItem(), m_recipe_list_selected))
			{
				m_state = state;
			}
			break;
		default:
			break;
		}
	}

	void FactoryBot::LoadRecipes()
	{
		m_mixitems.clear();
		m_state = FactoryBotState::DISABLED;
		m_buddy->GetPersistingTools()->GetAllRecipes(m_mixitems);
		if (m_mixitems.size() > 0)
		{
			m_no_recipes_found = false;
			UpdateCraftableStatusAllRecipes();
		}
		else
		{

			m_no_recipes_found = true;
			AddDummyItem();
		}
		SetSelectItem(0);
	}

	void FactoryBot::ClearRecipes()
	{
		m_no_recipes_found = true;
		m_mixitems.clear();
	}

	void FactoryBot::SetSelectItem(uint32_t list_idx)
	{
		m_item_list_selected = list_idx;
		m_recipe_list_selected = 0;

		// prefill recipe combo
		if (!m_no_recipes_found)
		{
			m_selected_recipe_text = Utility::string_format("Recipe %d: Craftable: %d", 1, GetSelectedRecipeInfo().craftable);
		}
		else
		{
			m_selected_recipe_text = Utility::string_format("Recipe %d: Craftable: %d", 0, 0);
		}

		m_ingredient_walker = 0;
	}

	MixItem& FactoryBot::GetSelectedItem()
	{
		return m_mixitems[m_item_list_selected];
	}

	RecipeInformation& FactoryBot::GetSelectedRecipeInfo()
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

	uint32_t FactoryBot::CalculateMaxCraftableAmount(const Recipe& recipe)
	{
		uint32_t max_craftable_amount = UINT_MAX;

		auto checkMaxCraftable = [&](uint32_t craftable) -> void
		{
			if (craftable <= max_craftable_amount)
			{
				max_craftable_amount = craftable;
			}
		};

		for (auto ingredient : recipe.ingredients)
		{
			uint32_t inventory_amount = OSR_API->GetInventoryItemCount(ingredient.itemnumber);
			if (inventory_amount < ingredient.amount)
			{
				return 0;
			}
			else
			{
				checkMaxCraftable(inventory_amount / ingredient.amount);
			}
		}

		if (recipe.cost > 0)
		{
			checkMaxCraftable(OSR_API->GetInventorySPI() / recipe.cost);
		}

		return max_craftable_amount;
	}

	bool FactoryBot::CanCraftItem(const MixItem& item, uint32_t recipeIdx)
	{
		if (!OSR_API->CanInsertItemToInventory(item.itemnum))
		{
			return false;
		}

		if (recipeIdx != -1)
		{
			const auto& recipe = item.recipes.at(recipeIdx);
			if (!recipe.craftable)
			{
				return false;
			}
		}
		else
		{
			for (const auto& recipe : item.recipes)
			{
				if (!recipe.craftable)
				{
					return false;
				}
			}
		}
		return true;
	}

	void FactoryBot::UpdateCraftableStatusAllRecipes()
	{
		for (auto& mixitem : m_mixitems)
		{
			for (auto& recipeinfo : mixitem.recipes)
			{
				recipeinfo.craftable = CalculateMaxCraftableAmount(recipeinfo.recipe);
			}
		}
	}

	void FactoryBot::ItemSearchCallback(bool success, std::vector<nlohmann::json>& results)
	{
		for (auto& itemdetails : results)
		{
			Features::MixItem mixitem;
			const auto& json_mi = itemdetails["pedia"];

			if (json_mi.find("mixing") != json_mi.end())
			{
				mixitem.itemnum = TO_INT(json_mi["itemDetail"]["ItemNum"]);
				mixitem.itemname = json_mi["itemDetail"]["Name"];
				mixitem.recipes.clear();

				Features::Recipe recipe;
				
				for (const auto& json_recipe : json_mi["mixing"])
				{
					recipe.chance = TO_UINT(json_recipe["Chance"]);
					recipe.cost = TO_UINT(json_recipe["Cost"]);
					recipe.ingredients.clear();

					bool has_null = false;
					Features::Ingredient ingredient;
					for (const auto& json_ingredient : json_recipe["Items"])
					{
						if (json_ingredient["Name"].is_null())
						{
							has_null = true;
							break;
						}
						ingredient.itemname = json_ingredient["Name"];
						ingredient.itemnumber = TO_INT(json_ingredient["Num"]);
						ingredient.amount = TO_UINT(json_ingredient["Count"]);
						recipe.ingredients.push_back(ingredient);						
					}

					if (recipe.ingredients.size() > 0 && !has_null)
					{
						mixitem.recipes.push_back(Features::RecipeInformation{ recipe, 0 });
					}
				}
				if (mixitem.recipes.size() > 0)
				{
					m_mixitems.push_back(mixitem);
				}
			}

		}

		if (m_mixitems.size() > 0)
		{
			UpdateCraftableStatusAllRecipes();
			SetSelectItem(0);
			m_no_recipes_found = false;
		}
		else
		{
			m_no_recipes_found = true;
		}
		m_ongoing_request = false;
	}

	void FactoryBot::AddDummyItem()
	{
		m_no_recipes_found = true;

		MixItem dummyitem;
		dummyitem.itemname = "No recipes available.";

		Recipe dummyrecipe;
		dummyrecipe.chance = 0;

		Ingredient dummyingredient;
		dummyingredient.itemname = "Nothing";
		dummyingredient.amount = 1337;

		dummyrecipe.ingredients.push_back(dummyingredient);
		dummyitem.recipes.push_back(RecipeInformation{ dummyrecipe, false });

		m_mixitems.push_back(dummyitem);
	}
}