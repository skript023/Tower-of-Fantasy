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
                if (auto const self = unreal_engine::get_hotta_character(); self)
                {
                    auto quest = self->m_quest_component->m_quest_in_progress->m_quest_in_progress[0];
                    auto object = quest.m_objective_progress->m_objective_progress[0];
                    g_logger->info("Quest %X Quest ID %d | Objective %d | Needed : %d", quest, quest.m_quest_id, object.m_objective_id, object.m_needed_amount);
                    self->m_server_quest_update_progress(quest.m_quest_id, object.m_objective_id, object.m_needed_amount, true);
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Test Quest"))
            {
                if (auto const self = unreal_engine::get_hotta_character(); self)
                {
                    for (auto& quest : self->m_quest_component->quest_in_progress())
                    {
                        for (auto& objective : quest.object_progress())
                        {
                            g_logger->info("Quest Base : 0x%X | Quest : 0x%X | Objective : %X | Quest ID : %d | Objective ID : %d", self->m_quest_component, quest, objective, quest.m_quest_id, objective.m_objective_id);
                            self->m_server_quest_update_progress(quest.m_quest_id, objective.m_objective_id, objective.m_needed_amount, true);
                        }
                    }

                    for (auto& quest : self->m_quest_component->accepted_quest())
                    {
                        for (auto& objective : quest.object_progress())
                        {
                            g_logger->info("Quest Base 2 : 0x%X | Quest 2 : 0x%X | Objective 2 : %X | Quest ID 2 : %d | Objective 2 ID : %d", self->m_quest_component, quest, objective, quest.m_quest_id, objective.m_objective_id);
                            self->m_server_quest_update_progress(quest.m_quest_id, objective.m_objective_id, objective.m_needed_amount, true);
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