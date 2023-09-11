#pragma once
#include "BuddyFeatureBase.h"

#include <vector>
#include <map>
#include <unordered_map>

class StopWatch;

namespace Features
{	
	class Drops : public BuddyFeatureBase
	{
	public:
		Drops(OSRBuddyMain* buddy);
		~Drops();

		// Geerbt über BuddyFeatureBase
		virtual Features::FeatureType GetType() const override;
		virtual std::string GetName() const override;
		virtual void Tick() override;
		virtual void RenderImGui() override;

		virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;

	private:
		struct AcquiredItemInfo
		{
			std::string ItemName;
			int32_t DeltaAmount = 0;
		};

		std::unordered_map<uint32_t, std::map<BYTE, AcquiredItemInfo>> m_acquiredItems;
		std::unique_ptr<StopWatch> m_stopWatch;
		bool m_DropsFilter[IUT_CITYWAR_BRING_SUMOFTEX];
	};
}

