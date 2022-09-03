#pragma once
#include "common.hpp"

namespace big
{
	class protected_memory
	{
	public:
		explicit protected_memory(std::string name, void* target);
		~protected_memory() noexcept = default;

		protected_memory(protected_memory&& that) = delete;
		protected_memory& operator=(protected_memory&& that) = delete;
		protected_memory(protected_memory const&) = delete;
		protected_memory& operator=(protected_memory const&) = delete;

		void enable();
		void disable();
		inline void read_raw(void* base, size_t size, void* out)
		{
			if (!::ReadProcessMemory(GetCurrentProcess(), (LPCVOID)base, out, size, nullptr))
			{
				throw std::exception("RPM failed");
			}
		}
		template <typename T>
		inline void read(uintptr_t base, T& ref)
		{
			read_raw(base, sizeof(T), &ref);
		}

		template <typename T>
		inline T read(uintptr_t base)
		{
			T out{};
			read_raw(base, sizeof(T), &out);
			return out;
		}
	private:
		std::string m_name;
		void* m_target;
		DWORD m_original{};
		DWORD m_disable_original{};
	};
}