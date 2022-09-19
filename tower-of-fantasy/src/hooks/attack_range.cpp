#include "hooking.hpp"
#include "class/vector.hpp"

namespace big
{
	__int64 __fastcall hooks::attack_range(__int64 a1, __int64 a2, __int64 a3)
	{
		*(__m128*)(a3 + 0x13C) = { 300.f, 300.f, 300.f, 300.f };

		//return g_hooking->m_attack_range_hook.get_original<decltype(&attack_range)>()(a1, a2, a3);
	}
}