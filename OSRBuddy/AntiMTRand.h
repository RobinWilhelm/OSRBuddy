#pragma once
#include "BuddyFeatureBase.h"
#include "RandomBreakHelper.h"
#include "MTRandSimulator.h"

#include "OSRAPI.h"

#include <vector>
#include <string>	

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

	private:
		uint32_t m_seed;
		uint32_t m_sequence_search_start;
		uint32_t m_sequence_search_end;
		std::unique_ptr<MTRandSimulator> m_mtrandsim;
		std::unique_ptr<RandomBreakHelper> m_randomhelper;
		SequenceSearchResult m_seq_search_result;
		UID64_t m_current_enchant_target;
		std::vector<EnchantResult> m_enchant_logs;
		float m_current_entropy;
		bool m_logging_active;
		bool m_in_seq;
	};
}