#include "hooking.hpp"
#include "pointers.hpp"
#include "script_mgr.hpp"
#include "class/vector.hpp"


namespace big
{
	int8_t __fastcall hooks::fast_attack(__int64 a1, float* a2, signed __int64* a3)
	{
		if (g_running)
		{
			g_script_mgr.tick();
		}
		return g_hooking->m_rapid_attack_hook.get_original<decltype(&fast_attack)>()(a1, a2, a3);
	}
}

