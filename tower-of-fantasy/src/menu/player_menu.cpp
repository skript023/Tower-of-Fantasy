#include "imgui.h"
#include "player_menu.h"
#include "script.hpp"
#include "translation.hpp"

#include "utility/services/all.hpp"
#include "utility/ecryption.h"
#include "utility/features/all.hpp"
#include "utility/config/persist_teleport.h"

namespace big
{
	void player_menu::render_menu()
	{
        if (ImGui::BeginTabItem("Player Option"))
        {
            auto end = std::chrono::system_clock::now();
            std::time_t date = std::chrono::system_clock::to_time_t(end);

            ImGui::Text("%s", std::ctime(&date));

            ImGui::BeginGroup();
            if (ImGui::Checkbox(BIG_TRANSLATE("Godmode"), &g_settings->player.godmode))
                g_features->defense.godmode(g_settings->player.godmode);

            ImGui::Checkbox(BIG_TRANSLATE("Inf Jump"), &g_settings->player.infinite_jump);

            if (ImGui::Checkbox(BIG_TRANSLATE("No Cooldown"), &g_settings->player.no_cooldown))
                g_features->attack.remove_cooldown(g_settings->player.no_cooldown);

            ImGui::Checkbox(BIG_TRANSLATE("ESP"), &g_settings->player.esp);

            ImGui::Checkbox(BIG_TRANSLATE("Inf Energy"), &g_settings->player.infinite_energy);

            ImGui::EndGroup();

            ImGui::SameLine(200);

            ImGui::BeginGroup();

            if (ImGui::Checkbox("No Fall Damage", &g_settings->player.no_fall_damage))
                g_features->defense.remove_fall_damage(g_settings->player.no_fall_damage);

            if (ImGui::Checkbox("Freeze Player", &g_settings->player.freeze_entity))
                g_features->movement.freeze_entity(g_settings->player.freeze_entity);

            if (ImGui::Checkbox("Freeze Mobs", &g_settings->player.freeze_mobs))
                g_features->movement.freeze_mobs(g_settings->player.freeze_mobs);

            if (ImGui::Checkbox(BIG_TRANSLATE("Skateboard"), &g_settings->player.skateboard))
            {
                unreal_engine::get_pawn()->m_skateboard_starting = g_settings->player.skateboard;
                unreal_engine::get_pawn()->m_skateboard_sliding = g_settings->player.skateboard;
            }

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(xorstr("Enable skateboard relic"));

            ImGui::Checkbox(BIG_TRANSLATE("Inf Mana"), &g_settings->player.infinite_mana);

            ImGui::EndGroup();

            ImGui::SameLine(400);

            ImGui::BeginGroup();

            ImGui::Checkbox(BIG_TRANSLATE("Inf Dodge"), &g_settings->player.infinite_dodge);

            if (ImGui::Checkbox(BIG_TRANSLATE("Can't jump"), &g_settings->player.cant_jump))
                unreal_engine::get_pawn()->m_cant_jump = g_settings->player.cant_jump;

            if (ImGui::Checkbox(BIG_TRANSLATE("No Clip"), &g_settings->player.no_clip))
                g_features->movement.no_clip(g_settings->player.no_clip);

            ImGui::Checkbox(BIG_TRANSLATE("Reset Box"), &g_settings->player.reset_box);

            if (ImGui::Checkbox(xorstr("Auto Combat"), &g_settings->player.auto_combat))
            {
                g_fiber_pool->queue_job([] {
                    if (auto self = unreal_engine::get_hotta_character(); self)
                    {
                        self->client_set_auto_combat(g_settings->player.auto_combat);
                    }
                });
            }

            ImGui::EndGroup();

            ImGui::BeginGroup();
            if (ImGui::Button(BIG_TRANSLATE("AI Only PVP"), ImVec2(120, 0)))
            {
                g_fiber_pool->queue_job([] {
                    unreal_engine::get_local_player()->m_player_controller->m_character->server_match_solo_league(true);
                });
            }
            ImGui::EndGroup();

            ImGui::SameLine();

            ImGui::BeginGroup();

            if (ImGui::Button(BIG_TRANSLATE("Auto Quest"), ImVec2(120, 0)))
            {
                g_fiber_pool->queue_job([]
                {
                    if (auto const self = unreal_engine::get_hotta_character(); self)
                    {
                        for (auto&& quest : self->m_quest_component->m_quest_in_progress)
                        {
                            for (auto&& objective : quest.m_objective_progress)
                            {
                                g_notification_service->success(xorstr("Ellohim Auto Quest"), std::format("{} Quest has been completed", quest.m_quest_id.get_name()));
                                self->server_quest_update_progress(quest.m_quest_id, objective.m_objective_id, objective.m_needed_amount, true);
                            }
                        }

                        for (auto&& quest : self->m_quest_component->m_auto_accept_quest_array)
                        {
                            for (auto&& objective : quest.m_objective_progress)
                            {
                                self->server_quest_update_progress(quest.m_quest_id, objective.m_objective_id, objective.m_needed_amount, true);
                            }
                        }
                    }
                });
            }
            
            ImGui::EndGroup();

            ImGui::SameLine();

            ImGui::BeginGroup();

            

            ImGui::EndGroup();
            ImGui::Combo("##BygonLevels", &selected_bygon_level, bygon_level, IM_ARRAYSIZE(bygon_level));
            if (ImGui::Button(xorstr("Enter Bygon Phantasm")))
            {
                g_fiber_pool->queue_job([] {
                    if (auto self = unreal_engine::get_character())
                    {
                        self->server_require_enter_big_secret(selected_bygon_level);
                    }
                });
            }

            ImGui::EndTabItem();
        }
	}
}