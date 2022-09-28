#pragma once
#include "../unreal_engine_utility.hpp"

namespace big
{
	class AttackOption
	{
	public:
		inline int get_weapon_type()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return skill_component->m_weapon_type;
			}

			return 0;
		}

		inline void rapid_attack(bool activate)
		{
			if (activate)
			{
				switch (get_weapon_type())
				{
				case 2:
					if (*(uint8_t*)g_pointers->m_rapid_attack != 0xC0)
						*(uint8_t*)g_pointers->m_rapid_attack = 0xC0;
					break;
				case 3:
					if (*(uint8_t*)g_pointers->m_rapid_attack != 0xC3)
						*(uint8_t*)g_pointers->m_rapid_attack = 0xC3;
					break;
				}
			}
			else if (!activate && *(uint8_t*)g_pointers->m_rapid_attack != 0xC2)
			{
				*(uint8_t*)g_pointers->m_rapid_attack = 0xC2;
			}
		}

		inline void remove_cooldown(bool activate)
		{
			if (auto cooldown = *g_pointers->m_cooldown)
			{
				if (activate && cooldown == 0x74)
				{
					*(int8_t*)g_pointers->m_cooldown = 0x75;
				}
				else if (!activate && cooldown == 0x75)
				{
					*(int8_t*)g_pointers->m_cooldown = 0x74;
				}
			}
		}

		inline float* pysical_attack()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return &skill_component->m_pysical_attack;
			}

			return nullptr;
		}

		inline float* fire_attack()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return &skill_component->m_fire_attack;
			}

			return nullptr;
		}

		inline float* thunder_attack()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return &skill_component->m_thunder_attack;
			}

			return nullptr;
		}

		inline float* ice_attack()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return &skill_component->m_ice_attack;
			}

			return nullptr;
		}

		inline float* super_power_attack()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return &skill_component->m_super_power_atk;
			}

			return nullptr;
		}

		inline float* critical_attack()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return &skill_component->m_critical;
			}

			return nullptr;
		}

		inline float* critical_damage()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return &skill_component->m_critical_damage;
			}

			return nullptr;
		}

		inline float* critical_rate()
		{
			if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
			{
				return &skill_component->m_critical_rate;
			}

			return nullptr;
		}

		inline float* attack_multiplier()
		{
			if (auto player = unreal_engine::get_local_player())
			{
				return &player->m_player_controller->m_pawn->m_attribute_set->m_attack;
			}

			return nullptr;
		}

		inline float* critical_multiplier()
		{
			if (auto player = unreal_engine::get_local_player())
			{
				return &player->m_player_controller->m_pawn->m_attribute_set->m_critical_base;
			}

			return nullptr;
		}

		inline void critical_hack(bool activate)
		{
			if (activate)
			{
				if (auto self = unreal_engine::get_pawn(); self)
				{
					if (auto skill_component = self->m_skill_component; skill_component)
					{
						skill_component->m_critical_rate = 100.f;
						skill_component->m_critical_damage += 25.f;
					}
				}
			}
		}
	};
}