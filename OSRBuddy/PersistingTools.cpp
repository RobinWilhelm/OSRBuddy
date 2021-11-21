#include "PersistingTools.h"
#include "EnchantBot.h"
#include "nlohmann/json.hpp"
#include <iostream>    
#include <fstream>
#include <iostream>
#include <iomanip> 
#include <stdio.h>
#include <direct.h> 

PersistingTools::PersistingTools()
{
    using json = nlohmann::json;
    char* cwd = _getcwd(0, 0); // **** microsoft specific ****
    std::string working_directory(cwd);
    std::free(cwd);
    std::string osrpart = "\\OSRBuddy";
    m_workingDirectory = working_directory.append(osrpart);
	CreateDirectory(m_workingDirectory.c_str(), NULL);
    m_workingDirectory = m_workingDirectory.append("\\Weapons");
    CreateDirectory(m_workingDirectory.c_str(), NULL);
}

void PersistingTools::SetItem(UID64_t uid) 
{
    m_fileName = std::to_string(uid) + ".json";
    m_fullpath = m_workingDirectory + "\\" + m_fileName;
    struct stat buffer;
    ZeroMemory(&m_statistics, sizeof(EnchantStatistics));

    if (stat(m_fullpath.c_str(), &buffer) == 0) 
    {
        m_file.open(m_fullpath, ios::in);
        m_file >> m_j;
        //todo: preparation for gamblecount
        m_statistics.m_used_prefixcards = (int)m_j["prefixcards"];
        m_statistics.m_used_suffixcards = (int)m_j["suffixcards"];
        try 
        {
            m_statistics.m_used_prefixwipes = (int)m_j["prefixwipes"];
            m_statistics.m_used_suffixwipes = (int)m_j["suffixwipes"];
        }
        catch (...) 
        {
            m_statistics.m_used_prefixwipes = (int)m_j["prefixwhipes"];
            m_statistics.m_used_suffixwipes = (int)m_j["suffixwhipes"];
        }
        
        for (int i = 0; i < 8; i++) 
        {
            try
            {
                std::string groupname = "E" + std::to_string(i + 5) + "-E" + std::to_string(i + 6);
                m_statistics.m_enchantStats[i][0] = (int)m_j[groupname]["tries"];
                m_statistics.m_enchantStats[i][1] = (int)m_j[groupname]["fails"];
            }
            catch(...)
            { /*Do nothing, just ignore the missing fields*/ }
        }
        m_statistics.m_used_enchprots_e1            = (int) m_j["protect1"];
        m_statistics.m_used_enchprots_e5            = (int) m_j["protect5"];
        m_statistics.m_used_enchantcards            = (int) m_j["cards"];
        try
        {
            m_statistics.m_used_speedcards          = (int) m_j["speedcards"];
            m_statistics.m_used_energyshieldcard    = (int)m_j["energyshieldcards"];
            m_statistics.m_used_chancecards_3       = (int)m_j["chancecards_3"];
            m_statistics.m_used_chancecards_5       = (int)m_j["chancecards_5"];
            m_statistics.m_used_chancecards_8       = (int)m_j["chancecards_8"];
        }
        catch (...) 
        { 
            m_statistics.m_used_speedcards = (int)m_j["specialcards"];
            m_statistics.m_used_chancecards_8 = (int)m_j["usedluckycards"];
        }  

        m_file.close();
    }
    else 
    {
        m_j["prefixwipes"] = 0;
        m_j["prefixcards"] = 0;
        m_j["suffixwipes"] = 0;
        m_j["suffixcards"] = 0;
        for (int i = 0; i < 8; i++) 
        {
            std::string groupname = "E" + std::to_string(i + 5) + "-E" + std::to_string(i + 6);
            m_j[groupname]["tries"] = 0;
            m_j[groupname]["fails"] = 0;
        }
        m_j["protect1"] = 0;
        m_j["protect5"] = 0;
        m_j["cards"] = 0;
        m_j["speedcards"] = 0;
        m_j["energyshieldcards"] = 0;
        m_j["chancecards_3"] = 0;
        m_j["chancecards_5"] = 0;
        m_j["chancecards_8"] = 0;
        ZeroMemory(&m_statistics, sizeof(EnchantStatistics));
        m_file.open(m_fullpath, ios::out);
        m_file << std::setw(4) << m_j << std::endl;
        m_file.close();
    }
}

EnchantStatistics PersistingTools::GetStats() 
{
    return m_statistics;
}

void PersistingTools::CloseStream() 
{
    if (m_file.is_open()) {
        m_file.close();
    }
}



void PersistingTools::PersistEnchantments(EnchantStatistics enchstats) 
{
    for (int i = 0; i < 8; i++) 
    {
        std::string groupname = "E" + std::to_string(i + 5) + "-E" + std::to_string(i + 6);
        m_j[groupname]["tries"] = enchstats.m_enchantStats[i][0];
        m_j[groupname]["fails"] = enchstats.m_enchantStats[i][1];
    }
    m_j["protect1"] = enchstats.m_used_enchprots_e1;
    m_j["protect5"] = enchstats.m_used_enchprots_e5;
    m_j["cards"] = enchstats.m_used_enchantcards;
    m_j["speedcards"] = enchstats.m_used_speedcards;
    m_j["energyshieldcards"] = enchstats.m_used_energyshieldcard;
    m_j["chancecards_3"] = enchstats.m_used_chancecards_3;
    m_j["chancecards_5"] = enchstats.m_used_chancecards_5;
    m_j["chancecards_8"] = enchstats.m_used_chancecards_8;
    m_file.open(m_fullpath, ios::out);
    m_file << std::setw(4) << m_j << std::endl;
    m_file.close();
}

void PersistingTools::PersistGambleCards(EnchantStatistics enchstats) 
{
    m_j["prefixwipes"] = enchstats.m_used_prefixwipes;
    m_j["prefixcards"] = enchstats.m_used_prefixcards;
    m_j["suffixwipes"] = enchstats.m_used_suffixwipes;
    m_j["suffixcards"] = enchstats.m_used_suffixcards;
    m_file.open(m_fullpath, ios::out);
    m_file << std::setw(4) << m_j << std::endl;
    m_file.close();
}