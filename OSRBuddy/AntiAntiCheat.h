#pragma once
#include <windows.h>

class AntiAntiCheat
{
public:
    // FreeLibraryAndExitThread function for manually mapped modules
    static void ManualFreeLibraryAndExitThread(LPVOID imageBase, SIZE_T imageSize, DWORD exitCode);

    // Set PEB BeeingDebugged flag to 0
    static bool PatchDebugFlag();

    // simple peb unlinking from https://www.unknowncheats.me/forum/c-and-c-/81519-unlinking-relinking-loaded-dlls-peb.html
    static void UnlinkModuleFromPEB(HMODULE hModule);
    static void RelinkModuleToPEB(HMODULE hModule);
};

