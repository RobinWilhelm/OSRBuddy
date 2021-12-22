#pragma once
#include <vector>

using Hotkey = uint32_t;

struct HotkeyInfo
{
	Hotkey id;
	uint32_t vkey;
	bool set_new;
	bool was_pressed;
	std::string description;
};

class HotkeyManager
{
private:
	HotkeyManager();
	~HotkeyManager();

public:
	static HotkeyManager& GetInstance();

	Hotkey RegisterHotkey(uint32_t vkey = 0);
	void ReleaseHotkey(Hotkey& hk);
	void ReleaseAll();
	bool WasHotkeyPressed(Hotkey hk);
	void SetHotkeyChange(Hotkey hk);

	std::string GetHotkeyText(Hotkey hk);

	int WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	std::vector<HotkeyInfo> m_hotkeys;
	uint32_t m_next_id;
};