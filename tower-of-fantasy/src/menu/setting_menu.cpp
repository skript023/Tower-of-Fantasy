#include "imgui.h"
#include "setting_menu.h"
#include "utility/features/all.hpp"
#include "thread_pool.hpp"
#include <script.hpp>
#include <gui.hpp>
#include <utility/ecryption.h>

namespace big
{
    void setting_menu::render_menu()
    {
        if (ImGui::BeginTabItem("Setting"))
        {
            ImGui::Checkbox(xorstr("Log Process Event"), &g_settings->system.log_process_event);

            if (ImGui::Button("Get Entity List Name"))
            {
                for (auto level : (*g_pointers->m_world)->m_level)
                {
                    for (auto actor : level->m_actor)
                    {
                        if (actor->get_name().find("Scene_Box_OnceOnly_") != std::string::npos ||
                            actor->get_name().find("scene_box_brambles_") != std::string::npos)
                        {
                            g_logger->info("Name : %s | Harvested : %d | Allow pick : %d | Client can open : %d", actor->get_fullname().c_str(), actor->m_has_harvested, actor->m_is_allow_pick, actor->m_can_client_open);
                        }
                    }
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Test Quest"))
            {
                if (auto const self = unreal_engine::get_hotta_character(); self)
                {
                    for (auto&& quest : self->m_quest_component->m_quest_in_progress)
                    {
                        for (auto&& objective : quest.m_objective_progress)
                        {
                            g_logger->info("Quest : 0x%X | Objective : %X | Quest ID : %d | Objective ID : %d | Amount : %d", quest, objective, quest.m_quest_id, objective.m_objective_id, objective.m_needed_amount);
                            self->server_quest_update_progress(quest.m_quest_id, objective.m_objective_id, objective.m_needed_amount, true);
                        }
                        
                    }

                    for (auto&& quest : self->m_quest_component->m_auto_accept_quest_array)
                    {
                        g_logger->info("Quest Base : 0x%X | Quest : 0x%X | Quest ID : %d", self->m_quest_component, quest, quest.m_quest_id);
                        for (auto&& objective : quest.m_objective_progress)
                        {
                            g_logger->info("Quest Base 2 : 0x%X | Quest 2 : 0x%X | Objective 2 : %X | Quest ID 2 : %d | Objective 2 ID : %d", self->m_quest_component, quest, objective, quest.m_quest_id, objective.m_objective_id);
                            self->server_quest_update_progress(quest.m_quest_id, objective.m_objective_id, objective.m_needed_amount, true);
                        }
                    }
                }
            }
            
            if (ImGui::Button("Unload"))
            {
                g_running = false;
            }

            ImGui::SameLine();

            if (ImGui::Button(xorstr("Quit Game")))
            {
                exit(0);
            }

            ImGui::EndTabItem();
        }
    }
}