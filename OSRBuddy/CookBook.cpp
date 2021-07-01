#include "CookBook.h"
#include <vector>
#include <map>

//todo: über json füllen
CookBook::CookBook()
{
	Recipie vanillaIceCream = Recipie();
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

	m_recipies.insert(std::pair<int, Recipie>(vanillaIceCream.itemid, vanillaIceCream));
}
std::map<int, Recipie> CookBook::GetRecipies()
{
	return m_recipies;
}

Recipie CookBook::getRecipie(int id)
{
	return m_recipies.at(id);
}
