#include "OSRBuddy.h"
#include "Utility.h"
#include <thread>            
#include "OSRAPI.h"
      
#include "KitBot.h"
#include "TestItemUse.h"
#include "GambleBot.h"
#include "EnchantBot.h"
#include "GrindBot.h"
#include "FactoryBot.h"
#include "Visuals.h"
#include "Miscellaneous.h"
                                
#include "AntiAntiCheat.h"
#include "PatternManager.h"
#include "Windowsx.h"  // get_x_lpraram && get_y_lparam


OSRBuddyMain* g_osrbuddy = nullptr;  // for the static hook methods


LRESULT OSRBuddyMain::WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{       
    for (auto& feature : m_features) 
    {
        if (feature->IsEnabled()) {
            feature->WindowProc(hwnd, msg, wParam, lParam);
        }
    }
    
    switch (msg)
    {
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_END:
            DisableAllFeatures();
            break;
        case VK_DELETE:
            InitiateAppShutdown();
            break;
        }
        break;
        case WM_QUIT:
        case WM_CLOSE:
        case WM_DESTROY:
            InitiateAppShutdown();
            break;   
        case WM_MOUSEMOVE:
            if (m_block_mouse)
            {
                return 1;
            }

            if (m_emulate_mouse)
            {
                m_cur_mousepos.x = GET_X_LPARAM(lParam);
                m_cur_mousepos.y = GET_Y_LPARAM(lParam);
                ClientToScreen(OSR_API->GetAtumApplication()->m_hWnd, &m_cur_mousepos);
            }
    }
    return 0;
}

void _fastcall OSRBuddyMain::Tick_Hooked(CInterface* ecx, void* edx)
{
    PUSHCPUSTATE
    g_osrbuddy->Tick(); 
    POPCPUSTATE
    g_osrbuddy->m_orig_tick(ecx);    
}

BOOL __fastcall OSRBuddyMain::OnRecvdPacket_Hooked(CFieldWinSocket* ecx, void* edx, LPSTR pPacket, int nLength, BYTE nSeq)
{        
    BOOL res =  g_osrbuddy->m_orig_onrecvdpacket(ecx, pPacket, nLength, nSeq); 
    return res;
}


BOOL __fastcall OSRBuddyMain::OnReadPacket_Hooked(CAtumapplication* ecx, void* edx, DWORD wParam, UINT nSocketNotifyType)
{
    PUSHCPUSTATE
    g_osrbuddy->OnReadPacket(wParam, nSocketNotifyType); 
    POPCPUSTATE
    return g_osrbuddy->m_orig_OnRecvFieldSocketMessage(ecx, wParam, nSocketNotifyType);
}

int __fastcall OSRBuddyMain::OnWritePacket_Hooked(CWinSocket* ecx, void* edx, LPCSTR pPacket, int nLength)
{
    PUSHCPUSTATE
    g_osrbuddy->OnWritePacket(pPacket, nLength); 
    POPCPUSTATE
    return g_osrbuddy->m_orig_OnWritePacket(ecx, pPacket, nLength);
}

BOOL __stdcall OSRBuddyMain::OnGetCursorPos_Hooked(LPPOINT lpPoint)
{ 
    return g_osrbuddy->GetCursorPosition(lpPoint);
}

BOOL __stdcall OSRBuddyMain::OnSetCursorPos_Hooked(int x, int y)
{             
    return g_osrbuddy->SetCursorPosition(x, y);
}  

void OSRBuddyMain::MessageBoxThreadFunction(std::string message, std::string header, NotifyType type, std::function<void(int)> callback)
{     
    int uType = MB_SYSTEMMODAL;
    switch (type)
    {
    case NotifyType::Information:
        uType |= MB_ICONINFORMATION;
        break;
    case NotifyType::Warning:
        uType |= MB_ICONWARNING;
        break;
    case NotifyType::Error:
        uType |= MB_ICONERROR;
        break;
    }  

    int returnval = MessageBox(NULL, message.c_str(), header.c_str(), uType);
    if (callback) {
        callback(returnval);
    }
}

void OSRBuddyMain::Render(IDirect3DDevice9* device)
{
    m_renderer->Begin();
    for (auto& feature : m_features) {
        feature->Render(m_renderer.get());
    }
    m_renderer->End();
} 

