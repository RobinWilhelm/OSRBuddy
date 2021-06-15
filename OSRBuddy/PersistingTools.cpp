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

void PersistingTools::SetItem(UID64_t uid) {
    m_fileName = std::to_string(uid) + ".json";
    m_fullpath = m_workingDirectory + "\\" + m_fileName;
    struct stat buffer;
    if (stat(m_fullpath.c_str(), &buffer) == 0) {
        m_file.open(m_fullpath, ios::in);
        m_file >> m_j;
        //todo: preparation for gamblecount
        m_statistics.m_used_enchprots_e1 = (int) m_j["protect1"];
        m_statistics.m_used_enchprots_e5 = (int) m_j["protect5"];
        m_statistics.m_used_enchantcards = (int) m_j["cards"];
        m_statistics.m_used_speedcards = (int) m_j["specialcards"];
        m_statistics.m_used_chancecards_8 = (int) m_j["usedluckycards"];
        m_statistics.m_enchantStats[5][0] = (int)m_j["failstoeleven"];
        m_file.close();
    }
    else {
        m_j["protect1"] = 0;
        m_j["protect5"] = 0;
        m_j["cards"] = 0;
        m_j["specialcards"] = 0;
        m_j["usedluckycards"] = 0;
        m_j["failstoeleven"] = 0;
        m_j["failstotwelve"] = 0;
        ZeroMemory(&m_statistics, sizeof(EnchantStatistics));
        m_file.open(m_fullpath, ios::out);
        m_file << std::setw(4) << m_j << std::endl;
        m_file.close();
    }
}

EnchantStatistics PersistingTools::GetStats() {
    return m_statistics;
}

void PersistingTools::CloseStream() {
    if (m_file.is_open()) {
        m_file.close();
    }
}



void PersistingTools::PersistEnchantments(EnchantStatistics enchstats) {
    m_file.open(m_fullpath, ios::out);
    m_j["protect1"] = enchstats.m_used_enchprots_e1;
    m_j["protect5"] = enchstats.m_used_enchprots_e5;
    m_j["cards"] = enchstats.m_used_enchantcards;
    m_j["specialcards"] = enchstats.m_used_speedcards;
    m_j["usedluckycards"] = enchstats.m_used_chancecards_8;
    m_j["failstoeleven"] = enchstats.m_enchantStats[5][0];
    m_file << std::setw(4) << m_j << std::endl;
    m_file.close();
}

