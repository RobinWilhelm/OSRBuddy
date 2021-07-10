#pragma once
#include <vector>
#include <map>

struct Ingredient {
	int itemnumber;
	int amount;
};

struct Recipie 
{
	std::vector<Ingredient> ingreds;
	int itemid;
	bool stackable;
};

class CookBook
{
public:
	CookBook();
	std::map<int, Recipie> GetRecipies();
	Recipie getRecipie(int id);
private:
	std::map<int, Recipie> m_recipies;
};
