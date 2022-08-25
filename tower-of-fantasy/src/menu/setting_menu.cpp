#include "imgui.h"
#include "setting_menu.h"
#include "utility/features/all.hpp"
#include "thread_pool.hpp"
#include <script.hpp>

namespace big
{
    void setting_menu::render_menu()
    {
        if (ImGui::BeginTabItem("Setting"))
        {
            if (ImGui::Button("Check Name Pool"))
            {
				auto level_array = (*g_pointers->m_world)->m_level;
				auto level_size = (*g_pointers->m_world)->m_level_size;

				for (int j = 0; j < level_size; j++)
				{
					auto level_data = level_array->m_level_array[j];
					if (!*(uintptr_t*)level_data) continue;

					g_logger->info("ULevel Array : 0x%X", level_data);
					auto actor_array = level_data->m_actor;
					auto actor_size = level_data->m_actor_count;

					for (int i = 0; i < actor_size; i++)
					{
						auto actor = actor_array->m_actor_array[i];
						if (!*(uintptr_t*)actor) continue;

						g_logger->info("AActor Array : 0x%X", actor);

						if (int id = actor->m_name_index)
						{
						}
						/*
						if (int id = actor->m_name_index)
						{
							auto name = unreal_engine::get_name(id);
							g_logger->info("Name : %s", name.c_str());
							auto root_component = actor->m_root_component;
							if (*(uintptr_t*)root_component != NULL || root_component != nullptr)
							{
								auto pos = root_component->m_relative_location;
								g_logger->info("Location : x : %f | y : %f | z : %f", pos.x, pos.y, pos.z);

								//auto location = unreal_engine::get_local_player()->m_player_controller->project_world_to_screen(pos);
							}
						}
						*/
					}
				}
            }

            if (ImGui::Button("Quit"))
            {
                g_running = false;
            }

            ImGui::EndTabItem();
        }
    }
}