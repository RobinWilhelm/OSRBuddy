#pragma once	  
#include "BuddyFeatureBase.h"
#include "IOPacketManager.h"
#include "BuddyTimer.h"

#include <vector>
#include <unordered_map>

#define AVG_PDL_UPDATES_PER_SECOND 10

namespace Features
{
	struct PacketDebugInfo
	{
		std::string name;
		uint32_t count_total;
		uint32_t count_last_second;
		uint32_t count_old[AVG_PDL_UPDATES_PER_SECOND];
	};

	class DebugInfo : public BuddyFeatureBase
	{
	public:
		DebugInfo(OSRBuddyMain* buddy);
		~DebugInfo();

		// Geerbt über BuddyFeatureBase
		virtual FeatureType GetType() const override;
		virtual std::string GetName() const override;
		virtual void Tick() override;
		virtual void RenderImGui() override;
		virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
		virtual bool OnWritePacket(unsigned short msgtype, byte* packet) override;

	private:
		PacketDebugLog m_pdl_current;
		PacketDebugLog m_pdl_old[AVG_PDL_UPDATES_PER_SECOND];
		PacketDebugLog m_pdl_last_second;
		uint32_t m_pdl_old_next_index;
		BuddyTimer m_pdl_timer;


		std::vector<PacketDebugInfo> m_packetlog;
		std::vector<USHORT> m_packetlog_lookup_sent;
		std::vector<USHORT> m_packetlog_lookup_recv;
		uint32_t m_pdi_old_next_index;
		PacketDebugInfo m_total_sent;
		PacketDebugInfo m_total_recv;
	};
}