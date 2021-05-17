#pragma once
#include <Windows.h>
#include <cstring>
#include <functional>
#include <memory>	  
#include "Offset.h"
	
// todo get rid of the identifier
/*
template <typename FuncType>
class TrampolineHook;

template <class Object, typename RetVal, typename ...Args>
class TrampolineHook<RetVal(Object::*)(Args...)>
{																  
public:
	TrampolineHook();
	TrampolineHook(byte* funcAddr, unsigned int trampLength);
	~TrampolineHook();


	void SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after = nullptr);
	bool Init();

	bool Hook();
	void Unhook();

private:
	byte* CreateTrampoline();
   
private:
	BYTE* m_source;
	BYTE* m_destination;
	unsigned int m_length;
	BYTE* m_gateway; 
	
	static int m_identifier;
	HookFunction< __COUNTER__ , RetVal(Object::*)(Args...)> m_hookedFn;
};

template <class Object, typename RetVal, typename ...Args>
inline TrampolineHook<RetVal(Object::*)(Args...)>::TrampolineHook()
{
	m_gateway = 0;
	m_destination = 0;
	m_source = 0;
}

template<class Object, typename RetVal, typename ... Args>
TrampolineHook<RetVal(Object::*)(Args...)>::TrampolineHook(byte* funcAddr, unsigned int trampLength)
{	  
	m_source = funcAddr;
	m_length = trampLength;
	Init();
}

template <class Object, typename RetVal, typename ... Args>
TrampolineHook<RetVal(Object::*)(Args...)>::~TrampolineHook()
{
	Unhook();
	// free trampoline memory
	VirtualFree(m_gateway, 0, MEM_RELEASE);
}

template<class Object, typename RetVal, typename ...Args>
inline void TrampolineHook<RetVal(Object::*)(Args...)>::SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after)
{
	m_hookedFn.SetCallback(before, after);
}

template<class Object, typename RetVal, typename ...Args>
inline bool TrampolineHook<RetVal(Object::*)(Args...)>::Init()
{  	
	m_destination = m_hookedFn.GetAddress();
	m_gateway = (BYTE*)CreateTrampoline();
	if (m_gateway)
	{
		m_hookedFn.SetOriginal(m_gateway);
		return true;
	}	 		
	else 
	{
		return false;
	}
}

template <class Object, typename RetVal, typename ... Args>
bool TrampolineHook<RetVal(Object::*)(Args...)>::Hook()
{
	if (!m_gateway || !m_source || m_length < 5)
		return false;

	DWORD oProc;
	if (VirtualProtect(m_source, m_length, PAGE_EXECUTE_READWRITE, &oProc))
	{
		memset(m_source, 0x90, m_length);
		uintptr_t relAddy = (uintptr_t)(m_destination - m_source - 5);
		*m_source = (char)0xE9;
		*(uintptr_t*)(m_source + 1) = (uintptr_t)relAddy;
		if (VirtualProtect(m_source, m_length, oProc, &oProc))
		{
			return true;
		}
	}
	return false;
}

template <class Object, typename RetVal, typename ... Args>
void TrampolineHook<RetVal(Object::*)(Args...)>::Unhook()
{
	if (!m_gateway || !m_source || m_length < 5)
		return;

	DWORD oProc;
	if (VirtualProtect(m_source, m_length, PAGE_EXECUTE_READWRITE, &oProc))
	{
		std::memcpy(m_source, m_gateway, m_length);
		VirtualProtect(m_source, m_length, oProc, &oProc);
	}
} 

template <class Object, typename RetVal, typename ... Args>
byte* TrampolineHook<RetVal(Object::*)(Args...)>::CreateTrampoline()
{
	if (m_gateway != nullptr) return 0;
	if (m_length < 5) return 0;

	byte* gateway = (BYTE*)VirtualAlloc(0, m_length + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (gateway)
	{
		std::memcpy(gateway, m_source, m_length);
		uintptr_t jumpAddy = (uintptr_t)(m_source - gateway - 5);
		*(gateway + m_length) = (char)0xE9;
		*(uintptr_t*)(gateway + m_length + 1) = jumpAddy;
		return gateway;
	}
	return 0;
}
														  
// specification for __stdcall , e.g. direct3d methods
template <typename RetVal, typename ...Args>
class TrampolineHook<RetVal(__stdcall*)(Args...)>
{
public:
	TrampolineHook();
	TrampolineHook(byte* funcAddr, unsigned int trampLength);
	~TrampolineHook();


	void SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after = nullptr);
	bool Init();

	bool Hook();
	void Unhook();

private:
	byte* CreateTrampoline();

private:
	BYTE* m_source;
	BYTE* m_destination;
	unsigned int m_length;
	BYTE* m_gateway;

	static int m_identifier;
	HookFunction< __COUNTER__, RetVal(__stdcall*)(Args...)> m_hookedFn;
};

template <typename RetVal, typename ...Args>
inline TrampolineHook<RetVal(__stdcall*)(Args...)>::TrampolineHook()
{
	m_gateway = 0;
	m_destination = 0;
	m_source = 0;
}

template<typename RetVal, typename ... Args>
TrampolineHook<RetVal(__stdcall*)(Args...)>::TrampolineHook(byte* funcAddr, unsigned int trampLength)
{
	m_source = funcAddr;
	m_length = trampLength;
	Init();
}

template <typename RetVal, typename ... Args>
TrampolineHook<RetVal(__stdcall*)(Args...)>::~TrampolineHook()
{
	Unhook();
	// free trampoline memory
	VirtualFree(m_gateway, 0, MEM_RELEASE);
}

template<typename RetVal, typename ...Args>
inline void TrampolineHook<RetVal(__stdcall*)(Args...)>::SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after)
{
	m_hookedFn.SetCallback(before, after);
}

template<typename RetVal, typename ...Args>
inline bool TrampolineHook<RetVal(__stdcall*)(Args...)>::Init()
{
	m_destination = m_hookedFn.GetAddress();
	m_gateway = (BYTE*)CreateTrampoline();
	if (m_gateway)
	{
		m_hookedFn.SetOriginal(m_gateway);
		return true;
	}
	else
	{
		return false;
	}
}

template <typename RetVal, typename ... Args>
bool TrampolineHook<RetVal(__stdcall*)(Args...)>::Hook()
{
	if (!m_gateway || !m_source || m_length < 5)
		return false;

	DWORD oProc;
	if (VirtualProtect(m_source, m_length, PAGE_EXECUTE_READWRITE, &oProc))
	{
		memset(m_source, 0x90, m_length);
		uintptr_t relAddy = (uintptr_t)(m_destination - m_source - 5);
		*m_source = (char)0xE9;
		*(uintptr_t*)(m_source + 1) = (uintptr_t)relAddy;
		if (VirtualProtect(m_source, m_length, oProc, &oProc))
		{
			return true;
		}
	}
	return false;
}

template <typename RetVal, typename ... Args>
void TrampolineHook<RetVal(__stdcall*)(Args...)>::Unhook()
{
	if (!m_gateway || !m_source || m_length < 5)
		return;

	DWORD oProc;
	if (VirtualProtect(m_source, m_length, PAGE_EXECUTE_READWRITE, &oProc))
	{
		std::memcpy(m_source, m_gateway, m_length);
		VirtualProtect(m_source, m_length, oProc, &oProc);
	}
}

template <typename RetVal, typename ... Args>
byte* TrampolineHook<RetVal(__stdcall*)(Args...)>::CreateTrampoline()
{
	if (m_gateway != nullptr) return 0;
	if (m_length < 5) return 0;

	byte* gateway = (BYTE*)VirtualAlloc(0, m_length + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (gateway)
	{
		std::memcpy(gateway, m_source, m_length);
		uintptr_t jumpAddy = (uintptr_t)(m_source - gateway - 5);
		*(gateway + m_length) = (char)0xE9;
		*(uintptr_t*)(gateway + m_length + 1) = jumpAddy;
		return gateway;
	}
	return 0;
}



// __thiscall specification
template <typename RetVal, typename Object, typename ...Args>
class TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>
{
public:
	TrampolineHook();
	TrampolineHook(byte* funcAddr, unsigned int trampLength);
	~TrampolineHook();


	void SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after = nullptr);
	bool Init();

	bool Hook();
	void Unhook();

private:
	byte* CreateTrampoline();

private:
	BYTE* m_source;
	BYTE* m_destination;
	unsigned int m_length;
	BYTE* m_gateway;

	static int m_identifier;
	HookFunction< __COUNTER__, RetVal(__thiscall*)(Args...)> m_hookedFn;
};

template <typename RetVal, typename Object, typename ...Args>
inline TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>::TrampolineHook()
{
	m_gateway = 0;
	m_destination = 0;
	m_source = 0;
}

template<typename RetVal, typename Object, typename ... Args>
TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>::TrampolineHook(byte* funcAddr, unsigned int trampLength)
{
	m_source = funcAddr;
	m_length = trampLength;
	Init();
}

template <typename RetVal, typename Object, typename ... Args>
TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>::~TrampolineHook()
{
	Unhook();
	// free trampoline memory
	VirtualFree(m_gateway, 0, MEM_RELEASE);
}

template<typename RetVal, typename Object, typename ...Args>
inline void TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>::SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after)
{
	m_hookedFn.SetCallback(before, after);
}

template<typename RetVal, typename Object, typename ...Args>
inline bool TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>::Init()
{
	m_destination = m_hookedFn.GetAddress();
	m_gateway = (BYTE*)CreateTrampoline();
	if (m_gateway)
	{
		m_hookedFn.SetOriginal(m_gateway);
		return true;
	}
	else
	{
		return false;
	}
}

template <typename RetVal, typename Object, typename ... Args>
bool TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>::Hook()
{
	if (!m_gateway || !m_source || m_length < 5)
		return false;

	DWORD oProc;
	if (VirtualProtect(m_source, m_length, PAGE_EXECUTE_READWRITE, &oProc))
	{
		memset(m_source, 0x90, m_length);
		uintptr_t relAddy = (uintptr_t)(m_destination - m_source - 5);
		*m_source = (char)0xE9;
		*(uintptr_t*)(m_source + 1) = (uintptr_t)relAddy;
		if (VirtualProtect(m_source, m_length, oProc, &oProc))
		{
			return true;
		}
	}
	return false;
}

template <typename RetVal, typename Object, typename ... Args>
void TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>::Unhook()
{
	if (!m_gateway || !m_source || m_length < 5)
		return;

	DWORD oProc;
	if (VirtualProtect(m_source, m_length, PAGE_EXECUTE_READWRITE, &oProc))
	{
		std::memcpy(m_source, m_gateway, m_length);
		VirtualProtect(m_source, m_length, oProc, &oProc);
	}
}

template <typename RetVal, typename Object, typename ... Args>
byte* TrampolineHook<RetVal(__thiscall*)(Object*, Args...)>::CreateTrampoline()
{
	if (m_gateway != nullptr) return 0;
	if (m_length < 5) return 0;

	byte* gateway = (BYTE*)VirtualAlloc(0, m_length + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (gateway)
	{
		std::memcpy(gateway, m_source, m_length);
		uintptr_t jumpAddy = (uintptr_t)(m_source - gateway - 5);
		*(gateway + m_length) = (char)0xE9;
		*(uintptr_t*)(gateway + m_length + 1) = jumpAddy;
		return gateway;
	}
	return 0;
}
*/

