#include "hooking.hpp"
#include <script_mgr.hpp>

namespace big
{
	uintptr_t* hooks::task_queue(uintptr_t* this_, int8_t a2)
	{
		if (g_running)
		{
			g_logger->info("function is running");
			g_script_mgr.tick();
		}

		return g_hooking->m_task_queue_hook.get_original<decltype(&task_queue)>()(this_, a2);
	}
}