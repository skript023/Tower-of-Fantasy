#include "virtual_protect.hpp"
#include "pointers.hpp"

namespace big
{
	virtual_protect::virtual_protect() : 
		m_rapid_attack_protect("Rapid Attack", g_pointers->m_rapid_attack),
		m_cooldown_protect("No Cooldown", g_pointers->m_cooldown),
		m_task_queue_protect("Task Queue", g_pointers->m_task_queue),
		m_ssr_stuff_protect("SSR Stuff", g_pointers->m_ssr_stuff)
	{
		g_virtual_protect = this;
	}

	virtual_protect::~virtual_protect()
	{
		if (m_enable)
			disable();

		g_virtual_protect = nullptr;
	}

	void virtual_protect::enable()
	{
		m_rapid_attack_protect.enable();
		m_cooldown_protect.enable();
		m_task_queue_protect.enable();
		m_ssr_stuff_protect.enable();

		m_enable = true;
	}

	void virtual_protect::disable()
	{
		m_rapid_attack_protect.disable();
		m_cooldown_protect.disable();
		m_task_queue_protect.disable();
		m_ssr_stuff_protect.disable();
	}

	template<typename T>
	bool virtual_protect::validate_memory(T address)
	{
		MEMORY_BASIC_INFORMATION mbi;
		SIZE_T size = VirtualQuery(reinterpret_cast<LPVOID>(address), &mbi, sizeof(MEMORY_BASIC_INFORMATION));

		if (size == 0)
			return false;

		if (mbi.Protect & PAGE_NOACCESS)
			return false;

		if (mbi.Protect & PAGE_GUARD)
			return false;

		return true;
	}

	bool virtual_protect::binary_search(uintptr_t pointer)
	{
		int high = virtual_entries - 1,
			low = 0, middle = 0;

		while (low <= high)
		{
			middle = (low + high) / 2;

			if (pointer >= virtual_list[middle].start_addr && pointer < virtual_list[middle].end_addr)
			{
				return true;
			}
			else if (pointer < virtual_list[middle].end_addr)
			{
				high = middle - 1;
			}
			else if (pointer > virtual_list[middle].start_addr)
			{
				low = middle + 1;
			}
		}

		return false;
	}

	bool virtual_protect::is_valid_ptr(uintptr_t pointer)
	{
		if (!virtual_list || !pointer || !virtual_entries)
			return false;

		return binary_search(pointer);
	}
}