template <typename FuncType>
class TrampolineHook
{
public:
	TrampolineHook();
	TrampolineHook(byte* funcAddr, byte* destination, unsigned int trampLength);
	~TrampolineHook();	

	bool Init();

	FuncType GetOriginal();
	bool Hook();
	void Unhook();

private:
	byte* CreateTrampoline();

private:
	BYTE* m_source;
	BYTE* m_destination;
	unsigned int m_length;
	BYTE* m_gateway;
};

template <typename FuncType>
inline TrampolineHook<FuncType>::TrampolineHook()
{
	m_gateway = 0;
	m_destination = 0;
	m_source = 0;
}

template<typename FuncType>
TrampolineHook<FuncType>::TrampolineHook(byte* funcAddr, byte* destination, unsigned int trampLength)
{
	m_destination = destination;
	m_source = funcAddr;
	m_length = trampLength;
	Init();
}

template<typename FuncType>
TrampolineHook<FuncType>::~TrampolineHook()
{
	Unhook();
	// free trampoline memory
	VirtualFree(m_gateway, 0, MEM_RELEASE);
}
	  
template<typename FuncType>
inline bool TrampolineHook<FuncType>::Init()
{
	m_gateway = (BYTE*)CreateTrampoline();
	return (m_gateway != nullptr);
}

