#pragma once
#include "../unreal_engine_utility.hpp"

namespace big::defense
{
	inline void godmode(bool activate)
	{
		if (auto player = unreal_engine::get_local_player())
		{
			uint8_t godmode_status = player->m_player_controller->m_pawn->m_godmode;
			if (activate && godmode_status == 141)
			{
				player->m_player_controller->m_pawn->m_godmode = 13;
			}
			else if (activate && godmode_status == 13)
			{
				player->m_player_controller->m_pawn->m_godmode = 141;
			}
		}
	}

	inline void remove_fall_damage(bool activate)
	{
		if (auto player = unreal_engine::get_local_player())
		{
			bool is_enable = player->m_player_controller->m_pawn->m_fall_damage;

			if (activate && is_enable)
				player->m_player_controller->m_pawn->m_fall_damage = false;
			else if (!activate && !is_enable)
				player->m_player_controller->m_pawn->m_fall_damage = true;
		}
	}

	inline float* max_health()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_max_health;
		}

		return nullptr;
	}

	inline float* max_energy()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_max_energy;
		}

		return nullptr;
	}

	inline float* energy_recover_multiplier()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_energy_recovery;
		}

		return nullptr;
	}

	inline float* health()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_health;
		}

		return nullptr;
	}

	inline float* pysical_defense()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_pysical_deff;
		}

		return nullptr;
	}

	inline float* fire_defense()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_fire_deff;
		}

		return nullptr;
	}

	inline float* thunder_defense()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_thunder_deff;
		}

		return nullptr;
	}

	inline float* ice_defense()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_ice_deff;
		}

		return nullptr;
	}

	inline float* super_power_defense()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_super_power_deff;
		}

		return nullptr;
	}

	inline float* crit_defense()
	{
		if (auto skill_component = unreal_engine::get_local_player()->m_player_controller->m_pawn->m_skill_component)
		{
			return &skill_component->m_critical_deff;
		}

		return nullptr;
	}
}