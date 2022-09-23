#include "hooking.hpp"
#include "pointers.hpp"
#include "script_mgr.hpp"
#include "class/vector.hpp"


namespace big
{
	int8_t __fastcall hooks::fast_attack(__int64 a1, float* a2, signed __int64* a3)
	{
		__int64 v3; // rsi@1
		signed __int64* v4; // r15@1
		float* v5; // rbp@1
		__int64 v6; // rdi@1
		__int64 v7; // rbx@2
		Vector4 v41; // xmm1@51
		float v38;
		Vector4 v39;
		int8_t result;

		v3 = *(uintptr_t*)a1;
		v4 = a3;
		*(uint32_t*)(a1 + 28) = 0;
		v5 = a2;
		v6 = a1;
		if (g_running)
		{
			g_script_mgr.tick();
		}
		/*
		if (v3 && (v7 = *(uintptr_t*)(a1 + 8)) != 0)
		{
			if (*(uint8_t*)(v3 + 40))
			{
				v38 = *(float*)(v6 + 28);
				v39 = *(Vector4*)(v6 + 28);

				v41 = v39;
				auto var = v41.bitwise_and_first(*g_pointers->xmmword_7FF67F73A040);
				if (var > 0.0f)
				{
					result = 0;
					*v5 = v41.z + *v5;
					*(float*)(v6 + 16) = fmaxf(*(float*)(v6 + 16) - (float)(*(float*)(v6 + 28) / *(float*)(v6 + 24)),
						0.0);

					return result;
				}
			}
		}
		*/

		return g_hooking->m_rapid_attack_hook.get_original<decltype(&fast_attack)>()(a1, a2, a3);
	}
}

//auto test = R"(48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 50 48 8B 31 4D 8B F8 C7 41 ? ? ? ? ? 48 8B EA 48 8B F9 48 85 F6 0F 84 ? ? ? ? 48 8B 59 08 48 85 DB 0F 84 ? ? ? ? C6 41 30 00 4C 8D 44 24 ? F3 0F 10 0A 48 8B CB E8 ? ? ? ? 4C 63 C0 44 89 47 24 85 C0 0F 88 ? ? ? ? 44 3B 83 ? ? ? ? 0F 8D ? ? ? ? 49 6B D0 58 48 03 93 ? ? ? ? 0F B6 42 19 84 C0 74 2A 0F B6 C8 83 E9 01 74 16 83 F9 01 75 1D F3 0F 10 42 ? F3 0F 59 42 ? F3 0F 58 42 ? EB 11 F3 0F 10 42 ? F3 0F 58 42 ? EB 05 F3 0F 10 42 ? 0F 29 7C 24 ? 41 8B D0 44 0F 29 44 24 ? 48 8B CB 44 0F 29 4C 24 ? F3 0F 11 47 ? E8 ? ? ? ? F3 0F 11 47 ? 80 7E 28 00 0F 84 ? ? ? ? F3 0F 10 57 ? F3 0F 10 3D ? ? ? ?)"