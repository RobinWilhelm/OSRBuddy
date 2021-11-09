#pragma once
#include "Content.h"
#include "IPacketWatcher.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include <Windows.h>
#include <string>
   	 
class OSRBuddyMain;
class OldSchoolRivalsAPI;
struct IDirect3DDevice9;
class D3D9Renderer;

enum class FeatureType : int
{
	KitBuffBot = 0,
	TestItemUse,
	GambleBot,
	EnchantBot,
	FactoryBot,
	AntiRandomness,
	GrindBot,
	DebugInfo,
	Miscellaneous,
	InventoryManager,
};
			 
class BuddyFeatureBase : public IPacketWatcher
{
	friend class OSRBuddyMain;
	friend class ImGuiBase;	 	
	friend class OSRImGuiMenu;	  	
	
	// features are not copy/moveable
	BuddyFeatureBase(const BuddyFeatureBase&) = delete;
	BuddyFeatureBase& operator=(const BuddyFeatureBase&) = delete;

public: 	
	BuddyFeatureBase(OSRBuddyMain* osr) 
	{
		m_buddy = osr;
		m_enabled = false;
	}

	virtual ~BuddyFeatureBase() {
		m_buddy = nullptr;
	}
			   				 
	virtual FeatureType GetType() const = 0;
	virtual std::string GetName() const = 0;  
	virtual void OnEnable() { return;  };
	virtual void OnDisable() { return; };

	virtual void Tick() = 0;
	virtual void RenderImGui() = 0;		   

	virtual void Render(D3D9Renderer* renderer) { return; };
	virtual int WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { return 0; };
		
	void Enable(bool enable);
	bool IsEnabled() const { return m_enabled; };

protected:
	bool DrawEnableCheckBox();


protected:
	OSRBuddyMain* m_buddy;

private:
	bool m_enabled;
};

