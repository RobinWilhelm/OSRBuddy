#include "osrb_pch.h"
#include "PersistingTools.h"
#include "nlohmann/json.hpp"

#include <iostream>    
#include <fstream>
#include <iostream>
#include <iomanip> 
#include <stdio.h>
#include <direct.h> 

PersistingTools::PersistingTools()
{
    char* cwd = _getcwd(0, 0); // **** microsoft specific ****
    m_executable_dir = std::string(cwd);
    std::free(cwd);

    std::string osrpart = "\\OSRBuddy";
    m_osrbuddy_dir = m_executable_dir.append(osrpart);
	CreateDirectory(m_osrbuddy_dir.c_str(), NULL);

    m_labitems_dir = m_osrbuddy_dir.append("\\Weapons");
    CreateDirectory(m_labitems_dir.c_str(), NULL);
}

 /*
void PersistingTools::SetItem(UID64_t uid) 
{
    m_fileName = std::to_string(uid) + ".json";
    m_fullpath = m_workingDirectory + "\\" + m_fileName;
    struct stat buffer;
    ZeroMemory(&m_statistics, sizeof(ItemLabStatistics));

    // check if file already exists, if not -> create it with default values
    if (stat(m_fullpath.c_str(), &buffer) != 0) 
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
        ZeroMemory(&m_statistics, sizeof(ItemLabStatistics));
        m_file.open(m_fullpath, ios::out);
        m_file << std::setw(4) << m_j << std::endl;
        m_file.close();
    }
    m_current_item_id = uid;
}

void PersistingTools::ReadItemLabStatistics(ItemLabStatistics& stats)
{
    if (m_current_item_id == 0 || m_fullpath.empty()) 
    {
        ZeroMemory(&stats, sizeof(ItemLabStatistics));
        return;
    }

    m_file.open(m_fullpath, ios::in);
    m_file >> m_j;
    //todo: preparation for gamblecount
    stats.m_used_prefixcards = (int)m_j["prefixcards"];
    stats.m_used_suffixcards = (int)m_j["suffixcards"];
    try
    {
        stats.m_used_prefixwipes = (int)m_j["prefixwipes"];
        stats.m_used_suffixwipes = (int)m_j["suffixwipes"];
    }
    catch (...)
    {
        stats.m_used_prefixwipes = (int)m_j["prefixwhipes"];
        stats.m_used_suffixwipes = (int)m_j["suffixwhipes"];
    }

    for (int i = 0; i < 8; i++)
    {
        try
        {
            std::string groupname = "E" + std::to_string(i + 5) + "-E" + std::to_string(i + 6);
            stats.m_enchantStats[i][0] = (int)m_j[groupname]["tries"];
            stats.m_enchantStats[i][1] = (int)m_j[groupname]["fails"];
        }
        catch (...)
        { 
        }
    }
    stats.m_used_enchprots_e1 = (int)m_j["protect1"];
    stats.m_used_enchprots_e5 = (int)m_j["protect5"];
    stats.m_used_enchantcards = (int)m_j["cards"];
    try
    {
        stats.m_used_speedcards = (int)m_j["speedcards"];
        stats.m_used_energyshieldcard = (int)m_j["energyshieldcards"];
        stats.m_used_chancecards_3 = (int)m_j["chancecards_3"];
        stats.m_used_chancecards_5 = (int)m_j["chancecards_5"];
        stats.m_used_chancecards_8 = (int)m_j["chancecards_8"];
    }
    catch (...)
    {
        stats.m_used_speedcards = (int)m_j["specialcards"];
        stats.m_used_chancecards_8 = (int)m_j["usedluckycards"];
    }

    m_file.close();
}

void PersistingTools::CloseStream()
{
    if (m_file.is_open()) {
        m_file.close();
    }
}



void PersistingTools::SaveItemLabStatistics(const ItemLabStatistics& statistics)
{
    for (int i = 0; i < 8; i++)
    {
        std::string groupname = "E" + std::to_string(i + 5) + "-E" + std::to_string(i + 6);
        m_j[groupname]["tries"] = statistics.m_enchantStats[i][0];
        m_j[groupname]["fails"] = statistics.m_enchantStats[i][1];
    }
    m_j["protect1"] = statistics.m_used_enchprots_e1;
    m_j["protect5"] = statistics.m_used_enchprots_e5;
    m_j["cards"] = statistics.m_used_enchantcards;
    m_j["speedcards"] = statistics.m_used_speedcards;
    m_j["energyshieldcards"] = statistics.m_used_energyshieldcard;
    m_j["chancecards_3"] = statistics.m_used_chancecards_3;
    m_j["chancecards_5"] = statistics.m_used_chancecards_5;
    m_j["chancecards_8"] = statistics.m_used_chancecards_8;

    m_j["prefixwipes"] = statistics.m_used_prefixwipes;
    m_j["prefixcards"] = statistics.m_used_prefixcards;
    m_j["suffixwipes"] = statistics.m_used_suffixwipes;
    m_j["suffixcards"] = statistics.m_used_suffixcards;

    m_file.open(m_fullpath, ios::out);
    m_file << std::setw(4) << m_j << std::endl;
    m_file.close();
}
*/

