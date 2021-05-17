#pragma once          
#include <functional>                        

template<int identifier, typename funcType>
class HookFunction;

   
// helper class for generic method hooks
template<int identifier, class Object, typename RetVal, typename ... Args>
class HookFunction<identifier, RetVal(Object::*)(Args...)>
{
public:
    using MethodType = RetVal(__fastcall*)(void* ecx, Args...);

    HookFunction();

    void SetOriginal(byte* originalFn);
    void SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after = nullptr);
    byte* GetAddress();
                                                                        
private:
    static RetVal __fastcall hkMethod(void* ecx, void* edx, Args... params);
    static HookFunction<identifier, RetVal(Object::*)(Args...)>* me;

    std::function<void(Args...)> m_callback_before;
    std::function<void(Args...)> m_callback_after;
    MethodType m_original;
};

template<int identifier, class Object, typename RetVal, typename ...Args>
HookFunction<identifier, RetVal(Object::*)(Args...)>* HookFunction<identifier, RetVal(Object::*)(Args...)>::me = nullptr;

template<int identifier, class Object, typename RetVal, typename ...Args>
inline HookFunction<identifier, RetVal(Object::*)(Args...)>::HookFunction()
{
    HookFunction<identifier, RetVal(Object::*)(Args...)>::me = this;
    m_callback_before = nullptr;
    m_callback_after = nullptr;
}

template<int identifier, class Object, typename RetVal, typename ...Args>
inline void HookFunction<identifier, RetVal(Object::*)(Args...)>::SetOriginal(byte* originalFn)
{
    m_original = reinterpret_cast<MethodType>(originalFn);
}

template<int identifier, class Object, typename RetVal, typename ...Args>
inline void HookFunction<identifier, RetVal(Object::*)(Args...)>::SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after)
{
    m_callback_before = before;
    m_callback_after = after;
}

template<int identifier, class Object, typename RetVal, typename ...Args>
inline byte* HookFunction<identifier, RetVal(Object::*)(Args...)>::GetAddress()
{
    return reinterpret_cast<byte*>(HookFunction<identifier, RetVal(Object::*)(Args...)>::hkMethod);
}

template<int identifier, class Object, typename RetVal, typename ...Args>
RetVal __fastcall HookFunction<identifier, RetVal(Object::*)(Args...)>::hkMethod(void* ecx, void* edx, Args ...params)
{       
   if (HookFunction<identifier, RetVal(Object::*)(Args...)>::me->m_callback_before)
    {
        __asm
        {
            pushad;
            pushf;
        }

        HookFunction<identifier, RetVal(Object::*)(Args...)>::me->m_callback_before(params...);

        __asm
        {
            popf;
            popad;
        }
    }    

    RetVal ret = HookFunction<identifier, RetVal(Object::*)(Args...)>::me->m_original(ecx, params...);

    if (HookFunction<identifier, RetVal(Object::*)(Args...)>::me->m_callback_after)
    {
        __asm
        {
            pushad;
            pushf;
        }

        HookFunction<identifier, RetVal(Object::*)(Args...)>::me->m_callback_after(params...);

        __asm
        {
            popf;
            popad;
        }
    }
    return ret;
}


// helper class for generic method hooks
template<int identifier, typename RetVal, typename ... Args>
class HookFunction<identifier, RetVal(__stdcall*)(Args...)>
{
public:
    using MethodType = RetVal(__stdcall*)(Args...);

    HookFunction();

    void SetOriginal(byte* originalFn);
    void SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after = nullptr);
    byte* GetAddress();

private:
    static RetVal __stdcall hkMethod(Args... params);
    static HookFunction<identifier, RetVal(__stdcall*)(Args...)>* me;

    std::function<void(Args...)> m_callback_before;
    std::function<void(Args...)> m_callback_after;
    MethodType m_original;
};

template<int identifier, typename RetVal, typename ...Args>
HookFunction<identifier, RetVal(__stdcall*)(Args...)>* HookFunction<identifier, RetVal(__stdcall*)(Args...)>::me = nullptr;

template<int identifier, typename RetVal, typename ...Args>
inline HookFunction<identifier, RetVal(__stdcall*)(Args...)>::HookFunction()
{
    HookFunction<identifier, RetVal(__stdcall*)(Args...)>::me = this;
    m_callback_before = nullptr;
    m_callback_after = nullptr;
}

