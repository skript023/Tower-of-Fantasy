#pragma once
#include "../unreal_engine_utility.hpp"
#include "../drawing/d3d_drawing.hpp"
#include "thread_pool.hpp"

namespace big::misc
{
	inline bool* attribute_initialized()
	{
		if (auto player = unreal_engine::get_local_player())
		{
			if (auto control = player->m_player_controller)
			{
				if (auto pawn = control->m_pawn)
				{
					return &pawn->m_is_ability_initialized;
				}
			}
		}
		return nullptr;
	}

	inline void skip_button(bool activate)
	{
		g_thread_pool->push([activate] {
			if (activate)
			{
				*g_pointers->m_skip_button = 0x75;
			}
			else if (!activate)
			{
				*g_pointers->m_skip_button = 0x74;
			}
		});
	}

	inline void render_esp(bool activate)
	{
		if (activate && unreal_engine::game_state())
		{
			auto level_array = (*g_pointers->m_world)->m_level;

			for (int j = 0; j < level_array.count(); j++)
			{
				auto level_data = level_array[j];
				if (!level_array.valid(j)) continue;
				auto actor_array = level_data->m_actor;

				for (int i = 0; i < actor_array.count(); i++)
				{
					auto actor = actor_array[i];
					if (!actor_array.valid(i)) continue;
					auto name = actor->get_name();

					if (auto root_component = actor->root_component())
					{
						auto pos = root_component->m_relative_location;
						
						if (auto local_player = unreal_engine::get_local_player())
						{
							if (auto self = local_player->m_player_controller)
							{
								Vector2 location;
								if (self->project_world_to_screen(pos, location))
								{
									if (name.find("Scene_Box_Refresh_Wild_") != std::string::npos ||
										name.find("BP_Harvest_Gem_") != std::string::npos ||
										name.find("Box_OnlyOnce_") != std::string::npos
										)
									{
										auto distance = movement::get_entity_coords()->distance(pos);
										draw::RGBA red = { 255, 0, 0, 255 };
										draw::RGBA white = { 255, 255, 255, 255 };
										draw::RGBA green = { 0, 255, 0, 255 };
										float width = static_cast<float>(g_pointers->m_screen->x / 2);
										float height = static_cast<float>(g_pointers->m_screen->y / 2);

										draw::draw_line(width, 0, location.x, location.y, &red, 1.f);
										draw::draw_stroke_text(location.x, location.y, &white, std::format("{} [{:.2f}]m", name, distance).c_str());

										if (distance < 100.f) draw::draw_corner_box(location.x, location.y, 100.f, 50.f, 2.f, &green);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}