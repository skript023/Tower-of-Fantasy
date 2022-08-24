#pragma once
#include "common.hpp"
#include "memory/protected_memory.hpp"

namespace big
{
	class virtual_protect
	{
	public:
		explicit virtual_protect();
		~virtual_protect();

		void enable();
		void disable();

	private:
		bool m_enable{};
		protected_memory m_rapid_attack_protect;
		protected_memory m_cooldown_protect;
	};

	inline virtual_protect* g_virtual_protect;
}