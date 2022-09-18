#include "misc.hpp"
#include "thread_pool.hpp"
#include "../drawing/d3d_drawing.hpp"
#include "all.hpp"
#include "class/kismet_text.hpp"

namespace big
{
	bool* MiscOption::attribute_initialized()
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
	void MiscOption::skip_button(bool activate)
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
	void MiscOption::get_entity_list(bool activate)
	{
		if (activate && unreal_engine::game_state())
		{
			m_entity_list.clear();
			for (auto level : (*g_pointers->m_world)->m_level.to_vector())
			{
				for (auto actor : level->m_actor.to_vector())
				{
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
									m_entity_list.push_back({ location, pos, name, actor });
								}
							}
						}
					}
				}
			}
		}
	}
	void MiscOption::render_esp(bool activate)
	{
		if (activate && unreal_engine::game_state())
		{
			for (auto entity : m_entity_list)
			{
				auto distance = g_features->movement.get_entity_coords() != nullptr ? g_features->movement.get_entity_coords()->distance(entity.m_relative_location) : 0.f;
				draw::RGBA red = { 255, 0, 0, 255 };
				draw::RGBA white = { 255, 255, 255, 255 };
				draw::RGBA green = { 0, 255, 0, 255 };
				float width = static_cast<float>(g_pointers->m_screen->x / 2);
				float height = static_cast<float>(g_pointers->m_screen->y / 2);

				if (entity.name.find("Scene_Box_Refresh_Wild_") != std::string::npos ||
					entity.name.find("BP_FireLink_Minigame") != std::string::npos ||
					entity.name.find("BP_MiniGame_ThrowFlower_") != std::string::npos ||
					entity.name.find("BP_Harvest_Gem_") != std::string::npos
					)
				{
					draw::draw_line(width, 0, entity.m_position.x, entity.m_position.y, &red, 1.f);
					draw::draw_stroke_text(entity.m_position.x, entity.m_position.y, &white, std::format("{} [{:.2f}]m", entity.name, distance).c_str());

					if (distance < 100.f) draw::draw_corner_box(entity.m_position.x, entity.m_position.y, 100.f, 50.f, 2.f, &green);
				}
				else if (entity.name.find("Scene_Box_OnceOnly_") != std::string::npos ||
					entity.name.find("scene_box_brambles_") != std::string::npos
					)
				{
					if (!entity.m_actor->harvested() && entity.m_actor->allow_pick())
					{
						draw::draw_line(width, 0, entity.m_position.x, entity.m_position.y, &red, 1.f);
						draw::draw_stroke_text(entity.m_position.x, entity.m_position.y, &white, std::format("{} [{:.2f}]m", entity.name, distance).c_str());

						if (distance < 100.f) draw::draw_corner_box(entity.m_position.x, entity.m_position.y, 100.f, 50.f, 2.f, &green);
					}
				}
			}
		}
	}
}