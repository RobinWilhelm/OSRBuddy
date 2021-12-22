#pragma once

#include "Structs.h"

#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include <limits>
#include <memory>
#include <Windows.h>



struct SeedHit
{
	uint32_t seed;
	time_t start;
	int  clocks;
	uint32_t seq_offset;
};

struct SeedSearchResult
{
	std::vector<SeedHit> hits;
};

struct SequenceSearchResult
{
	bool found;
	uint32_t sequence_start;
	uint32_t sequence_end;
};

class MTRandSimulator;

class RandomBreakHelper
{
public:
	RandomBreakHelper();
	
	SequenceSearchResult SearchEnchantResultSequence(MTRandSimulator* randsimul, const std::vector<Features::EnchantResult>& er, uint32_t sequence_start = 0, bool beginonly = false);
	bool SimulateEnchant(MTRandSimulator* randsimul, uint32_t enchant_to);

	time_t MakeTime(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);

	static uint32_t GetEnchantProb(uint32_t enchant_to)
	{
		std::vector<uint32_t> enchant_probabilities = { 10000, 10000, 10000, 10000, 10000, 9000, 8000, 6000, 4000, 2000, 1000, 500, 100 };
		return enchant_probabilities.at(enchant_to - 1);
	}
};

