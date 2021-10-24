#include "FactoryBot2.h"

FactoryBot2::FactoryBot2(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
}

FactoryBot2::~FactoryBot2()
{
}

FeatureType FactoryBot2::GetType() const
{
	return FeatureType::FactoryBot;
}

std::string FactoryBot2::GetName() const
{
	return "FactoryBot 2";
}

void FactoryBot2::Tick()
{
}

void FactoryBot2::RenderImGui()
{
}
