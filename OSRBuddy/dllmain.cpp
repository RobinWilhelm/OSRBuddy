// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "OSRBuddy.h"
#include "AntiAntiCheat.h"
#include "Utility.h"
#include "BuddyAPI.h"


bool is_manual_mapped = false;
BUDDY_API MapEntryInfo mapinfo;

HMODULE this_module = 0;

using DllMainFnType = BOOL(__stdcall*)(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);

void MainThread()
{
    {
        OSRBuddyMain osrbuddy;
        osrbuddy.Start();
    } // ensure destruction 

    if (!is_manual_mapped)
    {
        AntiAntiCheat::RelinkModuleToPEB(this_module);
        FreeLibraryAndExitThread(this_module, 0);
    }
    else
    {
        AntiAntiCheat::ManualFreeLibraryAndExitThread((LPVOID)mapinfo.imagebase, mapinfo.imagesize, 0);
    }    
}

   
extern "C" BUDDY_API bool ManualEntry(LPVOID lpThreadParameter)
{
    is_manual_mapped = true;  

    DllMainFnType entry = (DllMainFnType)mapinfo.entrypoint;
    entry((HMODULE)mapinfo.imagebase, DLL_PROCESS_ATTACH, 0);
    return true;
}
     
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: 
        if (is_manual_mapped)
        {
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
        }
        else
        {
            DisableThreadLibraryCalls(hModule);
            this_module = hModule;
            AntiAntiCheat::UnlinkModuleFromPEB(this_module);
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
        }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

