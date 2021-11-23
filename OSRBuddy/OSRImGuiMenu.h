#pragma once
#include "ImGuiBase.h"

class OSRBuddyMain;

class OSRImGuiMenu : public ImGuiBase
{
public:
	OSRImGuiMenu(OSRBuddyMain* osrbuddy) { m_osrbuddy = osrbuddy; }												  
	~OSRImGuiMenu()	{ m_osrbuddy = nullptr; }

	// Geerbt über ImGuiBase
	virtual void Render() override;

private:
	OSRBuddyMain* m_osrbuddy;
};
