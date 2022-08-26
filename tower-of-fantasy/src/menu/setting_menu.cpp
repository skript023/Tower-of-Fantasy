#include "imgui.h"
#include "setting_menu.h"
#include "utility/features/all.hpp"
#include "thread_pool.hpp"
#include <script.hpp>
#include <gui.hpp>

namespace big
{
    void setting_menu::render_menu()
    {
        if (ImGui::BeginTabItem("Setting"))
        {
            if (ImGui::Button("Check Name Pool"))
            {
				auto level_array = (*g_pointers->m_world)->m_level;

				for (int j = 0; j < level_array.count(); j++)
				{
					auto level_data = level_array[j];
					if (!*(uintptr_t*)level_data) continue;

					g_logger->info("ULevel Array : 0x%X", level_data);
					auto actor_array = level_data->m_actor;

					for (int i = 0; i < actor_array.count(); i++)
					{
						auto actor = actor_array[i];
						if (!*(uintptr_t*)actor || (*(uintptr_t*)actor < 0x1000000)) continue;

						g_logger->info("AActor Array : 0x%X", actor);

						if (int id = actor->m_name_index)
						{
							auto name = unreal_engine::get_name(id);
							if (auto root_component = actor->m_root_component)
							{
								if (!**(uintptr_t**)root_component || (*(uintptr_t*)root_component < 0x1000000)) continue;

								g_logger->info("Name : %s | Root : 0x%X", name.c_str(), root_component);

								auto pos = root_component->m_relative_location;
								if (pos == Vector3(0.f, 0.f, 0.f)) continue;

								g_logger->info("Location : x : %f | y : %f | z : %f", pos.x, pos.y, pos.z);
								//auto location = unreal_engine::get_local_player()->m_player_controller->project_world_to_screen(pos);
								//g_gui.m_entity_list[name] = location;
							}
						}
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