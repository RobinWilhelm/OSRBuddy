#pragma once	  
#include "BuddyFeatureBase.h"
#include "IOPacketManager.h"
#include "BuddyTimer.h"

#define AVG_PDL_UPDATES_PER_SECOND 10

namespace Features
{
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

	private:
		PacketDebugLog m_pdl_current;
		PacketDebugLog m_pdl_old[AVG_PDL_UPDATES_PER_SECOND];
		PacketDebugLog m_pdl_last_second;
		uint32_t m_pdl_old_next_index;
		BuddyTimer m_pdl_timer;
	};
}