ItemLabPersistingPtr PersistingTools::GetLabStatisticPersistence(UID64_t item_uid) const
{
    std::string fullpath = m_labitems_dir + "\\" + std::to_string(item_uid) + ".json";

    auto ptr = new ItemLabStatisticsJsonPersistence(fullpath);
    // check if file already exists, if not -> create it with empty values
    struct stat buffer;
    if (stat(fullpath.c_str(), &buffer) != 0)
    {
        ItemLabStatistics stats;
        ZeroMemory(&stats, sizeof(ItemLabStatistics));
        ptr->Save(stats);
    }

    return std::unique_ptr<ItemLabStatisticsJsonPersistence>(ptr);
}

void ItemLabStatisticsJsonPersistence::Read(ItemLabStatistics& data) const
{
    nlohmann::json jsonobject = nlohmann::json();
    std::fstream file;
    file.open(m_fullpath, ios::in);
    if (file.good() && file.is_open())
    {
        file >> jsonobject;
    }
  
    //todo: preparation for gamblecount
    data.m_used_prefixcards = TO_UINT(jsonobject["prefixcards"]);
    data.m_used_suffixcards = TO_UINT(jsonobject["suffixcards"]);
    try
    {
        data.m_used_prefixwipes = TO_UINT(jsonobject["prefixwipes"]);
        data.m_used_suffixwipes = TO_UINT(jsonobject["suffixwipes"]);
    }
    catch (...)
    {
        data.m_used_prefixwipes = TO_UINT(jsonobject["prefixwhipes"]);
        data.m_used_suffixwipes = TO_UINT(jsonobject["suffixwhipes"]);
    }

    for (int i = 0; i < 8; i++)
    {
        try
        {
            std::string groupname = "E" + std::to_string(i + 5) + "-E" + std::to_string(i + 6);
            data.m_enchantStats[i][0] = TO_UINT(jsonobject[groupname]["tries"]);
            data.m_enchantStats[i][1] = TO_UINT(jsonobject[groupname]["fails"]);
        }
        catch (...)
        { /*Do nothing, just ignore the missing fields*/
        }
    }
    data.m_used_enchprots_e1 = TO_UINT(jsonobject["protect1"]);
    data.m_used_enchprots_e5 = TO_UINT(jsonobject["protect5"]);
    data.m_used_enchantcards = TO_UINT(jsonobject["cards"]);
    try
    {
        data.m_used_speedcards = TO_UINT(jsonobject["speedcards"]);
        data.m_used_energyshieldcard = TO_UINT(jsonobject["energyshieldcards"]);
        data.m_used_chancecards_3 = TO_UINT(jsonobject["chancecards_3"]);
        data.m_used_chancecards_5 = TO_UINT(jsonobject["chancecards_5"]);
        data.m_used_chancecards_8 = TO_UINT(jsonobject["chancecards_8"]);
    }
    catch (...)
    {
        data.m_used_speedcards = TO_UINT(jsonobject["specialcards"]);
        data.m_used_chancecards_8 = TO_UINT(jsonobject["usedluckycards"]);
    }
}

void ItemLabStatisticsJsonPersistence::Save(const ItemLabStatistics& data) const
{
    nlohmann::json jsonobject = nlohmann::json();
    for (int i = 0; i < 8; i++)
    {
        std::string groupname = "E" + std::to_string(i + 5) + "-E" + std::to_string(i + 6);
        jsonobject[groupname]["tries"] = data.m_enchantStats[i][0];
        jsonobject[groupname]["fails"] = data.m_enchantStats[i][1];
    }
    jsonobject["protect1"] = data.m_used_enchprots_e1;
    jsonobject["protect5"] = data.m_used_enchprots_e5;
    jsonobject["cards"] = data.m_used_enchantcards;
    jsonobject["speedcards"] = data.m_used_speedcards;
    jsonobject["energyshieldcards"] = data.m_used_energyshieldcard;
    jsonobject["chancecards_3"] = data.m_used_chancecards_3;
    jsonobject["chancecards_5"] = data.m_used_chancecards_5;
    jsonobject["chancecards_8"] = data.m_used_chancecards_8;

    jsonobject["prefixwipes"] = data.m_used_prefixwipes;
    jsonobject["prefixcards"] = data.m_used_prefixcards;
    jsonobject["suffixwipes"] = data.m_used_suffixwipes;
    jsonobject["suffixcards"] = data.m_used_suffixcards;

    std::fstream file;
    file.open(m_fullpath, ios::out);
    if (file.good() && file.is_open())
    {
        file << std::setw(4) << jsonobject << std::endl;
        file.close();
    }
}
