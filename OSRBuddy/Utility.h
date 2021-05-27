#pragma once
#include <windows.h>
#include <string>
#include <iomanip>
#include <sstream>



class Utility
{
public:
    static HWND FindWindowFromProcessId(DWORD dwProcessId);
          
    // from learn_more https://github.com/learn-more/findpattern-bench/blob/master/patterns/learn_more.h
    static PBYTE FindPattern(const PBYTE rangeStart, const PBYTE rangeEnd, const char* pattern);

    static SIZE_T GetModuleSize(HMODULE module);

    // IDA style pattern
    static PBYTE FindPatternEasy(std::string moduleName, std::string pattern);
    
    template< typename T >
    static std::string int_to_hexstring(T i)
    {
        std::stringstream stream;
        stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
        return stream.str();
    }

    template <typename T>
    static std::string to_string_with_precision(const T a_value, const int n = 6)
    {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << a_value;
        return out.str();
    } 

    static FORCEINLINE void PushCpuState()
    {  
        __asm
        {
            pushad;
            pushf;
        } 
    }


    static FORCEINLINE void PopCpuState()
    {
        __asm
        {
            popf;
            popad;
        }
    }

    static void MoveMouse(uint32_t x, uint32_t y);
};

#ifdef RELEASE
    #define PUSHCPUSTATE Utility::PushCpuState();
    #define POPCPUSTATE Utility::PopCpuState();
#else
    #define PUSHCPUSTATE
    #define POPCPUSTATE
#endif



