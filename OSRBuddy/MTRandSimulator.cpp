#include "osrb_pch.h"
#include "MTRandSimulator.h"
#include "RandomBreakHelper.h"

MTRandSimulator::MTRandSimulator(time_t t, clock_t c)
{
    m_seed = MTRand::hash(t, c);
    m_mtrand = std::make_unique<MTRand>(m_seed);
    m_sequence_offset = 0;
}

MTRandSimulator::MTRandSimulator(uint32_t seed)
{
    m_seed = seed;
    m_mtrand = std::make_unique<MTRand>(m_seed);
    m_sequence_offset = 0;
}

void MTRandSimulator::GenerateRandomSequence(uint32_t length)
{
    m_random_sequence.reserve(length);
    for (uint32_t i = 0; i < length; i++)
    {
        m_random_sequence.push_back(m_mtrand->randInt());
    }
}

uint32_t MTRandSimulator::GetRandInt32(uint32_t min_value, uint32_t max_value)
{
    if (min_value >= max_value) {
        return false;
    }

    uint32_t nGap = max_value - min_value;

    // Find which bits are used in n
    // Optimized by Magnus Jonsson (magnus@smartelectronix.com)
    uint32_t used = nGap;
    used |= used >> 1;
    used |= used >> 2;
    used |= used >> 4;
    used |= used >> 8;
    used |= used >> 16;

    // Draw numbers until one is found in [0,n]
    uint32_t i;
    do
    {
        if (m_sequence_offset >= m_random_sequence.size()) {
            return 0;
        }

        i = m_random_sequence[m_sequence_offset] & used;  // toss unused bits to shorten search
        m_sequence_offset++;
    } while (i > nGap);


    return min_value + i;
}

uint32_t MTRandSimulator::GetRandInt32(uint32_t& seq_offset, uint32_t min_value, uint32_t max_value)
{
    uint32_t seq_offset_buffer = m_sequence_offset;
    m_sequence_offset = seq_offset;
    uint32_t randnum = GetRandInt32(min_value, max_value);
    seq_offset = m_sequence_offset;
    m_sequence_offset = seq_offset_buffer;
    return randnum;
}
