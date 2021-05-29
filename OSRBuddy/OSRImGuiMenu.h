#pragma once
#include "ImGuiBase.h"
#include "OsrItemInfo.h"

class OSRBuddyMain;
class CItemInfo;

#define SHIELDKIT_COLOR ImColor(0,50,234,255) 
#define ENERGYKIT_COLOR ImColor(234,0,0,255) 
#define SKILLPKIT_COLOR ImColor(247,148,29,255) 

class OSRImGuiMenu : public ImGuiBase
{
public:
	OSRImGuiMenu(OSRBuddyMain* osrbuddy)
	{
		m_osrbuddy = osrbuddy;
	}

	~OSRImGuiMenu()
	{
		m_osrbuddy = nullptr;
	}

	// Geerbt über ImGuiBase
	virtual void Render() override;

	static ImColor TranslateAceCharToColor(char color);
	static void DrawOsrItemName(const OsrItemInfo& item);

private:
	OSRBuddyMain* m_osrbuddy;
};
