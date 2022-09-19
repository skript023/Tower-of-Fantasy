#include "hooking.hpp"
#include "pointers.hpp"
#include <dos.h>

namespace big
{
	__int64 __fastcall hooks::evasion_handler(EvadeBeanParam* a1)
	{
        static const float v1 = (float)(a1->m_cur_bean_count - a1->m_cur_bean_count / 10);

		if (g_settings->player.infinite_dodge)
		{
			if (GetAsyncKeyState(VK_LSHIFT) & 0x1)
			{
				return (__int64)(signed int)floor((float)(v1 * *(float*)g_pointers->dword_7FF681753804) - 3.0);
			}
		}

		return g_hooking->m_evasion_handler_hook.get_original<decltype(&evasion_handler)>()(a1);
	}
}

