#pragma once
#include "AtumParam.h"
#include "nlohmann/json.hpp"

#include <memory>
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

template <typename DataType>
class IPersistData
{
public:
	virtual void Read(DataType& data) const = 0;
	virtual void Save(const DataType& data) const = 0;
};

class ItemLabStatisticsJsonPersistence : public IPersistData<ItemLabStatistics>
{
	friend class PersistingTools;
private:
	ItemLabStatisticsJsonPersistence(std::string path) { m_fullpath = path; };

public:
	// Inherited via IPersist  	
	virtual void Read(ItemLabStatistics& data) const override;
	virtual void Save(const ItemLabStatistics& data) const override;

private:
	std::string m_fullpath;
};

using LaboratoryStatsPersistingPtr = std::unique_ptr<IPersistData<ItemLabStatistics>>;

class PersistingTools
{
public:
	PersistingTools();

	LaboratoryStatsPersistingPtr GetLabStatisticPersistence(UID64_t item_uid) const;

private:
	std::string m_executable_dir;
	std::string m_osrbuddy_dir;
	std::string m_labitems_dir;
};
