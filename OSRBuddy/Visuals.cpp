#include "Visuals.h"

FeatureType Visuals::GetType() const
{
	return FeatureType::Visuals;
}

const char* Visuals::GetName() const
{
	return "Visuals";
}

void Visuals::Tick()
{
}

void Visuals::RenderImGui()
{
}
