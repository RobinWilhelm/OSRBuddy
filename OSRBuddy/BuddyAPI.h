#pragma once
#include "Content.h"

#ifdef OSRBUDDY_MANUALMAP

#ifdef BUDDY_EXPORTS
#define BUDDY_API __declspec(dllexport)
#else
#define BUDDY_API __declspec(dllimport)
#endif

struct MapEntryInfo
{
    DWORD entrypoint;
    DWORD imagebase;
    DWORD imagesize;
};


extern "C" BUDDY_API bool ManualEntry(LPVOID lpThreadParameter);
extern "C" BUDDY_API MapEntryInfo mapinfo;

#endif