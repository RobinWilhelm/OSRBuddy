#pragma once
#include "OSRBuddyDefine.h"
#include "D3DInternalBase.h"
#include "FeatureTypes.h"

#include <vector>
#include <chrono>

class PersistingTools;
class IOPacketManager;
class BuddyFeatureBase;

class CInterface;
class CWinSocket;
class CFieldWinSocket;
class CAtumapplication;

// CInterface::Tick()
using InterfaceTickType = void(__thiscall*)(CInterface * ecx);

// CFieldWinSocket::OnRecvdPacket
using WinSocketOnRecvdPacketType = BOOL(__thiscall*)(CFieldWinSocket * ecx, LPSTR pPacket, int nLength, BYTE nSeq);

// CAtumApplication::OnRecvFieldSocketMessage
using CAtumApplicationOnRecvFieldSocketMessageType = int(__thiscall*)(CAtumapplication * ecx, DWORD wParam, UINT nSocketNotifyType);

// CWinSocket::Write  
using CWinSocketWriteType = int(__thiscall*)(CWinSocket * ecx, LPCSTR pPacket, int nLength);

// mouse move emulation
using GetCursorPosType = BOOL(__stdcall*)(LPPOINT lpPoint);
using SetCursorPosType = BOOL(__stdcall*)(int x, int y);

using FeatureKeyValue = std::pair<FeatureType, BuddyFeatureBase*>;
using FeatureContainer = std::vector<BuddyFeatureBase*>;

enum class NotifyType
{
	Information = 0,
	Warning,
	Error
};

class OSRBuddyMain : public D3DInternalBase
{
	friend class OSRImGuiMenu;
public:	
	OSRBuddyMain();
	~OSRBuddyMain();
		
	// Geerbt über D3DInternalBase
	virtual bool Start() override;
	ImGuiBase* GetMenu();
	BuddyFeatureBase* GetFeatureByType(FeatureType type) const;
	const FeatureContainer& GetAllFeatures() const;
	void RegisterFeature(BuddyFeatureBase* feature);
	void ReleaseFeatures();
	void DisableAllFeatures();				 // disable all features and close the imgui menu
	std::chrono::microseconds GetTickTime(); // should be much more accurate than the games GetElapsedTime() function

	void EnableMouseEmulation(bool on);

	// move mouse cursor by the given x and y values
	bool SetCursorPosition(int x, int y);

	// get the current cursor position
	bool GetCursorPosition(LPPOINT pos);

	bool NotificationSoundAllowed() { return m_allow_notify_sounds; };
	bool NotificationPopupAllowed() { return m_allow_notify_popups; };

	void NotifySound(NotifyType type);
	void OpenMessageBoxAsync(std::string message, std::string header, NotifyType type, std::function<void(int)> callback);
	void OpenMessageBoxAsync(std::string message, std::string header, NotifyType type);
	
	void BlockMouseInput(bool on);		   

	PersistingTools* GetPersistingTools()	{ return m_persistingTools.get(); };
	IOPacketManager* GetPacketManager()		{ return m_packetmanager.get(); };

private:
	void static MessageBoxThreadFunction(std::string message, std::string header, NotifyType type, std::function<void(int)> callback = nullptr);
	// Geerbt über D3DInternalBase
	virtual void Render(IDirect3DDevice9* device) override;
	 
	void ShutdownHooks();
	
	bool InitTickHook(); 
	void ShutdownTickHook();	 
		
	//bool InitOnRecvdPacketHook();		//not currently used
	//void ShutdownOnRecvdPacketHook();	//not currently used
	
	bool InitOnReadPacketHook();
	void ShutdownOnReadPacketHook();

	bool InitOnWriteHook();
	void ShutdownOnWriteHook();
// START MOUSE MOVEMENT EMULATION
	bool InitOnGetCursorPosHook();
	void ShutdownGetCursorPosHook();

	bool InitOnSetCursorPosHook();
	void ShutdownSetCursorPosHook();
// END MOUSE MOVEMENT

	void Tick(); 
	void OnReadPacket(DWORD wParam, UINT nSocketNotifyType);
	void OnWritePacket(LPCSTR pPacket, int nLength);

private: 
	virtual LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;	 	
	void static __fastcall Tick_Hooked(CInterface* ecx, void* edx);							 
	BOOL static __fastcall OnRecvdPacket_Hooked(CFieldWinSocket* ecx, void* edx, LPSTR pPacket, int nLength, BYTE nSeq); //not currently used
	int static __fastcall OnReadPacket_Hooked(CAtumapplication* ecx, void* edx, DWORD wParam, UINT nSocketNotifyType); 		
	int static __fastcall OnWritePacket_Hooked(CWinSocket* ecx, void* edx, LPCSTR pPacket, int nLength);

// START MOUSE MOVEMENT EMULATION
	BOOL static __stdcall OnGetCursorPos_Hooked(LPPOINT lpPoint);
	BOOL static __stdcall OnSetCursorPos_Hooked(int x, int y);
// END MOUSE MOVEMENT

private:
	std::unique_ptr<VMTHook<CInterface*>> m_interfacehook;
	InterfaceTickType m_orig_tick;		  

	std::unique_ptr<VMTHook<CFieldWinSocket*>> m_fieldsockethooks;
	WinSocketOnRecvdPacketType m_orig_onrecvdpacket;
	
	std::unique_ptr<TrampolineHook<CAtumApplicationOnRecvFieldSocketMessageType>> m_OnRecvFieldSocketMessagehook;
	CAtumApplicationOnRecvFieldSocketMessageType m_orig_OnRecvFieldSocketMessage;

	std::unique_ptr<TrampolineHook<CWinSocketWriteType>> m_OnWritePackethook;
	CWinSocketWriteType m_orig_OnWritePacket;
	
	// Start Section MOUSE MOVEMENT EMULATION
	std::unique_ptr<TrampolineHook<GetCursorPosType>> m_OnGetCursorPos;
	GetCursorPosType m_orig_OnGetCursorPos;

	std::unique_ptr<TrampolineHook<SetCursorPosType>> m_OnSetCursorPos;
	SetCursorPosType m_orig_OnSetCursorPos;

	POINT m_cur_mousepos;
	bool m_emulate_mouse;
	// End Section MOUSE MOVEMENT EMULATION

	FeatureContainer m_features;

	std::chrono::microseconds m_lastTick;
	std::chrono::microseconds m_tickTime;

	bool m_allow_notify_sounds;
	bool m_allow_notify_popups;
	std::unique_ptr<PersistingTools> m_persistingTools;
	bool m_block_mouse;

	std::unique_ptr<IOPacketManager> m_packetmanager;
};