#pragma once
#include "BuddyFeatureBase.h"	
	   
namespace Features
{
	class ESP : public BuddyFeatureBase
	{
	public:
		ESP(OSRBuddyMain* buddy);
		

		// Inherited via BuddyFeatureBase
		virtual Features::FeatureType GetType() const override;
		virtual std::string GetName() const override;
		virtual void Tick() override;
		virtual void RenderImGui() override;
		virtual void Render(D3D9Renderer* renderer) override;
	};
}

