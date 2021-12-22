#pragma once
#include "MTRand.h"

#include <memory>
#include <Windows.h>
#include <vector>

#ifdef  max
#undef max
#endif //  max

#define MAX_RAND100_VALUE		99				// int, 0 ~ 99
#define MAX_RAND1000_VALUE		999				// int, 0 ~ 999
#define MAX_RAND10K_VALUE		9999			// int, 0 ~ 9999
#define MAX_RAND100K_VALUE		99999			// int, 0 ~ 99999
#define MAX_RAND1000K_VALUE		999999			// int, 0 ~ 999999
#define MAX_RAND256_VALUE		255				// int, 0 ~ 255

typedef short		Prob256_t;				// È®·ü [0, 256)
#define PROB256_MAX_VALUE	255
typedef short		Prob100_t;				// È®·ü [0, 100]
// 2010-07-19 by dhjin, È®·ü ¼ö½Ä º¯°æ
// #define PROB100_MAX_VALUE	99	// 2010-07-19 by dhjin, È®·ü ¼ö½Ä º¯°æ
#define PROB100_MAX_VALUE	100
typedef short		Prob1000_t;				// È®·ü [0, 1000)
#define PROB1000_MAX_VALUE	999
typedef short		Prob10K_t;				// È®·ü [0, 10000)
#define PROB10K_MAX_VALUE	9999
typedef int			Prob100K_t;				// È®·ü [0, 100000)
#define PROB100K_MAX_VALUE	99999
typedef int			Prob1000K_t;			// È®·ü [0, 1000000)
#define PROB1000K_MAX_VALUE	999999


class MTRandSimulator
{
public:
	MTRandSimulator(time_t t, clock_t c);
	MTRandSimulator(uint32_t seed);

	void GenerateRandomSequence(uint32_t length);
	void SetSequenceOffset(uint32_t offset) { m_sequence_offset = offset; };
	uint32_t GetSequenceOffset() { return m_sequence_offset; };
	uint32_t GetRandInt32(uint32_t min_value, uint32_t max_value);
	uint32_t GetRandInt32(uint32_t& seq_offset, uint32_t min_value, uint32_t max_value);
	uint32_t RandomSequenceLength() const { return m_random_sequence.size(); };
	uint32_t GetSeed() { return m_seed; };

private:
	uint32_t m_seed;
	std::unique_ptr<MTRand> m_mtrand;
	std::vector<uint32_t> m_random_sequence;
	uint32_t m_sequence_offset;
};

