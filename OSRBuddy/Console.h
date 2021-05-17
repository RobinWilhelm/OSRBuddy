#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#ifdef _DEBUG
	#define DEBUG_LOG(x)(Console::GetInstance()->Log(x);)
#else
	#define DEBUG_LOG(x)()
#endif // _DEBUG



class Console
{
public:
	~Console();

	static Console* GetInstance();
	bool Init();
	void Free();
	void Log(std::string msg);
};