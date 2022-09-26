#include "hooking.hpp"
#include "pointers.hpp"
#include "script_mgr.hpp"

namespace big
{
	__int64 __fastcall hooks::evasion_handler(EvadeBeanParam* a1)
	{
		if (g_running)
		{
			g_script_mgr.tick();

			if (g_settings->player.infinite_dodge)
			{
				EvadeBeanParam params{};
				params.m_rand_bean = 6001;
				params.m_cur_bean_count = 6641;
				params.m_change_time = 637963816908830000;

				return g_hooking->m_evasion_handler_hook.get_original<decltype(&evasion_handler)>()(&params);
			}
		}

		return g_hooking->m_evasion_handler_hook.get_original<decltype(&evasion_handler)>()(a1);
	}
}

//static const float v1 = (float)(a1->m_cur_bean_count - a1->m_cur_bean_count / 10);
//(__int64)(signed int)floor((float)(v1 * *(float*)g_pointers->dword_7FF681753804) - 3.0);