#include "D3DInternalBase.h"
#include "ImGuiBase.h"
#include "Utility.h"
#include <functional>
#include "Trampoline.h"

enum class D3D9DeviceIndex : int
{
    Reset       = 16,
    Present     = 17,
    EndScene    = 42
};

using D3D9VTABLE = BYTE*[175];

extern D3DInternalBase* g_D3DInternalBase = nullptr;

bool D3DInternalBase::GetD3D9DeviceVtable(void** pTable, size_t Size)
{
    {
        if (!pTable)
            return false;

        IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

        if (!pD3D)
            return false;

        IDirect3DDevice9* pDummyDevice = NULL;

        // options to create dummy device
        D3DPRESENT_PARAMETERS d3dpp = {};
        d3dpp.Windowed = false;
        d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp.hDeviceWindow = Utility::FindWindowFromProcessId(GetCurrentProcessId());

        HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

        if (dummyDeviceCreated != S_OK)
        {
            // may fail in windowed fullscreen mode, trying again with windowed mode
            d3dpp.Windowed = !d3dpp.Windowed;

            dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

            if (dummyDeviceCreated != S_OK)
            {
                pD3D->Release();
                return false;
            }
        }

        memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

        pDummyDevice->Release();
        pD3D->Release();
        return true;
    }
}

LRESULT D3DInternalBase::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{ 
    if (g_D3DInternalBase->WindowProcedure(hwnd, msg, wParam, lParam)) {
        return 1;
    } 
    if (g_D3DInternalBase->m_imguimenu && g_D3DInternalBase->m_imguimenu->WindowProcedure(hwnd, msg, wParam, lParam)) {
        return 1;
    }

    return CallWindowProc(g_D3DInternalBase->m_OriginalWndproc, hwnd, msg, wParam, lParam);
}


long __stdcall D3DInternalBase::EndScene_hooked(IDirect3DDevice9* device)
{          
    g_D3DInternalBase->OnEndScene(device);
    return g_D3DInternalBase->m_orig_endscene(device);
}

