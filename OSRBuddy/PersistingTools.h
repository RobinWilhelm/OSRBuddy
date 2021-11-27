#pragma once
#include "AtumParam.h"
#include "nlohmann/json.hpp"
#include "Structs.h"

#include <memory>
#include <fstream>

#define FOLDERNAME_OSRBUDDY "OSRBuddy"
#define FOLDERNAME_WEAPONS "Weapons"
#define FILENAME_RECIPES "Recipes.json"

template <typename DataType>
class IPersistData
{
public:
	virtual void Read(DataType& data) const = 0;
	virtual void Save(const DataType& data) const = 0;
};

class ItemLabStatisticsJsonPersistence : public IPersistData<Features::ItemLabStatistics>
{
	friend class PersistingTools;
private:
	ItemLabStatisticsJsonPersistence(std::string path) { m_fullpath = path; };

public:
	// Inherited via IPersist  	
	virtual void Read(Features::ItemLabStatistics& data) const override;
	virtual void Save(const Features::ItemLabStatistics& data) const override;

private:
	std::string m_fullpath;
};

using LaboratoryStatsPersistingPtr = std::unique_ptr<IPersistData<Features::ItemLabStatistics>>;

class PersistingTools
{
public:
	PersistingTools();

	LaboratoryStatsPersistingPtr GetLabStatisticPersistence(UID64_t item_uid) const;
	void GetAllRecipes(Features::MixItemList& mixitems);

private:
	std::string m_executable_dir;
	std::string m_osrbuddy_dir;
	std::string m_labitems_dir;
};
