#pragma once
#include "../unreal_engine_utility.hpp"
#include "script.hpp"

namespace big
{
	class MovementOption
	{
	public:
		inline void no_clip(bool activate)
		{
			if (auto player = unreal_engine::get_local_player())
			{
				if (activate)
				{
					player->m_player_controller->m_acknowledge_pawn->m_is_actor_enable_collision = 0x40;
				}
				else
				{
					player->m_player_controller->m_acknowledge_pawn->m_is_actor_enable_collision = 0x44;
				}
			}
		}

		inline void infinite_dodge(bool activate)
		{
			if (activate)
			{
				if (GetAsyncKeyState(VK_LSHIFT) & 0x1)
				{
					if (auto player = unreal_engine::get_local_player())
					{
						if (auto controller = player->m_player_controller)
						{
							if (auto pawn = controller->m_pawn)
							{
								pawn->m_evade_bean.m_rand_bean = 6001;
								pawn->m_evade_bean.m_cur_bean_count = 6641;
								pawn->m_evade_bean.m_change_time = 637963816908830000;
							}
						}
					}
				}
			}
		}

		inline Vector3* get_entity_coords()
		{
			if (auto pawn = unreal_engine::get_pawn())
			{
				if (auto self = pawn->m_capsule_component)
				{
					return &self->m_position;
				}
			}

			return nullptr;
		}

		inline void teleport_forward()
		{
			THREAD_POOL_BEGIN()
			{
				if (auto self = unreal_engine::get_hotta_character(); self)
				{
					constexpr auto forward = 1000.f;
					auto pos = self->m_capsule_component->m_position;
					auto rot = self->m_capsule_component->m_rotation;

					pos.x += forward * sin(unreal_engine::degree_to_radian(rot.yaw)) * -1.500f;
					pos.y += forward * cos(unreal_engine::degree_to_radian(rot.yaw));

					self->server_teleport_to(pos, rot);
					self->client_teleport_to(pos, rot);
				}
			} THREAD_POOL_END
		}

		inline void teleport_to(Vector3 coords)
		{
			QUEUE_JOB_BEGIN_CLAUSE(coords)
			{
				if (auto self = unreal_engine::get_hotta_character(); self)
				{
					self->server_teleport_to(coords, self->m_capsule_component->m_rotation);
					self->client_teleport_to(coords, self->m_capsule_component->m_rotation);
				}
			} QUEUE_JOB_END_CLAUSE
		}

		inline void teleport_with_loading(Vector3 coords)
		{
			QUEUE_JOB_BEGIN_CLAUSE(coords)
			{
				if (auto self = unreal_engine::get_hotta_character(); self)
				{
					self->server_teleport_with_loading(coords, self->m_capsule_component->m_rotation);
					self->teleport_with_loading(coords, self->m_capsule_component->m_rotation);
					self->client_teleport_with_loading(coords, self->m_capsule_component->m_rotation);
				}
			} QUEUE_JOB_END_CLAUSE
		}

		inline float* player_movement_speed()
		{
			if (auto player = unreal_engine::get_local_player())
				return &player->m_player_controller->m_pawn->m_chara_movement->m_movement_speed;

			return nullptr;
		}

		inline float* player_crouch_speed()
		{
			if (auto player = unreal_engine::get_local_player())
				return &player->m_player_controller->m_pawn->m_chara_movement->m_crouch_speed;

			return nullptr;
		}

		inline float* player_swim_speed()
		{
			if (auto player = unreal_engine::get_local_player())
				return &player->m_player_controller->m_pawn->m_max_swim_speed;

			return nullptr;
		}

		inline float* player_fly_speed()
		{
			if (auto player = unreal_engine::get_local_player())
				return &player->m_player_controller->m_pawn->m_chara_movement->m_fly_speed;

			return nullptr;
		}

		inline float* player_gravity()
		{
			if (auto player = unreal_engine::get_local_player())
				return &player->m_player_controller->m_pawn->m_gravity;

			return nullptr;
		}

		inline void infinite_jump(bool activate)
		{
			if (activate)
			{
				if (GetAsyncKeyState(VK_SPACE) & 0x1)
				{
					if (auto player = unreal_engine::get_local_player())
					{
						if (auto controller = player->m_player_controller)
						{
							if (auto actor_pawn = controller->m_pawn)
							{
								actor_pawn->m_jump_count = 0;
							}
						}
					}
				}
			}
		}

		inline bool is_crouch()
		{
			if (auto player = unreal_engine::get_local_player())
				return player->m_player_controller->m_pawn->m_is_crouch;

			return false;
		}

		inline bool is_armor_broken()
		{
			if (auto player = unreal_engine::get_local_player())
				return player->m_player_controller->m_pawn->m_is_armor_break;

			return false;
		}

		inline float* game_speed()
		{
			if (auto player = unreal_engine::get_local_player())
			{
				return &player->m_player_controller->m_pawn->m_game_speed;
			}

			return nullptr;
		}

		inline void freeze_mobs(bool activate)
		{
			if (auto player = unreal_engine::get_local_player())
			{
				player->m_player_controller->m_pawn->m_cant_be_Selected = activate;
			}
		}

		inline void freeze_entity(bool activate)
		{
			if (auto player = unreal_engine::get_local_player())
			{
				if (activate)
				{
					player->m_player_controller->m_pawn->m_chara_movement->m_freeze_entity = false;
				}
				else
				{
					player->m_player_controller->m_pawn->m_chara_movement->m_freeze_entity = true;
				}
			}
		}
	};
}