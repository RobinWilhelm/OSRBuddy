#include "AntiMTRand.h"
#include "MarsenneTwister.h"
#include <string>

#define IS_BETWEEN(value, minval, maxval) (value >= minval && value <= maxval)
#define MAX_RAND100_VALUE		99				// int, 0 ~ 99
#define MAX_RAND1000_VALUE		999				// int, 0 ~ 999
#define MAX_RAND10K_VALUE		9999			// int, 0 ~ 9999
#define MAX_RAND100K_VALUE		99999			// int, 0 ~ 99999
#define MAX_RAND1000K_VALUE		999999			// int, 0 ~ 999999
#define MAX_RAND256_VALUE		255				// int, 0 ~ 255

const std::vector<uint32_t> AntiMTRandBot::m_enchant_probabilities = { 10000, 10000, 10000, 10000, 10000, 9000, 8000, 6600, 4000, 2000, 1000, 500, 100 };

AntiMTRandBot::AntiMTRandBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{

}

AntiMTRandBot::~AntiMTRandBot()
{

}

void AntiMTRandBot::Tick()
{

}

void AntiMTRandBot::Render(IDirect3DDevice9* device)
{

}

void AntiMTRandBot::RenderImGui()
{
	ImGui::InputInt("Input Seed", reinterpret_cast<int*>(&m_seed));
	ImGui::InputInt("Test Sequence Length", reinterpret_cast<int*>(&m_sequence_length));
	if (ImGui::Button("Generate New Test Sequence")) {
		GenerateNewTestSequence();
	}

	if (ImGui::Button("Search Sequence Offset. This may take a few seconds!")) 
	{ 		
		uint32_t sequence_off = 0;

		if (SearchSequenceOffset(&sequence_off))
		{
			m_sequence_offset = sequence_off;
			m_ready = true;
		}
	}
	if (m_ready)
	{
		if (ImGui::Button("Next")) {
			GetRandInt32(m_sequence_offset, 0, MAX_RAND10K_VALUE);
		}

		uint32_t sequence_offset_buffer = m_sequence_offset;
		std::string next_value_text = "Predicted Value: " + std::to_string(GetRandInt32(sequence_offset_buffer, 0, MAX_RAND10K_VALUE));
		ImGui::Text(next_value_text.c_str());
	}
}

bool AntiMTRandBot::OnReadPacket(unsigned short msgtype, char* packet)
{
	return false;
}

const char* AntiMTRandBot::GetName() const
{
	return "Anti Randomness V0.1";
}

std::vector<uint32_t> AntiMTRandBot::GetEnchantProbabilities()
{
	return m_enchant_probabilities;
}


void AntiMTRandBot::GenerateNewTestSequence()
{
	m_mtrand.reset();
	m_rand_sequence.clear();
	m_mtrand = std::make_unique<MTRand>(m_seed);
	m_rand_sequence.reserve(m_sequence_length);

	for (uint32_t i = 0; i < m_sequence_length; i++) {
		m_rand_sequence.push_back(m_mtrand->randInt());
	}
}

bool AntiMTRandBot::GetRandInt32(std::vector<uint32_t> rand_sequence, uint32_t& sequence_offset, uint32_t min_value, uint32_t max_value, uint32_t* randNr)
{
	if (min_value >= max_value) {
		return false;
	}

	UINT nGap = max_value - min_value;

	// Find which bits are used in n
	// Optimized by Magnus Jonsson (magnus@smartelectronix.com)
	unsigned long used = nGap;
	used |= used >> 1;
	used |= used >> 2;
	used |= used >> 4;
	used |= used >> 8;
	used |= used >> 16;

	// Draw numbers until one is found in [0,n]
	unsigned long i;
	do
	{
		if (sequence_offset >= rand_sequence.size()) {
			return false;
		}

		i = rand_sequence[sequence_offset] & used;  // toss unused bits to shorten search
		sequence_offset++;
	} while (i > nGap);


	(*randNr) = min_value + i;
	return true;
}

bool AntiMTRandBot::SearchSequenceOffset(std::vector<uint32_t> rand_sequence, uint32_t rand_sequence_length, std::vector<EnchantResult> test_sequence, std::uint32_t* sequence_offset, bool beginonly = false)
{
	uint32_t test_sequence_index = 0;
	for (uint32_t offset = 0; offset <= (rand_sequence.size() - test_sequence.size()); offset++)
	{
		uint32_t cumulOffset = (*sequence_offset) + offset;
		bool in_sequence = false;

		do
		{
			uint32_t randNr;
			if (!GetRandInt32(rand_sequence, cumulOffset, 0, MAX_RAND10K_VALUE, &randNr)) {
				break;
			}
			uint32_t prob = m_enchant_probabilities[test_sequence[test_sequence_index].try_enchant_to - 1];

			if (test_sequence[test_sequence_index].success == (randNr <= prob))
			{
				test_sequence_index++;
				if (test_sequence_index == test_sequence.size()) {
					(*sequence_offset) = cumulOffset;
					return true;
				}
			}
			else
			{
				test_sequence_index = 0;
				if (beginonly) {
					return false;
				}
			}

		} while (cumulOffset < (rand_sequence.size() - test_sequence.size()) || test_sequence_index > 0);

		if (beginonly) {
			break;
		}
	}
	return false;
}
