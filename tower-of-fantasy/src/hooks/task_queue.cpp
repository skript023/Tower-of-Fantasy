#include "hooking.hpp"
#include <script_mgr.hpp>

namespace big
{
	__int64 hooks::task_queue(int* a1, __int64 a2, char a3, __int64 a4)
	{
		if (g_running)
		{
			g_logger->info("function is running");
			g_script_mgr.tick();
		}

		return g_hooking->m_task_queue_hook.get_original<decltype(&task_queue)>()(a1, a2, a3, a4);
	}
}