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
	private:
		std::string m_name;
		void* m_target;
		DWORD m_original{};
		DWORD m_disable_original{};
	};
}