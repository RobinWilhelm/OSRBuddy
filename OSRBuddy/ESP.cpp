#include "osrb_pch.h"
#include "ESP.h"
#include "D3D9Renderer.h"

using namespace Features;

ESP::ESP(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{

}

FeatureType ESP::GetType() const
{
	return FeatureType::ESP;
}

std::string ESP::GetName() const
{
	return "ESP";
}

void ESP::Tick()
{

}

void ESP::RenderImGui()
{
	DrawEnableCheckBox();
}

void ESP::Render(D3D9Renderer* renderer)
{
	if (IsEnabled())
	{
		for (auto& monster : OSR_API->GetSceneData()->m_vecMonsterRenderList)
		{
			
		}
		renderer->RenderBox2D(100, 100, 100, 100, 2.5f, D3DCOLOR_ARGB(255, 0, 255, 0));
	}
}