template<typename FuncType>
inline FuncType TrampolineHook<FuncType>::GetOriginal()
{
	return reinterpret_cast<FuncType>(m_gateway);
}

template<typename FuncType>
bool TrampolineHook<FuncType>::Hook()
{
	if (!m_gateway || !m_source || m_length < 5)
		return false;

	DWORD oProc;
	if (VirtualProtect(m_source, m_length, PAGE_EXECUTE_READWRITE, &oProc))
	{
		memset(m_source, 0x90, m_length);
		uintptr_t relAddy = (uintptr_t)(m_destination - m_source - 5);
		*m_source = (char)0xE9;
		*(uintptr_t*)(m_source + 1) = (uintptr_t)relAddy;
		if (VirtualProtect(m_source, m_length, oProc, &oProc))
		{
			return true;
		}
	}
	return false;
}

template<typename FuncType>
void TrampolineHook<FuncType>::Unhook()
{
	if (!m_gateway || !m_source || m_length < 5)
		return;

	DWORD oProc;
	if (VirtualProtect(m_source, m_length, PAGE_EXECUTE_READWRITE, &oProc))
	{
		std::memcpy(m_source, m_gateway, m_length);
		VirtualProtect(m_source, m_length, oProc, &oProc);
	}
}

template<typename FuncType>
byte* TrampolineHook<FuncType>::CreateTrampoline()
{
	if (m_gateway != nullptr) return 0;
	if (m_length < 5) return 0;

	byte* gateway = (BYTE*)VirtualAlloc(0, m_length + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (gateway)
	{
		std::memcpy(gateway, m_source, m_length);
		uintptr_t jumpAddy = (uintptr_t)(m_source - gateway - 5);
		*(gateway + m_length) = (char)0xE9;
		*(uintptr_t*)(gateway + m_length + 1) = jumpAddy;
		return gateway;
	}
	return 0;
}