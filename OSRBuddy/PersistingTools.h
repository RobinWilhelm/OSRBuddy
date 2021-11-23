#pragma once
#include "AtumParam.h"
#include "nlohmann/json.hpp"

#include <fstream>

struct ItemLabStatistics
{
	uint32_t m_enchantStats[8][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };	 // total_tries, fails

	uint32_t	m_used_enchprots_e1;
	uint32_t	m_used_enchprots_e5;

	uint32_t	m_used_chancecards_3;
	uint32_t	m_used_chancecards_5;
	uint32_t	m_used_chancecards_8;

	uint32_t	m_used_enchantcards;
	uint32_t	m_used_speedcards;
	uint32_t	m_used_energyshieldcard;

	uint32_t	m_used_prefixwipes;
	uint32_t	m_used_prefixcards;
	uint32_t	m_used_suffixwipes;
	uint32_t	m_used_suffixcards;

	uint32_t	m_cost_enchprots_e1;
	uint32_t	m_cost_enchprots_e5;

	uint32_t	m_cost_chancecards_3;
	uint32_t	m_cost_chancecards_5;
	uint32_t	m_cost_chancecards_8;

	uint32_t	m_cost_enchantcards;
	uint32_t	m_cost_speedcards;
	uint32_t	m_cost_energyshieldcard;
	uint32_t	m_cost_total;
};


class PersistingTools
{
public:
	PersistingTools();
	void SetItem(UID64_t item);
	void CloseStream();
	void PersistEnchantments(ItemLabStatistics enchstats);
	ItemLabStatistics PersistingTools::GetStats();
	void PersistingTools::PersistGambleCards(ItemLabStatistics enchstats);
	

private:
	using json = nlohmann::json;
	std::string m_fileName;
	std::string m_workingDirectory;
	std::string m_fullpath;
    json m_j;
	std::fstream m_file;
	ItemLabStatistics m_statistics;
};
