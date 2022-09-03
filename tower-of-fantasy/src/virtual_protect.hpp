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

		template<typename T>
		bool validate_memory(T address);
		bool binary_search(uintptr_t pointer);
		bool is_valid_ptr(uintptr_t pointer);
	private:
		bool m_enable{};
		protected_memory m_rapid_attack_protect;
		protected_memory m_cooldown_protect;
		protected_memory m_task_queue_protect;

		struct _VIRTUAL_LIST
		{
			uintptr_t start_addr;
			uintptr_t end_addr;
		};

		_VIRTUAL_LIST* virtual_list;
		int32_t virtual_entries;
	};

	inline virtual_protect* g_virtual_protect;
}