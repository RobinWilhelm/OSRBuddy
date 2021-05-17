#pragma once
#include <Windows.h>
#include <assert.h> 
#include <cstdint>
#include <stdexcept>

/*Creds go to MarkHc*/

namespace detail
{
	class protect_guard
	{
	public:
		protect_guard(void* base, size_t len, std::uint32_t flags)
		{
			_base = base;
			_length = len;
			if (!VirtualProtect(base, len, flags, (PDWORD)&_old))
				throw std::runtime_error("Failed to protect region.");
		}
		~protect_guard()
		{
			VirtualProtect(_base, _length, _old, (PDWORD)&_old);
		}

	private:
		void* _base;
		size_t        _length;
		std::uint32_t _old;
	};
}

template <class basetype>
class VMTHook
{
public:
	VMTHook()
		: class_base(nullptr), vftbl_len(0), new_vftbl(nullptr), old_vftbl(nullptr)
	{
	}
	VMTHook(basetype* base)
		: class_base(base), vftbl_len(0), new_vftbl(nullptr), old_vftbl(nullptr)
	{
	}
	~VMTHook()
	{
		unhook_all();

		delete[] new_vftbl;
	}

	bool setupvmt(basetype* base /*= nullptr*/)
	{
		if (base != nullptr)
			class_base = base;

		if (class_base == nullptr)
			return false;

		old_vftbl = *(std::uintptr_t**)class_base;
		vftbl_len = estimate_vftbl_length(old_vftbl);

		if (vftbl_len == 0)
			return false;

		new_vftbl = new std::uintptr_t[vftbl_len]();

		std::memcpy(new_vftbl, old_vftbl, vftbl_len * sizeof(std::uintptr_t));

		try {
			auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
			*(std::uintptr_t**)class_base = new_vftbl;
		}
		catch (...) {
			delete[] new_vftbl;
			return false;
		}

		return true;
	}

	template<typename T>
	void hook_index(int index, T fun)
	{
		assert(index >= 0 && index < (int)vftbl_len);
		new_vftbl[index] = reinterpret_cast<std::uintptr_t>(fun);
	}
	void unhook_index(int index)
	{
		new_vftbl[index] = old_vftbl[index];
	}
	void unhook_all()
	{
		try {
			if (old_vftbl != nullptr) {
				auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
				*(std::uintptr_t**)class_base = old_vftbl;
				old_vftbl = nullptr;
			}
		}
		catch (...) {
		}
	}

	template<typename T>
	T get_original(int index)
	{
		return (T)old_vftbl[index];
	}

protected:
	static inline std::size_t estimate_vftbl_length(std::uintptr_t* vftbl_start)
	{
		auto len = std::size_t{};

		while (vftbl_start[len] >= 0x00010000 &&
			vftbl_start[len] < 0xFFF00000 &&
			len < 512 /* Hard coded value. Can cause problems, beware.*/) {
			len++;
		}

		return len;
	}

private:
	basetype* class_base;
	std::size_t     vftbl_len;
	std::uintptr_t* new_vftbl;
	std::uintptr_t* old_vftbl;
};