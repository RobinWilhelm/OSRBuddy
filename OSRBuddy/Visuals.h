#pragma once	  
#include "BuddyFeatureBase.h"

class Visuals :	public BuddyFeatureBase
{
	// Geerbt �ber BuddyFeatureBase
	virtual FeatureType GetType() const override;
	virtual const char* GetName() const override;
	virtual void Tick() override;
	virtual void RenderImGui() override;
};

