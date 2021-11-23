#pragma once
#include "IPacketWatcher.h"
#include "Content.h"
#include "OSRBuddy.h"

#include <Windows.h>
#include <string>
   	 
class OldSchoolRivalsAPI;
struct IDirect3DDevice9;
class D3D9Renderer;
class BuddyFeatureBase;
		

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



