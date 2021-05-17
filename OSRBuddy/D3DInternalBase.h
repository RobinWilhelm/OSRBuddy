#pragma once
#include "Trampoline.h"
#include "VMTHook.h"
#include <memory>
#include "Trampoline.h"
#include "ImGuiBase.h"
#include <random>

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")



																				 
using EndSceneType	= HRESULT(__stdcall*)(IDirect3DDevice9*);	  
using PresentType	= HRESULT(__stdcall*)(IDirect3DDevice9* , const RECT *, const RECT *, HWND, const RGNDATA *);
using ResetType		= HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
																				  
using EndSceneTypeNew	= HRESULT(IDirect3DDevice9::*)(void);
using PresentTypeNew	= HRESULT(IDirect3DDevice9::*)(const RECT*, const RECT*, HWND, const RGNDATA*);
using ResetTypeNew		= HRESULT(IDirect3DDevice9::*)(D3DPRESENT_PARAMETERS*);

enum class RenderHookOption
{
	ENDSCENE = 0,
	PRESENT	 
};

enum class RenderHookType
{
	VMT = 0,
	TRAMPOLINE,
};

class ImGuiBase;

class D3DInternalBase
{
	D3DInternalBase(const D3DInternalBase&) = delete;
	D3DInternalBase& operator=(const D3DInternalBase&) = delete;

public:
	virtual bool Start() = 0;
	int GetRandInt32(int min, int max);
	HWND GetHwnd() { return m_hWindow; };

protected:
	D3DInternalBase();
	virtual ~D3DInternalBase();	 	
	
	virtual void Render(IDirect3DDevice9* device) = 0; 										  
	virtual LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
			   
	void InitiateAppShutdown();
	

protected:
	void OnEndScene(IDirect3DDevice9*);
	void OnPresent(IDirect3DDevice9* ,const RECT*, const RECT*, HWND, const RGNDATA*);
	void OnBeforeReset(IDirect3DDevice9* , D3DPRESENT_PARAMETERS* params);
	void OnAfterReset(IDirect3DDevice9* ,D3DPRESENT_PARAMETERS* params);


	bool InitD3DHooks(RenderHookType hooktype, RenderHookOption hookoption, IDirect3DDevice9* device);
	void ShutdownD3DHooks();
	
	bool HookWindowProcedure(HWND window);
	void UnhookWindowProcedure();
	bool GetD3D9DeviceVtable(void** pTable, size_t Size);

private:
	// Hooks
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	static HRESULT __stdcall EndScene_hooked(IDirect3DDevice9* device);
	static HRESULT __stdcall Present_hooked(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
	static HRESULT __stdcall Reset_hooked(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);
	
protected:
	bool m_doUnload;

	RenderHookOption									m_hookoption;
	RenderHookType										m_hooktype;
	std::unique_ptr<VMTHook<IDirect3DDevice9>>			m_d3d9_vmt_hooks;
	std::unique_ptr<TrampolineHook<EndSceneType>>	    m_trampoline_endscene;
	std::unique_ptr<TrampolineHook<PresentType>>		m_trampoline_present;
	std::unique_ptr<TrampolineHook<ResetType>>			m_trampoline_reset;

	EndSceneType	m_orig_endscene;
	PresentType		m_orig_present;
	ResetType		m_orig_reset;
	  
	IDirect3DDevice9* m_d3d9device;

	WNDPROC m_OriginalWndproc;
	HWND m_hWindow;

	std::unique_ptr<ImGuiBase> m_imguimenu;		  

	std::unique_ptr<std::mt19937> m_random_generator;
};