#include "osrb_pch.h"
#include "CookBook.h"
#include <vector>
#include <map>

//todo: über json füllen
CookBook::CookBook()
{
	Recipe vanillaIceCream = Recipe();
	vanillaIceCream.itemid = 7036910;
	vanillaIceCream.stackable = false;

	Ingredient milk = Ingredient();
	milk.itemnumber = 7036870;
	milk.amount = 30;

	vanillaIceCream.ingreds.push_back(milk);

	Ingredient vanilla = Ingredient();
	vanilla.itemnumber = 7036890;
	vanilla.amount = 30;

	vanillaIceCream.ingreds.push_back(vanilla);

	Ingredient egg = Ingredient();
	egg.itemnumber = 7036880;
	egg.amount = 30;

	vanillaIceCream.ingreds.push_back(egg);

	Ingredient cream = Ingredient();
	cream.itemnumber = 7036900;
	cream.amount = 30;

	vanillaIceCream.ingreds.push_back(cream);

	m_recipies.insert(std::pair<int, Recipe>(vanillaIceCream.itemid, vanillaIceCream));
}
std::map<int, Recipe> CookBook::GetRecipies()
{
	return m_recipies;
}

Recipe CookBook::getRecipie(int id)
{
	return m_recipies.at(id);
}