OSRBuddyMain::OSRBuddyMain()
{
    g_osrbuddy = this;
    m_lastTick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    m_cur_mousepos = POINT();
    m_emulate_mouse = false;
    m_fieldsockethooks = nullptr;
    m_interfacehook = nullptr;
    m_lastTick = 0ms;
    m_OnGetCursorPos = nullptr;
    m_OnSetCursorPos = nullptr;
    m_OnRecvFieldSocketMessagehook = nullptr;
    m_OnWritePackethook = nullptr;
    m_orig_onrecvdpacket = nullptr;
    m_orig_OnGetCursorPos = nullptr;
    m_orig_OnRecvFieldSocketMessage = nullptr;
    m_orig_OnSetCursorPos = nullptr;
    m_orig_OnSetCursorPos = nullptr;
    m_orig_tick = nullptr;

    m_allow_notify_popups = false;
    m_allow_notify_sounds = true;
}

OSRBuddyMain::~OSRBuddyMain()
{                             
    ShutdownHooks();
    ReleaseFeatures();
}

bool OSRBuddyMain::Start()
{   
    try {
#ifdef b_DEBUG
        if (!Console::GetInstance()->Init()) {
            throw exception("Console allocation failed");
        }
#endif // _DEBUG 

        PatternManager::Init();

        if (!OldSchoolRivalsAPI::CreateAndCheckConsistence()) {
            throw exception("Structures outdated");
        }

        if (!IsWindow(OSR_API->GetMainWindow()))  {
            throw exception("Structures outdated");
        }
        
        if (!HookWindowProcedure(OSR_API->GetMainWindow())) {
           throw exception("WndProc Hook failed");
        }         
        
        m_imguimenu = std::make_unique<OSRImGuiMenu>(this);
        if (!m_imguimenu->Init(OSR_API->GetD3D9Device()))  {
            throw exception("ImGui failed to initialise");
        }    

        m_renderer = std::make_unique<D3D9Renderer>(OSR_API->GetD3D9Device());
                 
        //RegisterFeature(new KitBuffBot(this)); 
       // RegisterFeature(new GrindBot(this));          
        RegisterFeature(new GambleBot(this));
        RegisterFeature(new EnchantBot(this));
        //RegisterFeature(new FactoryBot(this));
        //RegisterFeature(new Miscellaneous(this));    
        //RegisterFeature(new TestItemUse(this));

        if (!InitD3DHooks(RenderHookType::TRAMPOLINE, RenderHookOption::ENDSCENE, OSR_API->GetD3D9Device())) {
            throw exception("D3D9 Hooks failed to initialise");
        }
         
        if (!InitTickHook()) {
            throw exception("TickHook failed to initialise");
        } 

        // not used
        //if (!InitOnRecvdPacketHook()) {
        //    throw exception("OnRevdPacketHook failed to initialise");
        //}            
        
        if (!InitOnReadPacketHook()) {
            throw exception("ReadPacketHook failed to initialise");
        }     

        if(!InitOnWriteHook()) {
            throw exception("WritePacketHook failed to initialise");
        }            

        if (!InitOnGetCursorPosHook() || !InitOnSetCursorPosHook()) {
            throw exception("Mouseemulation failed to initialise");
        }

        m_imguimenu->ShowMenu(true);
    }
    catch (exception exc)
    {
        ShutdownHooks();
        MessageBoxA(0, exc.what(), "OSRBuddy", 0);
        return false;
    }

    while (!m_doUnload)
    {
        std::this_thread::sleep_for(10ms);
    }

    for (auto& elem : m_features)
    {
        elem->Enable(false);
    }
    
    ShutdownHooks();
    ReleaseFeatures();
    return true;
}
   
void OSRBuddyMain::ShutdownHooks()
{    
    ShutdownOnWriteHook();
    //ShutdownOnRecvdPacketHook();
    ShutdownOnReadPacketHook();
    UnhookWindowProcedure();            
    ShutdownTickHook();
    ShutdownD3DHooks(); 
    ShutdownGetCursorPosHook();
    ShutdownSetCursorPosHook();
    Sleep(100); // not 100% sure why but this prevents crashes in release mode
}

bool OSRBuddyMain::InitTickHook()
{         
    if (m_interfacehook) {
        return false;
    }
       
    m_interfacehook = std::make_unique<VMTHook<CInterface*>>();
    if (!m_interfacehook->setupvmt((CInterface**)OSR_API->GetInterface())) {
        return false;
    }
    
    m_orig_tick = g_osrbuddy->m_interfacehook->get_original<InterfaceTickType>(6);
    m_interfacehook->hook_index(6, (BYTE*)OSRBuddyMain::Tick_Hooked);
    return true;
}

