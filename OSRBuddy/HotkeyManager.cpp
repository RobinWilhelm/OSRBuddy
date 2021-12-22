#include "osrb_pch.h"
#include "HotkeyManager.h"
#include "Utility.h"

HotkeyManager::HotkeyManager()
{
	m_next_id = 1;
}


HotkeyManager::~HotkeyManager()
{
	ReleaseAll();
}

HotkeyManager& HotkeyManager::GetInstance()
{
	static HotkeyManager instance = HotkeyManager();
	return instance;
}

Hotkey HotkeyManager::RegisterHotkey(uint32_t vkey)
{
	HotkeyInfo hkinfo;
	hkinfo.vkey = vkey;
	hkinfo.description = Utility::VirtualKeyCodeToString(vkey);
	hkinfo.set_new = false;
	hkinfo.was_pressed = true;
	hkinfo.id = m_next_id;

	m_hotkeys.push_back(hkinfo);
	m_next_id++;

	return hkinfo.id;
}

void HotkeyManager::ReleaseHotkey(Hotkey& hk)
{
	std::vector<HotkeyInfo>::iterator iter = m_hotkeys.begin();
	for (; iter != m_hotkeys.end(); iter++)
	{
		if (iter->id == hk)
		{
			iter = m_hotkeys.erase(iter);
			break;
		}
	}
	hk = 0;
}


void HotkeyManager::ReleaseAll()
{
	m_hotkeys.clear();
}

bool HotkeyManager::WasHotkeyPressed(Hotkey hk)
{
	for (auto& hkinfo : m_hotkeys)
	{
		if (hkinfo.id == hk)
		{
			if (hkinfo.was_pressed)
			{
				hkinfo.was_pressed = false;
				return true;
			}
			return false;
		}
	}
	return false;
}

void HotkeyManager::SetHotkeyChange(Hotkey hk)
{
	for (auto& hkinfo : m_hotkeys)
	{
		if (hkinfo.id == hk)
		{
			hkinfo.set_new = true;
			return;
		}
	}
}

std::string HotkeyManager::GetHotkeyText(Hotkey hk)
{
	for (auto& hkinfo : m_hotkeys)
	{
		if (hkinfo.id == hk)
		{
			return hkinfo.description;
		}
	}
	return "Invalid Hotkey";
}

int HotkeyManager::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYUP:
		for (auto& hkinfo : m_hotkeys)
		{
			if (hkinfo.set_new)
			{
				hkinfo.vkey = TO_UINT(wParam);
				hkinfo.description = Utility::VirtualKeyCodeToString(hkinfo.vkey);
				hkinfo.set_new = false;
			}
			else
			{
				if (hkinfo.vkey == TO_UINT(wParam))
				{
					//ToggleGrinding();
					return 1;
				}
			}
		}
	}
	return 0;
}