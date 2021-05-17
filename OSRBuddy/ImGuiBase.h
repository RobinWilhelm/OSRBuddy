#pragma once
#include <Windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui_addition.h"

class IDirect3DDevice9;

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

protected:
	bool m_isOpen;
	HWND m_hWindow;
	bool m_initialised;
	bool m_blockInput;
};