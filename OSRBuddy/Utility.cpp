#include "osrb_pch.h"
#include "Utility.h"
#include <winternl.h>

#include <Psapi.h>
#pragma comment( lib, "psapi.lib" )

#include <random>	 

#define INRANGE(x,a,b)		(x >= a && x <= b) 
#define getBits( x )		(INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte( x )		(getBits(x[0]) << 4 | getBits(x[1]))


// Structure used to communicate data from and to enumeration procedure
struct EnumData {
    DWORD dwProcessId;
    HWND hWnd;
};

BOOL CALLBACK EnumWindowsCallback(HWND hWnd, LPARAM lParam)
{
    // https://stackoverflow.com/questions/20162359/c-best-way-to-get-window-handle-of-the-only-window-from-a-process-by-process
    // Retrieve storage location for communication data
    EnumData& ed = *(EnumData*)lParam;
    DWORD dwProcessId = 0x0;
    // Query process ID for hWnd
    GetWindowThreadProcessId(hWnd, &dwProcessId);
    // Apply filter - if you want to implement additional restrictions,
    // this is the place to do so.
    if (ed.dwProcessId == dwProcessId) {
        // Found a window matching the process ID
        ed.hWnd = hWnd;
        // Report success
        SetLastError(ERROR_SUCCESS);
        // Stop enumeration
        return FALSE;
    }
    // Continue enumeration
    return TRUE;
    
}  

//https://stackoverflow.com/questions/38100667/windows-virtual-key-codes
std::string Utility::VirtualKeyCodeToString(uint32_t virtualKey)
{   
    UINT scanCode = MapVirtualKeyEx(virtualKey, MAPVK_VK_TO_VSC, GetKeyboardLayout(0));

    TCHAR szName[128];
    int result = 0;
    switch (virtualKey)
    {
    case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
    case VK_RCONTROL: case VK_RMENU:
    case VK_LWIN: case VK_RWIN: case VK_APPS:
    case VK_PRIOR: case VK_NEXT:
    case VK_END: case VK_HOME:
    case VK_INSERT: case VK_DELETE:
    case VK_DIVIDE:
    case VK_NUMLOCK:
        scanCode |= KF_EXTENDED;
    default:
        result = GetKeyNameTextA(scanCode << 16, szName, 128);
    }
    if (result == 0)
        throw std::system_error(std::error_code(GetLastError(), std::system_category()),
            "WinAPI Error occured.");
    return std::string(szName);
}

std::string Utility::GetTimeString(std::chrono::milliseconds ms)
{ 
    // convert to std::time_t in order to convert to std::tm (broken time)
    //auto timer = std::chrono::system_clock::to_time_t(std::chrono::time_point<std::chrono::system_clock>(ms));

    // convert to broken time
    std::tm bt;
    //localtime_s(&bt, &timer);

    std::ostringstream oss;

    bt.tm_sec = (ms.count() / 1000) % 60;
    bt.tm_min = (ms.count() / 60000) % 60;
    bt.tm_hour = (ms.count() / 3600000) % 24;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    //oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

int Utility::GetRandInt32(int min, int max)
{
    if (min >= max) {
        return min;
    }

    static std::random_device device;
    static std::mt19937 random_generator = std::mt19937(device());
                                    
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(random_generator);
}

HWND Utility::FindWindowFromProcessId(DWORD dwProcessId) {
    EnumData ed = { dwProcessId };
    if (!EnumWindows(EnumWindowsCallback, (LPARAM)&ed) &&
        (GetLastError() == ERROR_SUCCESS)) {
        return ed.hWnd;
    }
    return NULL;
}
       
PBYTE Utility::FindPatternEasy(std::string moduleName, std::string pattern)
{
    const PBYTE rangeStart = (PBYTE)GetModuleHandleA(moduleName.c_str());
    if (!rangeStart)
    {
        return nullptr;
    }                                  

    MODULEINFO miModInfo;
    if(!GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO)))
    {
        return nullptr;
    }

    const PBYTE rangeEnd = rangeStart + miModInfo.SizeOfImage;
    return FindPattern(rangeStart, rangeEnd, pattern.c_str());
}

void Utility::MoveMouse(uint32_t x, uint32_t y)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;// | MOUSEEVENTF_ABSOLUTE;
    input.mi.dx = x;
    input.mi.dy = y;
    ::SendInput(1, &input, sizeof(INPUT));
}