HRESULT __stdcall D3DInternalBase::Present_hooked(IDirect3DDevice9* device,const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{      
    g_D3DInternalBase->OnPresent(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    return g_D3DInternalBase->m_orig_present(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
} 

HRESULT __stdcall D3DInternalBase::Reset_hooked(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
{  
    g_D3DInternalBase->OnBeforeReset(device, params);
    HRESULT hr = g_D3DInternalBase->m_orig_reset(device, params);
    g_D3DInternalBase->OnAfterReset(device, params);
    return hr;
}


D3DInternalBase::D3DInternalBase()
{
    g_D3DInternalBase = this;
    m_doUnload = false;
    std::random_device device;
    m_random_generator = std::unique_ptr<std::mt19937>(new std::mt19937(device()));

}

D3DInternalBase::~D3DInternalBase()
{
    ShutdownD3DHooks();
    UnhookWindowProcedure();
}

bool D3DInternalBase::InitD3DHooks(RenderHookType hooktype, RenderHookOption hook, IDirect3DDevice9* device)
{
    m_d3d9device = device;
    m_hookoption = hook;
    m_hooktype   = hooktype;

    switch (hooktype)
    {
    case RenderHookType::VMT:
        m_d3d9_vmt_hooks = std::unique_ptr<VMTHook<IDirect3DDevice9>>(new VMTHook<IDirect3DDevice9>(m_d3d9device));
        if (!m_d3d9_vmt_hooks->setupvmt(m_d3d9device)) {
            return false;
        }

        switch (hook)
        {
        case RenderHookOption::ENDSCENE:
            m_orig_endscene = m_d3d9_vmt_hooks->get_original<EndSceneType>((int)D3D9DeviceIndex::EndScene);
            m_d3d9_vmt_hooks->hook_index((int)D3D9DeviceIndex::EndScene, (BYTE*)D3DInternalBase::EndScene_hooked);             
            break;
        case RenderHookOption::PRESENT:
            m_orig_present = m_d3d9_vmt_hooks->get_original<PresentType>((int)D3D9DeviceIndex::Present);
            m_d3d9_vmt_hooks->hook_index((int)D3D9DeviceIndex::Present, (BYTE*)D3DInternalBase::Present_hooked);            
            break;
        } 
        m_orig_reset = m_d3d9_vmt_hooks->get_original<ResetType>((int)D3D9DeviceIndex::Reset);
        m_d3d9_vmt_hooks->hook_index((int)D3D9DeviceIndex::Reset, (BYTE*)D3DInternalBase::Reset_hooked);
        return true;

    case RenderHookType::TRAMPOLINE: 
        std::uintptr_t* vtbl = *(std::uintptr_t**)m_d3d9device;  
        switch (hook)
        {
        case RenderHookOption::ENDSCENE:
            m_trampoline_endscene = std::make_unique<TrampolineHook<EndSceneType>>((BYTE*)vtbl[(int)D3D9DeviceIndex::EndScene], (byte*)D3DInternalBase::EndScene_hooked, 7);
            m_orig_endscene = m_trampoline_endscene->GetOriginal();
            if (!m_trampoline_endscene->Hook()) {
                return false;
            }             
            break; 
        case RenderHookOption::PRESENT:
            m_trampoline_present = std::make_unique<TrampolineHook<PresentType>>((BYTE*)vtbl[(int)D3D9DeviceIndex::Present], (byte*)D3DInternalBase::Present_hooked, 7);
            m_trampoline_present->GetOriginal();
            if (!m_trampoline_present->Hook()) {
                return false;
            } 
            break;
        } 
                      
        m_trampoline_reset = std::make_unique<TrampolineHook<ResetType>>((BYTE*)vtbl[(int)D3D9DeviceIndex::Reset], (byte*)D3DInternalBase::Reset_hooked, 14);
        m_orig_reset = m_trampoline_reset->GetOriginal();
        if (!m_trampoline_reset->Hook()) {
            return false;
        }       
        
        return true;        
    }
}

void D3DInternalBase::ShutdownD3DHooks()
{
    if (m_hooktype == RenderHookType::VMT)
    {
        if (m_d3d9_vmt_hooks) 
        {
            m_d3d9_vmt_hooks->unhook_all();
            Sleep(100);
            m_d3d9_vmt_hooks.reset();
        }
    }
    else if(m_hooktype == RenderHookType::TRAMPOLINE)
    {
        if (m_trampoline_endscene)
        {
            m_trampoline_endscene->Unhook();
            Sleep(100);
            m_trampoline_endscene.reset();            
        }
        if (m_trampoline_present)
        {
            m_trampoline_present->Unhook();
            Sleep(100);
            m_trampoline_present.reset();
        }
        if (m_trampoline_reset)
        {
            m_trampoline_reset->Unhook();
            Sleep(100);
            m_trampoline_reset.reset();
        } 
    }     
}

void D3DInternalBase::InitiateAppShutdown()
{       
    m_doUnload = true;
}

void D3DInternalBase::OnEndScene(IDirect3DDevice9* device)
{
    Render(device);

    if (m_imguimenu && m_imguimenu->IsOpen()) {
        m_imguimenu->Render(device);
    }
}

void D3DInternalBase::OnPresent(IDirect3DDevice9* device, const RECT*, const RECT*, HWND, const RGNDATA*)
{
    Render(device);

    if (m_imguimenu && m_imguimenu->IsOpen()) {
        m_imguimenu->Render(device);
    }
}

void D3DInternalBase::OnBeforeReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
{
    m_renderer->OnLostDevice();
    m_imguimenu->BeforeReset();
}

void D3DInternalBase::OnAfterReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
{
    m_renderer->OnResetDevice();
    m_imguimenu->AfterReset();
}

int D3DInternalBase::GetRandInt32(int min, int max)
{
    if (min == max) {
        return min;
    }

    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(*m_random_generator.get());
}

bool D3DInternalBase::HookWindowProcedure(HWND window)
{
    SetLastError(0);
    m_OriginalWndproc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(window, GWL_WNDPROC));

    if (GetLastError() == 0)
    {
        SetWindowLongPtr(window, GWL_WNDPROC, reinterpret_cast<LONG>(&D3DInternalBase::WndProc));

        if (GetLastError() == 0)
        {
            m_hWindow = window;
            return true;
        }            
    }
    return false;
}

void D3DInternalBase::UnhookWindowProcedure()
{
    if (m_OriginalWndproc)
    {
        SetWindowLongPtr(m_hWindow, GWLP_WNDPROC, reinterpret_cast<LONG>(m_OriginalWndproc));
        Sleep(100);
        m_OriginalWndproc = nullptr;           
    }
}