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
            if (ImGui::Button("Test Object"))
            {
                Vector2 location;
                unreal_engine::get_local_player()->m_player_controller->project_world_to_screen(*movement::get_entity_coords(), location, false);

                g_logger->info("Locations %f Screen Location %f", movement::get_entity_coords()->x, location.x);
            }

            ImGui::SameLine();

            if (ImGui::Button("Test Quest"))
            {
                if (auto const self = unreal_engine::get_hotta_character(); self)
                {
                    auto quest_component = self->m_quest_component->m_quest_in_progress;
                    for (int i = 0; i < quest_component.count(); i+=14)
                    {
                        if (!quest_component.valid(i)) continue;
                        auto quest = quest_component[i];
                        auto objective_progress = quest_component[i]->m_objective_progress;

                        for (int j = 0; j < objective_progress.count(); j+=4)
                        {
                            if (!objective_progress.valid(j)) continue;
                            auto objective = objective_progress[j];

                            self->m_server_quest_update_progress(quest->m_quest_id, objective->m_objective_id, objective->m_needed_amount, true);
                        }
                    }

                    auto accept = self->m_quest_component->m_auto_accept_quest_array;
                    for (int i = 0; i < accept.count(); i+=5)
                    {
                        if (!accept.valid(i)) continue;
                        auto quest = *accept[i];
                        auto objective_progress = accept[i]->m_objective_progress;

                        for (int j = 0; j < objective_progress.count(); j+=4)
                        {
                            if (!objective_progress.valid(j)) continue;
                            auto objective = objective_progress[j];
                            self->m_server_quest_update_progress(quest.m_quest_id, objective->m_objective_id, objective->m_needed_amount, true);
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