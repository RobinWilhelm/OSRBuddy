#pragma once
#include <vector>
#include <map>

struct Ingredient 
{
	int itemnumber;
	int amount;
};

struct Recipe 
{
	std::vector<Ingredient> ingreds;
	int itemid;
	bool stackable;
};

class CookBook
{
public:
	CookBook();
	std::map<int, Recipe> GetRecipies();
	Recipe getRecipie(int id);
private:
	std::map<int, Recipe> m_recipies;
};
