#pragma once
#include "ImGuiBase.h"
#include "OsrItemInfo.h"

class OSRBuddyMain;
class CItemInfo;



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
