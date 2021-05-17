#pragma once
#include "BuddyFeatureBase.h"
#include <vector>
#include <string>		  
#include "OSRAPI.h"



class MTRand;

class AntiMTRandBot :
	public BuddyFeatureBase
{
	struct EnchantResult
	{
		byte try_enchant_to;
		bool success;
	};

public:
	AntiMTRandBot(OSRBuddyMain* buddy);
	~AntiMTRandBot();


	// Geerbt über BuddyFeatureBase
	virtual void Tick() override;
	virtual void Render(IDirect3DDevice9* device) override;
	virtual void RenderImGui() override;
	virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
	virtual const char* GetName() const override;	   
	static std::vector<uint32_t> GetEnchantProbabilities();

private:
	bool GetRandInt32(std::vector<uint32_t> rand_sequence, uint32_t& sequence_offset, uint32_t min_value, uint32_t max_value, uint32_t* randNr);
	void GenerateNewTestSequence();
	bool SearchSequenceOffset(std::vector<uint32_t> rand_sequence, uint32_t rand_sequence_length, std::vector<EnchantResult> test_sequence, std::uint32_t* sequence_offset, bool beginonly = false);

private:
	const static std::vector<uint32_t> m_enchant_probabilities;
	std::unique_ptr<MTRand> m_mtrand;
	uint32_t m_seed;
	std::vector<uint8_t> m_rand_sequence;
	std::vector<EnchantResult> m_test_sequence;
	uint32_t m_sequence_length;
	uint32_t m_sequence_offset;
	bool m_ready;
};