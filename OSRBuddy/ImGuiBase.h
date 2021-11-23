#pragma once
#include "imgui/imgui.h"

#include <Windows.h>

struct IDirect3DDevice9;

class ImGuiBase
{
	friend class D3DInternalBase;
public:
	ImGuiBase();
	virtual ~ImGuiBase();

	bool Init(IDirect3DDevice9* device);
	void Toggle();
	void ShowMenu(bool open);
	bool IsOpen(); 
	void SetBlockInput(bool block);

protected:		 
	virtual void Render() = 0;

	void ImGuiBeginFrame();
	void ImGuiEndFrame();

	void BeforeReset();
	void AfterReset();

	void Render(IDirect3DDevice9* device);
	LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);	 

	 
	void LoadStandardTheme();
	void LoadClassicSteamTheme();
	void LoadCorporateGreyTheme();
	void LoadRayTeakTheme(); 

protected:
	ImGuiStyle m_standard_style;
	bool m_isOpen;
	HWND m_hWindow;
	bool m_initialised;
	bool m_blockInput;
	ImFontConfig m_tahoma;
};