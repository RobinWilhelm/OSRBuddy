#pragma once	  
#include "BuddyFeatureBase.h"

class Visuals :	public BuddyFeatureBase
{
public:
	Visuals(OSRBuddyMain* buddy);
	~Visuals();

	// Geerbt über BuddyFeatureBase
	virtual FeatureType GetType() const override;
	virtual std::string GetName() const override;
	virtual void Tick() override;
	virtual void RenderImGui() override;
};