DWORD Utility::GetFontColor(char chr)
{
    switch (chr)
    {
    case RED_FONT:
        return (HFONT_ARGB(0x00, (BYTE)255, (BYTE)0, (BYTE)0));
    case GREEN_FONT:
        return (HFONT_ARGB(0x00, (BYTE)0, (BYTE)255, (BYTE)0));
    case BLUE_FONT:
        return (HFONT_ARGB(0x00, (BYTE)0, (BYTE)0, (BYTE)255));
    case YELLOW_FONT:
        return (HFONT_ARGB(0x00, (BYTE)255, (BYTE)255, (BYTE)0));
    case CYAN_FONT:
        return (HFONT_ARGB(0x00, (BYTE)0, (BYTE)255, (BYTE)255));
    case MAGENTA_FONT:
        return (HFONT_ARGB(0x00, (BYTE)255, (BYTE)0, (BYTE)255));
    case WHITE_FONT:
        return (HFONT_ARGB(0x00, (BYTE)255, (BYTE)255, (BYTE)255));
    case ENCHANT_FONT:
        return (HFONT_ARGB(0x00, (BYTE)245, (BYTE)185, (BYTE)48));
    case GRAY_FONT:
        return (HFONT_ARGB(0x00, (BYTE)208, (BYTE)208, (BYTE)208));
    case DARKBLUE_FONT:
        return (HFONT_ARGB(0x00, (BYTE)178, (BYTE)190, (BYTE)255));
#ifdef C_FONT_COLOR_ADD
    case PINK_FONT:
        return (HFONT_ARGB(0x00, (BYTE)235, (BYTE)197, (BYTE)238));
    case LIGHTGREEN_FONT:
        return (HFONT_ARGB(0x00, (BYTE)130, (BYTE)209, (BYTE)152));
    case BLACK_FONT:
        return (HFONT_ARGB(0x00, (BYTE)1, (BYTE)1, (BYTE)1));
    case TEAL_FONT:
        return (HFONT_ARGB(0x00, (BYTE)0, (BYTE)128, (BYTE)128));
    case NAVY_FONT:
        return (HFONT_ARGB(0x00, (BYTE)176, (BYTE)224, (BYTE)230));
    case STEELBLUE_FONT:
        return (HFONT_ARGB(0x00, (BYTE)32, (BYTE)178, (BYTE)170));
    case RBROWN_FONT:
        return (HFONT_ARGB(0x00, (BYTE)188, (BYTE)143, (BYTE)143));
#endif
    case LIGHTBLUE_FONT:
        return (HFONT_ARGB(0x00, (BYTE)0, (BYTE)170, (BYTE)255));
    case PALEPINK_FONT:
        return (HFONT_ARGB(0x00, (BYTE)235, (BYTE)197, (BYTE)238));
    case LIGHTGREEN_FONT:
        return (HFONT_ARGB(0x00, (BYTE)130, (BYTE)209, (BYTE)152));
    case BLACK_FONT:
        return (HFONT_ARGB(0x00, (BYTE)1, (BYTE)1, (BYTE)1));
    case ORANGE_FONT:
        return (HFONT_ARGB(0x00, (BYTE)255, (BYTE)165, (BYTE)0));
    case TAN_FONT:
        return (HFONT_ARGB(0x00, (BYTE)210, (BYTE)180, (BYTE)140));
    case SALMON_FONT:
        return (HFONT_ARGB(0x00, (BYTE)250, (BYTE)128, (BYTE)114));
    case CORNFLOWER_BLUE_FONT:
        return (HFONT_ARGB(0x00, (BYTE)104, (BYTE)147, (BYTE)247));
    case DARK_TURQUOISE_FONT:
        return (HFONT_ARGB(0x00, (BYTE)0, (BYTE)206, (BYTE)209));
    case HOT_PINK_FONT:
        return (HFONT_ARGB(0x00, (BYTE)255, (BYTE)105, (BYTE)180));
    case FIREBRICK_FONT:
        return (HFONT_ARGB(0x00, (BYTE)178, (BYTE)34, (BYTE)34));
    case GOLDENROD_FONT:
        return (HFONT_ARGB(0x00, (BYTE)218, (BYTE)165, (BYTE)32));
    case BROWN_FONT:
        return (HFONT_ARGB(0x00, (BYTE)143, (BYTE)93, (BYTE)63));
    case VIOLET_FONT:
        return (HFONT_ARGB(0x00, (BYTE)127, (BYTE)0, (BYTE)255));
    default:
        return (HFONT_ARGB(0x00, (BYTE)0, (BYTE)0, (BYTE)0));
    }
}

PBYTE Utility::FindPattern(const PBYTE rangeStart, const PBYTE rangeEnd, const char* pattern)
{   
    const unsigned char* pat = reinterpret_cast<const unsigned char*>(pattern);

    PBYTE firstMatch = 0;
    for (PBYTE pCur = rangeStart; pCur < rangeEnd; ++pCur) {
        if (*(PBYTE)pat == (BYTE)'\?' || *pCur == getByte(pat)) {
            if (!firstMatch) {
                firstMatch = pCur;
            }
            pat += (*(PWORD)pat == (WORD)'\?\?' || *(PBYTE)pat != (BYTE)'\?') ? 2 : 1;
            if (!*pat) {
                return firstMatch;
            }
            pat++;
            if (!*pat) {
                return firstMatch;
            }
        }
        else if (firstMatch) {
            pCur = firstMatch;
            pat = reinterpret_cast<const unsigned char*>(pattern);
            firstMatch = 0;
        }
    }
    return NULL;      
}

SIZE_T Utility::GetModuleSize(HMODULE module)
{
    MODULEINFO miModInfo;
    if (!GetModuleInformation(GetCurrentProcess(), module, &miModInfo, sizeof(MODULEINFO))) {
        return 0;
    }
    return miModInfo.SizeOfImage;
}




