#pragma once
#include "BuddyFeatureBase.h"

namespace Features
{
	class FactoryBot2 : public BuddyFeatureBase
	{
	public:
		FactoryBot2(OSRBuddyMain* buddy);
		~FactoryBot2();

		// Inherited via BuddyFeatureBase
		virtual FeatureType GetType() const override;
		virtual std::string GetName() const override;
		virtual void Tick() override;
		virtual void RenderImGui() override;
	};
}