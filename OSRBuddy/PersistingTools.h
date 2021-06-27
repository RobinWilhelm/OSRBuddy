#pragma once
#include "AtumParam.h"
#include "EnchantBot.h"
#include "nlohmann/json.hpp"
#include <fstream>

class PersistingTools
{
public:
	PersistingTools();
	void SetItem(UID64_t item);
	void CloseStream();
	void PersistEnchantments(EnchantStatistics enchstats);
	EnchantStatistics PersistingTools::GetStats();
	void PersistingTools::PersistGambleCards(EnchantStatistics enchstats);
	

private:
	using json = nlohmann::json;
	std::string m_fileName;
	std::string m_workingDirectory;
	std::string m_fullpath;
    json m_j;
	std::fstream m_file;
	EnchantStatistics m_statistics;
};
