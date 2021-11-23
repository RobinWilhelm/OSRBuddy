#include "osrb_pch.h"
#include "Console.h"
#include <chrono>
#include <ctime>   
#include <iomanip>

Console::~Console()
{
	Free();
}

Console* Console::GetInstance()
{
	static Console con;
	return &con;
}

bool Console::Init()
{
	if (!AllocConsole()) {
		return false;
	}

	FILE* fDummy;
	if (!freopen_s(&fDummy, "CONIN$", "r", stdin) || !freopen_s(&fDummy, "CONOUT$", "w", stderr) || !freopen_s(&fDummy, "CONOUT$", "w", stdout)) {
		return false;
	}

	std::cout.clear();
	std::clog.clear();
	std::cerr.clear();
	std::cin.clear();

	HANDLE hConOut = CreateFile(("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hConIn = CreateFile(("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!SetStdHandle(STD_OUTPUT_HANDLE, hConOut) || !SetStdHandle(STD_ERROR_HANDLE, hConOut) || !SetStdHandle(STD_INPUT_HANDLE, hConIn)) {
		return false;
	}

	std::wcout.clear();
	std::wclog.clear();
	std::wcerr.clear();
	std::wcin.clear();

	return true;
}

void Console::Free()
{
	FreeConsole();
}

void Console::Log(std::string msg)
{  	
	std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm tinfo;
	localtime_s(&tinfo, &time);

	std::cout << std::put_time(&tinfo, "%T") << ":\t" << msg;
}
