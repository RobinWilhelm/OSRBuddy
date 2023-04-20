#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <Ntstatus.h>
#include <random>
//#include <winternl.h>	 
#include <cmath>
#include <minwindef.h>
#include <memory>
#include <functional>
#include <fstream>
#include <unordered_map>

#include <Psapi.h>
#pragma comment( lib, "psapi.lib" )

#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9core.h>
#pragma comment(lib,"d3dx9.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_addition.h"
#include "imgui/imgui_notify.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "Httplib/Httplib.h"
#pragma comment(lib, "ws2_32.lib")

#include "nlohmann/json.hpp"

#include "Content.h"
#include "BuddyAPI.h"
#include "Console.h"
#include "BuddyTimer.h"
#include "OSRBuddy.h"
#include "OSRAPI.h"

#include "SDK/AtumApplication.h"