void OSRBuddyMain::ShutdownTickHook()
{
    if (m_interfacehook)
    {         
        m_interfacehook->unhook_all();
        Sleep(100);
        m_interfacehook.reset();
    }
}

void OSRBuddyMain::NotifySound(NotifyType type)
{   
    if (!NotificationSoundAllowed()) {
        return;
    }

    switch (type)
    {
    case NotifyType::Information:
        MessageBeep(MB_ICONINFORMATION);
        break;
    case NotifyType::Warning:
        MessageBeep(MB_ICONWARNING);
        break;
    case NotifyType::Error:
        MessageBeep(MB_ICONERROR);
        break;
    default:
        MessageBeep(MB_ICONWARNING);
        break;
    }
}


void OSRBuddyMain::OpenMessageBoxAsync(std::string message, std::string header, NotifyType type, std::function<void(int)> callback)
{ 
    std::thread msgboxthread(OSRBuddyMain::MessageBoxThreadFunction, message, header, type, callback);
    msgboxthread.detach();
}


void OSRBuddyMain::OpenMessageBoxAsync(std::string message, std::string header, NotifyType type)
{
    std::thread msgboxthread(OSRBuddyMain::MessageBoxThreadFunction, message, header, type, nullptr);
    msgboxthread.detach();
}

void OSRBuddyMain::BlockMouseInput(bool on)
{
    m_block_mouse = on;
}

bool OSRBuddyMain::InitOnReadPacketHook()
{    
    if (m_OnRecvFieldSocketMessagehook) {
        return false;
    }

    PatternInfo pinfo = PatternManager::Get(OffsetIdentifier::CAtumApplication__OnRecvFieldSocketMessage);
    m_OnRecvFieldSocketMessagehook = std::make_unique<TrampolineHook<CAtumApplicationOnRecvFieldSocketMessageType>>(pinfo.address, (byte*)OSRBuddyMain::OnReadPacket_Hooked, pinfo.trampoline_length);

    m_orig_OnRecvFieldSocketMessage = m_OnRecvFieldSocketMessagehook->GetOriginal();
    if (!m_OnRecvFieldSocketMessagehook->Hook()) {
        return false;
    }

    return true;
}

void OSRBuddyMain::ShutdownOnReadPacketHook()
{
    if (m_OnRecvFieldSocketMessagehook)
    {
        m_OnRecvFieldSocketMessagehook->Unhook();
        Sleep(100);
        m_OnRecvFieldSocketMessagehook.reset();
    }
}

bool OSRBuddyMain::InitOnWriteHook()
{
    if (m_OnWritePackethook) {
        return false;
    }                     

    PatternInfo pinfo = PatternManager::Get(OffsetIdentifier::CWinSocket__Write);
    m_OnWritePackethook = std::make_unique<TrampolineHook<CWinSocketWriteType>>(pinfo.address, (byte*)OSRBuddyMain::OnWritePacket_Hooked, pinfo.trampoline_length);

    m_orig_OnWritePacket = m_OnWritePackethook->GetOriginal();
    if (!m_OnWritePackethook->Hook()) {
        return false;
    }

    return true;
}

void OSRBuddyMain::ShutdownOnWriteHook()
{
    if (m_OnWritePackethook)
    {
        m_OnWritePackethook->Unhook();
        Sleep(100);
        m_OnWritePackethook.reset();
    }
}

bool OSRBuddyMain::InitOnGetCursorPosHook()
{
    if (m_OnGetCursorPos) {
        return false;
    }                                 

    m_OnGetCursorPos = std::make_unique<TrampolineHook<GetCursorPosType>>((byte*)GetCursorPos, (byte*)OSRBuddyMain::OnGetCursorPos_Hooked, 5);

    m_orig_OnGetCursorPos = m_OnGetCursorPos->GetOriginal();
    if (!m_OnGetCursorPos->Hook()) {
        return false;
    }

    return true;
}

void OSRBuddyMain::ShutdownGetCursorPosHook()
{
    if (m_OnGetCursorPos)
    {
        m_OnGetCursorPos->Unhook();
        Sleep(100);
        m_OnGetCursorPos.reset();
    }
}

