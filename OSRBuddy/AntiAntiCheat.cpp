#include "osrb_pch.h"
#include "AntiAntiCheat.h"
#include <windows.h>
#include <vector>
#include <algorithm>

void AntiAntiCheat::ManualFreeLibraryAndExitThread(LPVOID imageBase, SIZE_T imageSize, DWORD exitCode)
{
    // orig from https://www.unknowncheats.me/forum/general-programming-and-reversing/304753-simple-function-cleanly-unload-manually-mapped-cheats.html

    auto kernelmodule = GetModuleHandle("Kernel32.dll");
    if (kernelmodule)
    {
        void* exitThread = GetProcAddress(kernelmodule, "ExitThread");
        void* virtualFree = GetProcAddress(kernelmodule, "VirtualFree");   

        __asm
        {
            mov esi, imageSize
            mov edi, imageBase
            push exitCode
            push MEM_RELEASE
            push esi
            push edi
            push exitThread
            mov esi, virtualFree
            jmp esi
        }
    }
} 

typedef struct _PEB_LDR_DATA {
    UINT8 _PADDING_[12];
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;


typedef struct _PEB {
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    PPEB_LDR_DATA Ldr;
} PEB, * PPEB;



typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    VOID* DllBase;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef struct _UNLINKED_MODULE
{
    HMODULE hModule;
    PLIST_ENTRY RealInLoadOrderLinks;
    PLIST_ENTRY RealInMemoryOrderLinks;
    PLIST_ENTRY RealInInitializationOrderLinks;
    PLDR_DATA_TABLE_ENTRY Entry;
} UNLINKED_MODULE;

#define UNLINK(x)					\
	(x).Flink->Blink = (x).Blink;	\
	(x).Blink->Flink = (x).Flink;

#define RELINK(x, real)			\
	(x).Flink->Blink = (real);	\
	(x).Blink->Flink = (real);	\
	(real)->Blink = (x).Blink;	\
	(real)->Flink = (x).Flink;

std::vector<UNLINKED_MODULE> UnlinkedModules;

struct FindModuleHandle
{
    HMODULE m_hModule;
    FindModuleHandle(HMODULE hModule) : m_hModule(hModule)
    {
    }
    bool operator() (UNLINKED_MODULE const& Module) const
    {
        return (Module.hModule == m_hModule);
    }
};

void AntiAntiCheat::RelinkModuleToPEB(HMODULE hModule)
{
    std::vector<UNLINKED_MODULE>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));

    if (it == UnlinkedModules.end())
    {
        //DBGOUT(TEXT("Module Not Unlinked Yet!"));
        return;
    }

    RELINK((*it).Entry->InLoadOrderLinks, (*it).RealInLoadOrderLinks);
    RELINK((*it).Entry->InInitializationOrderLinks, (*it).RealInInitializationOrderLinks);
    RELINK((*it).Entry->InMemoryOrderLinks, (*it).RealInMemoryOrderLinks);
    UnlinkedModules.erase(it);
}

void AntiAntiCheat::UnlinkModuleFromPEB(HMODULE hModule)
{
    std::vector<UNLINKED_MODULE>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));
    if (it != UnlinkedModules.end())
    {
        //DBGOUT(TEXT("Module Already Unlinked!"));
        return;
    }

#ifdef _WIN64
    PPEB pPEB = (PPEB)__readgsqword(0x60);
#else
    PPEB pPEB = (PPEB)__readfsdword(0x30);
#endif

    PLIST_ENTRY CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;
    PLDR_DATA_TABLE_ENTRY Current = NULL;

    while (CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != NULL)
    {
        Current = CONTAINING_RECORD(CurrentEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
        if (Current->DllBase == hModule)
        {
            UNLINKED_MODULE CurrentModule = { 0 };
            CurrentModule.hModule = hModule;
            CurrentModule.RealInLoadOrderLinks = Current->InLoadOrderLinks.Blink->Flink;
            CurrentModule.RealInInitializationOrderLinks = Current->InInitializationOrderLinks.Blink->Flink;
            CurrentModule.RealInMemoryOrderLinks = Current->InMemoryOrderLinks.Blink->Flink;
            CurrentModule.Entry = Current;
            UnlinkedModules.push_back(CurrentModule);

            UNLINK(Current->InLoadOrderLinks);
            UNLINK(Current->InInitializationOrderLinks);
            UNLINK(Current->InMemoryOrderLinks);

            break;
        }

        CurrentEntry = CurrentEntry->Flink;
    }
}

typedef struct _PROCESS_BASIC_INFORMATION {
    PVOID Reserved1;
    PPEB PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    PVOID Reserved3;
} PROCESS_BASIC_INFORMATION;
typedef PROCESS_BASIC_INFORMATION* PPROCESS_BASIC_INFORMATION;

bool AntiAntiCheat::PatchDebugFlag()
{
    typedef DWORD(WINAPI* PNtQueryInformationProcess)(HANDLE, DWORD, PVOID, DWORD, PVOID);

    ULONG returnlength;
    static bool initialized = false;
    static PROCESS_BASIC_INFORMATION pbi;
    if (!initialized)
    {
        HMODULE hNtDll = LoadLibrary("ntdll.dll");
        if (hNtDll == NULL)
        {
            return false;
        }

        PNtQueryInformationProcess fnNtQueryInforamtionProcess = (PNtQueryInformationProcess)GetProcAddress(hNtDll, "NtQueryInformationProcess");
        if (fnNtQueryInforamtionProcess)
        {
            if (0 == fnNtQueryInforamtionProcess(GetCurrentProcess(), 0/*ProcessBasicInformation*/, &pbi, sizeof(PROCESS_BASIC_INFORMATION), &returnlength))
            {
                initialized = true;
            }
        }

        FreeLibrary(hNtDll);
        if (!initialized)
        {
            return false;
        }
    }
    pbi.PebBaseAddress->BeingDebugged = 0;
    return true;
}