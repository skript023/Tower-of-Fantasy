#pragma once
#include "../unreal_engine_utility.hpp"
#include "../drawing/d3d_drawing.hpp"

namespace big::misc
{
	inline void skip_button(bool activate)
	{
		if (activate)
		{
			*g_pointers->m_skip_button = 0x75;
		}
		else if(!activate)
		{
			*g_pointers->m_skip_button = 0x74;
		}
	}

	inline void render_esp(bool activate)
	{
		if (activate && unreal_engine::world_state())
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

					if (int id = actor->m_name_index)
					{
						auto name = unreal_engine::get_name(id);
						if (!actor->valid_root_component()) continue;

						if (auto root_component = actor->m_root_component)
						{
							auto pos = root_component->m_relative_location;
							if (auto player = unreal_engine::get_local_player())
							{
								if (auto control = player->m_player_controller)
								{
									if (auto camera_mgr = control->m_camera_manager)
									{
										Vector2 location;
										if (camera_mgr->m_camera_cache.project_world_to_screen(pos, location))
										{
											if (name.find("Scene_Box_Refresh_Wild_") != std::string::npos ||
												name.find("BP_Harvest_Gem_") != std::string::npos ||
												name.find("Box_OnlyOnce_") != std::string::npos
												)
											{
												auto distance = movement::get_entity_coords()->distance(pos);
												draw::RGBA red = { 255, 0, 0, 255 };
												draw::RGBA white = { 255, 255, 255, 255 };
												float width = static_cast<float>((*g_pointers->m_screen).x / 2);
												float height = static_cast<float>((*g_pointers->m_screen).y / 2);

												draw::draw_line(width, height, location.x, location.y, &red, 1.f);
												draw::draw_stroke_text(location.x, location.y, &white, std::format("{} [{:.2f}]m", name, distance).c_str());
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
	}
}