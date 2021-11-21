#pragma once
#include <windows.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <locale>
#include <chrono>
#include <memory>
#include <string>
#include <stdexcept>
                   

class Utility
{
public:   
    template<typename ... Args>
    static std::string string_format(const std::string& format, Args ... args)
    {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args... ) + 1; // Extra space for '\0'
        if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
        auto size = static_cast<size_t>(size_s);
        auto buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }

    static std::string GetTimeString(std::chrono::milliseconds ms);

    static int GetRandInt32(int min, int max);

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
        out.imbue(std::locale(""));
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
