#include "ImGuiBase.h"   
#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"  
 
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ImGuiBase::ImGuiBase()
{
    m_initialised   = false;
    m_isOpen        = false;
    m_blockInput    = false;
}

ImGuiBase::~ImGuiBase()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

bool ImGuiBase::Init(IDirect3DDevice9* device)
{
    D3DDEVICE_CREATION_PARAMETERS device_params;
    device->GetCreationParameters(&device_params);
    m_hWindow = device_params.hFocusWindow;

    ImGui::CreateContext();
    if (!ImGui_ImplWin32_Init(m_hWindow)) {
        return false;
    }

    if (!ImGui_ImplDX9_Init(device)) {
        return false;
    }

    m_initialised = true;
    return true;
}

void ImGuiBase::Toggle()
{
    m_isOpen = !m_isOpen;
}

void ImGuiBase::ShowMenu(bool open)
{
    m_isOpen = open;
}

bool ImGuiBase::IsOpen()
{
    return m_isOpen;
}

void ImGuiBase::SetBlockInput(bool block)
{
    m_blockInput = block;
}
     
void ImGuiBase::ImGuiBeginFrame()
{
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void ImGuiBase::ImGuiEndFrame()
{
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiBase::BeforeReset()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
}

void ImGuiBase::AfterReset()
{
    ImGui_ImplDX9_CreateDeviceObjects();
}

void ImGuiBase::Render(IDirect3DDevice9* device)
{
    if (!m_initialised)
    {
        if (!Init(device)) {
            return;
        }
    } 

    ImGuiBeginFrame();
    Render();
    ImGuiEndFrame();
}

LRESULT ImGuiBase::WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_INSERT:
            Toggle();
            return 1;
        }
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:                                                                                                                             
    case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_MOUSEHWHEEL:
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_CHAR:
    case WM_SETCURSOR:
    case WM_DEVICECHANGE:
        if (IsOpen())
        {    
            LRESULT res = ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
            if (m_blockInput || ImGui::GetIO().WantCaptureMouse)
            {                 
                return 1;
            }
            else 
            {
                return res;
            }
            
        }
    default:
        return 0;
    }
}
