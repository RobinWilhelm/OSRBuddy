#include "osrb_pch.h"
#include "RandomBreakHelper.h"

#include "nlohmann/json.hpp"
#include "MTRandSimulator.h"

#include "Structs.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>


RandomBreakHelper::RandomBreakHelper()
{
   
}

SequenceSearchResult RandomBreakHelper::SearchEnchantResultSequence(MTRandSimulator* randsimul, const std::vector<Features::EnchantResult>& er, uint32_t sequence_start, bool beginonly)
{
    SequenceSearchResult result;
    result.found = false;
    result.sequence_start = 0;
    result.sequence_end = 0;

    for (uint32_t offset = sequence_start; offset <= (randsimul->RandomSequenceLength() - er.size()); offset++)
    {
        uint32_t test_sequence_index = 0;
        randsimul->SetSequenceOffset(offset);

        bool in_seq = true;
        for (auto& enchresult : er)
        {
            uint32_t random_number = randsimul->GetRandInt32(0, MAX_RAND10K_VALUE);
            uint32_t needed_prob = GetEnchantProb(enchresult.try_enchant_to);
            if (enchresult.success != (random_number <= needed_prob))
            {           
                in_seq = false;
                if (beginonly)
                {
                    return result;
                }
                break;
            }
        }

        if (in_seq)
        {
            result.found = true;
            result.sequence_start = offset;
            result.sequence_end = randsimul->GetSequenceOffset();
            return result;
        }
    }
    return result;
}

bool RandomBreakHelper::SimulateEnchant(MTRandSimulator* randsimul, uint32_t enchant_to)
{    
    short enchantprob = GetEnchantProb(enchant_to);
    if (0 >= enchantprob)
    {
        throw std::exception("wie?");
    }

    short randomnum = randsimul->GetRandInt32(0, MAX_RAND10K_VALUE);

    if (randomnum <= enchantprob)
    {
        return true;
    }
    else
    {
        return false;
    }
}

time_t RandomBreakHelper::MakeTime(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{
    struct tm t = { 0 };  // Initalize to all 0's
    t.tm_year = year - 1900;  // This is year-1900, so 112 = 2012
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    return mktime(&t);
}

