#pragma once
#include "BuddyFeatureBase.h"
#include "RandomBreakHelper.h"
#include "MTRandSimulator.h"

#include "OSRAPI.h"

#include <vector>
#include <string>	

#define ANTIMTRAND_NEXT_NUMBER_COUNT 15
#define ANTIMTRAND_GENERATED_SEQUENCE_LENGTH 1000000
#define ANTIRAND_SEED 3239254967

namespace Features
{
	class EnchantBot;

	class AntiMTRandBot :
		public BuddyFeatureBase
	{
	public:
		AntiMTRandBot(OSRBuddyMain* buddy);
		~AntiMTRandBot();


		// Geerbt über BuddyFeatureBase
		virtual void Tick() override;
		virtual void RenderImGui() override;
		virtual std::string GetName() const override;
		virtual FeatureType GetType() const override;
		virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
		virtual bool OnWritePacket(unsigned short msgtype, byte* packet) override;

		void OnEnchant(CItemInfo* item, bool success);
		void OnItemMix(bool success);

		void SaveEnchantLog();
	private:
		void CreateNextRandomNumbersForDisplay(uint32_t count);

	private:
		uint32_t m_seed;
		uint32_t m_sequence_search_start;
		uint32_t m_sequence_search_length;
		std::unique_ptr<MTRandSimulator> m_mtrandsim;
		std::unique_ptr<RandomBreakHelper> m_randomhelper;
		SequenceSearchResult m_seq_search_result;
		UID64_t m_current_enchant_target;
		std::vector<EnchantResult> m_enchant_logs;
		float m_current_entropy;
		bool m_logging_active;
		bool m_in_seq;
		std::vector<uint32_t> m_next_numbers;
		std::string m_current_entropy_buffer;
		std::string m_recommended_entropy_buffer;
	};
}