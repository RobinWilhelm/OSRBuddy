#pragma once
#include "BuddyFeatureBase.h"

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

		void Start();
		void Stop();
		void Reset();

	private:
		struct AcquiredItemInfo
		{
			std::string ItemName;
			uint32_t Amount = 0;
		};

		std::unordered_map<uint32_t, AcquiredItemInfo> m_acquiredItems;
		std::unique_ptr<StopWatch> m_stopWatch;
	};
}

