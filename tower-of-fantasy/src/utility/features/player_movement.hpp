#pragma once
#include "script.hpp"
#include "../unreal_engine_utility.hpp"
#include "../services/all.hpp"
#include "../ecryption.h"

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

		inline Rotator* get_entity_rotation()
		{
			if (auto pawn = unreal_engine::get_pawn())
			{
				if (auto self = pawn->m_capsule_component)
				{
					return &self->m_rotation;
				}
			}

			return nullptr;
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
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				if (auto self = unreal_engine::get_hotta_character(); self)
				{
					constexpr auto forward = 500.f;
					auto pos = self->m_capsule_component->m_position;
					auto rot = self->m_capsule_component->m_rotation;

					pos.x += forward * sin(unreal_engine::degree_to_radian(rot.yaw)) * -1.500f;
					pos.y += -forward * cos(unreal_engine::degree_to_radian(rot.yaw)) * 1.500f;
					pos.z -= 390.f;

					self->client_teleport_to(pos, rot);
					self->server_teleport_to(pos, rot);
				}
			} QUEUE_JOB_END_CLAUSE
		}

		inline void teleport_to(Vector3 coords)
		{
			QUEUE_JOB_BEGIN_CLAUSE(coords)
			{
				if (auto self = unreal_engine::get_hotta_character(); self)
				{
					self->client_teleport_to(coords, self->m_capsule_component->m_rotation);
					self->server_teleport_to(coords, self->m_capsule_component->m_rotation);
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

		inline void teleport_to_entity(const char* entityName, bool distanceCheck)
		{
			g_fiber_pool->queue_job([=]
			{
				for (auto level : (*g_pointers->m_world)->m_level)
				{
					if (!level) continue;
					for (auto actor : level->m_actor)
					{
						if (!actor) continue;
						auto name = actor->get_name();

						if (name.find(entityName) != std::string::npos)
						{
							if (auto root_component = actor->root_component())
							{
								auto pos = root_component->m_relative_location;
								auto distance = get_entity_coords()->distance(pos);
								if (distanceCheck)
								{
									if (distance > 100.f && distance < 2500.f)
									{
										if (!actor->harvested() && actor->allow_pick())
										{
											teleport_with_loading(pos);
											g_notification_service->success(xorstr("Ellohim Teleport"), std::format("Teleported to near {}", name));
											return;
										}
									}
								}
								else if (!distanceCheck)
								{
									teleport_with_loading(pos);
									g_notification_service->success(xorstr("Ellohim Teleport"), std::format("Teleported to {}", name));
									return;
								}
							}
						}
					}
				}
			});
		}
	};
}