template<int identifier, typename RetVal, typename ...Args>
inline void HookFunction<identifier, RetVal(__stdcall*)(Args...)>::SetOriginal(byte* originalFn)
{
    m_original = reinterpret_cast<MethodType>(originalFn);
}

template<int identifier, typename RetVal, typename ...Args>
inline void HookFunction<identifier, RetVal(__stdcall*)(Args...)>::SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after)
{
    m_callback_before = before;
    m_callback_after = after;
}

template<int identifier, typename RetVal, typename ...Args>
inline byte* HookFunction<identifier, RetVal(__stdcall*)(Args...)>::GetAddress()
{
    return reinterpret_cast<byte*>(HookFunction<identifier, RetVal(__stdcall*)(Args...)>::hkMethod);
}

template<int identifier, typename RetVal, typename ...Args>
RetVal __stdcall HookFunction<identifier, RetVal(__stdcall*)(Args...)>::hkMethod(Args ...params)
{
    if (HookFunction<identifier, RetVal(__stdcall*)(Args...)>::me->m_callback_before)
    {
        __asm
        {
            pushad;
            pushf;
        }

        HookFunction<identifier, RetVal(__stdcall*)(Args...)>::me->m_callback_before(params...);

        __asm
        {
            popf;
            popad;
        }
    }

    RetVal ret = HookFunction<identifier, RetVal(__stdcall*)(Args...)>::me->m_original(params...);

    if (HookFunction<identifier, RetVal(__stdcall*)(Args...)>::me->m_callback_after)
    {
        __asm
        {
            pushad;
            pushf;
        }

        HookFunction<identifier, RetVal(__stdcall*)(Args...)>::me->m_callback_after(params...);

        __asm
        {
            popf;
            popad;
        }
    }
    return ret;
}
          
// helper class for generic method hooks
template<int identifier, typename RetVal, typename ... Args>
class HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>
{
public:
    using MethodType = RetVal(__thiscall*)(void* ecx, Args...);

    HookFunction();

    void SetOriginal(byte* originalFn);
    void SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after = nullptr);
    byte* GetAddress();

private:
    static RetVal __fastcall hkMethod(void* ecx, void* edx, Args... params);
    static HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>* me;

    std::function<void(Args...)> m_callback_before;
    std::function<void(Args...)> m_callback_after;               
    MethodType m_original;
};

template<int identifier, typename RetVal, typename ...Args>
HookFunction<identifier, RetVal(__thiscall*)(void* ecx,  Args...)>* HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::me = nullptr;

template<int identifier, typename RetVal, typename ...Args>
inline HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::HookFunction()
{
    HookFunction<identifier, RetVal(__thiscall*)(Args...)>::me = this;
    m_callback_before = nullptr;
    m_callback_after = nullptr;
}

template<int identifier, typename RetVal, typename ...Args>
inline void HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::SetOriginal(byte* originalFn)
{
    m_original = reinterpret_cast<MethodType>(originalFn);
}

template<int identifier, typename RetVal, typename ...Args>
inline void HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::SetCallback(std::function<void(Args...)> before, std::function<void(Args...)> after)
{
    m_callback_before = before;
    m_callback_after = after;
}


template<int identifier, typename RetVal, typename ...Args>
inline byte* HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::GetAddress()
{
    return reinterpret_cast<byte*>(HookFunction<identifier, RetVal(__thiscall*)(Args...)>::hkMethod);
}

template<int identifier, typename RetVal, typename ...Args>
RetVal __fastcall HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::hkMethod(void* ecx, void* edx, Args ...params)
{
    if (HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::me->m_callback_before)
    {
        __asm
        {
            pushad;
            pushf;
        }

        HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::me->m_callback_before(params...);

        __asm
        {
            popf;
            popad;
        }
    }

    RetVal ret = HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::me->m_original(ecx, params...);

    if (HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::me->m_callback_after)
    {
        __asm
        {
            pushad;
            pushf;
        }

        HookFunction<identifier, RetVal(__thiscall*)(void* ecx, Args...)>::me->m_callback_after(params...);

        __asm
        {
            popf;
            popad;
        }
    }
    return ret;  
}