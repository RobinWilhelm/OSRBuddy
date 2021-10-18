#include "Visuals.h"

Visuals::Visuals(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
}

Visuals::~Visuals()
{
}

FeatureType Visuals::GetType() const
{
	return FeatureType::Visuals;
}

std::string Visuals::GetName() const
{
	return "Visuals";
}

void Visuals::Tick()
{
}

void Visuals::RenderImGui()
{
}