bool OSRBuddyMain::InitOnSetCursorPosHook()
{
    if (m_OnSetCursorPos) {
        return false;
    }
        
    m_OnSetCursorPos = std::make_unique<TrampolineHook<SetCursorPosType>>((byte*)SetCursorPos, (byte*)OSRBuddyMain::OnSetCursorPos_Hooked, 6);
    m_orig_OnSetCursorPos = m_OnSetCursorPos->GetOriginal();

    if (!m_OnSetCursorPos->Hook()) {
        return false;
    }

    return true;
}

void OSRBuddyMain::ShutdownSetCursorPosHook()
{
    if (m_OnSetCursorPos)
    {
        m_OnSetCursorPos->Unhook();
        Sleep(100);
        m_OnSetCursorPos.reset();
    }
}


void OSRBuddyMain::Tick()
{
   AntiAntiCheat::PatchDebugFlag();
   
   // update internal elapsed time
   std::chrono::microseconds current = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
   m_tickTime = current - m_lastTick;
   m_lastTick = current;

   for (auto& feature : m_features) 
   {       
        feature->Tick();
   }
}

void OSRBuddyMain::RegisterFeature(BuddyFeatureBase* feature)
{
    // dont register a second time
    if (GetFeatureByType(feature->GetType())) {
        return;
    }             
    m_features.push_back(feature);
}

FeatureContainer OSRBuddyMain::GetAllFeatures() const
{
    return m_features;
}

void OSRBuddyMain::ReleaseFeatures()
{
    for (auto& feature : m_features)
    {
        delete feature;
    } 
    m_features.clear();
}

void OSRBuddyMain::DisableAllFeatures()
{
    for (auto& feature : m_features) {
        feature->Enable(false);
    }                                
    m_imguimenu->ShowMenu(false);
}

std::chrono::microseconds OSRBuddyMain::GetTickTime()
{
    return m_tickTime;
}

void OSRBuddyMain::EnableMouseEmulation(bool on)
{
    if (m_emulate_mouse == on) {
        return;
    }

    if (on)
    {
        m_orig_OnGetCursorPos(&m_cur_mousepos);
    }       
    m_emulate_mouse = on;

    if (!on) 
    {
        m_orig_OnSetCursorPos(m_cur_mousepos.x, m_cur_mousepos.y);
    }
}

bool OSRBuddyMain::SetCursorPosition(int x, int y)
{
    if (m_emulate_mouse)
    {
        m_cur_mousepos.x = x;
        m_cur_mousepos.y = y;   
        return true;
    }
    else
    {
        return m_orig_OnSetCursorPos(x, y);

        /*
        INPUT input;
        ZeroMemory(&input, sizeof(input));
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = x;
        input.mi.dy = y;
        ::SendInput(1, &input, sizeof(INPUT));
        return true;
        */
    } 
}

bool OSRBuddyMain::GetCursorPosition(LPPOINT pos)
{
    if (m_emulate_mouse)
    {
        *pos = m_cur_mousepos;
        return true;
    }
    else
    {
        return m_orig_OnGetCursorPos(pos);
    }
}

void OSRBuddyMain::OnReadPacket(DWORD wParam, UINT nSocketNotifyType)
{       
    MessageType_t	nType = 0;       
    CFieldWinSocket* pFieldSocket = OSR_API->GetFieldWinSocket(nSocketNotifyType);   
    if (!pFieldSocket || pFieldSocket->m_queueRecvMessage.empty()) {
        return;
    }
    
    std::queue<char*> packet_buffer = pFieldSocket->m_queueRecvMessage;     
    char* packet = NULL;                

    while (!packet_buffer.empty())
    {
        packet = packet_buffer.front();
        packet_buffer.pop();                                            
        nType = *(MessageType_t*)packet;  
        for (auto feature : m_features)
        {
            if (feature->OnReadPacket(nType, reinterpret_cast<byte*>(packet + sizeof(MessageType_t)))) {
                break;
            }
        }   
    }
  
}

void OSRBuddyMain::OnWritePacket(LPCSTR pPacket, int nLength)
{
    MessageType_t	nType = 0;
    byte* packet = (byte*)pPacket;
    nType = *(MessageType_t*)packet;

    for (auto feature : m_features)
    {
        if (feature->OnWritePacket(nType, packet + sizeof(MessageType_t))) {
            break;
        }
    }
}
  
ImGuiBase* OSRBuddyMain::GetMenu()
{
    return m_imguimenu.get();
}

BuddyFeatureBase* OSRBuddyMain::GetFeatureByType(FeatureType type) const
{
    for (auto& elem : m_features) 
    {
        if (elem->GetType() == type) {
            return elem;
        }              
    }
    return nullptr;
}