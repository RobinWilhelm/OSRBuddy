#pragma once
#include <Windows.h>
#include <vector>
#include "AceColouredString.h"

namespace Features
{
	struct ItemLabStatistics
	{
		uint32_t m_enchantStats[8][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };	 // total_tries, fails

		uint32_t m_used_enchprots_e1 = 0;
		uint32_t m_used_enchprots_e5 = 0;

		uint32_t m_used_chancecards_3 = 0;
		uint32_t m_used_chancecards_5 = 0;
		uint32_t m_used_chancecards_8 = 0;

		uint32_t m_used_enchantcards = 0;
		uint32_t m_used_speedcards = 0;
		uint32_t m_used_energyshieldcard = 0;

		uint32_t m_used_prefixwipes = 0;
		uint32_t m_used_prefixcards = 0;
		uint32_t m_used_suffixwipes = 0;
		uint32_t m_used_suffixcards = 0;

		uint64_t m_cost_enchprots_e1 = 0;
		uint64_t m_cost_enchprots_e5 = 0;

		uint64_t m_cost_chancecards_3 = 0;
		uint64_t m_cost_chancecards_5 = 0;
		uint64_t m_cost_chancecards_8 = 0;

		uint64_t m_cost_enchantcards = 0;
		uint64_t m_cost_speedcards = 0;
		uint64_t m_cost_energyshieldcard = 0;
		uint64_t m_cost_total = 0;
	};

	struct EnchantResult
	{
		uint8_t try_enchant_to;
		bool success;
	};



	struct Ingredient
	{
		INT itemnumber = 0;
		uint32_t amount = 0;
		AceColouredString itemname;
	};

	struct Recipe
	{
		uint32_t chance = 0;
		uint32_t cost = 0;
		std::vector<Ingredient> ingredients;
	};

	struct RecipeInformation
	{
		Recipe recipe;
		uint32_t craftable;
	};

	struct MixItem
	{
		INT itemnum = 0;
		//bool stackable;
		AceColouredString itemname;
		std::vector<RecipeInformation> recipes;
	};

	using MixItemList = std::vector<MixItem>;
}