#include "imgui.h"
#include "player_menu.h"
#include "script.hpp"
#include <translation.hpp>

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
                        for (auto& quest : self->m_quest_component->m_quest_in_progress)
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

            if (ImGui::Button(BIG_TRANSLATE("Heal"), ImVec2(120, 0)))
            {
                QUEUE_JOB_BEGIN_CLAUSE()
                {
                    if (auto self = unreal_engine::get_hotta_character(); self)
                    {
                        auto max = self->m_skill_component->m_max_health;
                        self->set_health(max, EDamageReason::Max, false, 0.0f);
                        self->server_set_health(max, EDamageReason::Max);
                    }
                } QUEUE_JOB_END_CLAUSE
            }

            ImGui::EndGroup();

            if (ImGui::CollapsingHeader(BIG_TRANSLATE("Teleport Option")))
            {
                auto teleport_locations = persist_teleport::list_locations();
                static std::string selected_location;
                static char teleport_name[50]{};
                if (unreal_engine::game_state() && g_features->movement.get_entity_coords())
                {
                    ImGui::Text(std::format("Coordinates -> X : {:.2f} Y : {:.2f} Z : {:.2f}", g_features->movement.get_entity_coords()->x, g_features->movement.get_entity_coords()->y, g_features->movement.get_entity_coords()->z).c_str());
                }

                if (ImGui::Button(xorstr("Teleport Forward"), ImVec2(160, 0)))
                {
                    g_features->movement.teleport_forward();
                }

                ImGui::SameLine();

                if (ImGui::Button(BIG_TRANSLATE("Teleport to supply pod"), ImVec2(160, 0)))
                {
                    g_fiber_pool->queue_job([]
                    {
                        for (auto level : (*g_pointers->m_world)->m_level)
                        {
                            for (auto actor : level->m_actor)
                            {
                                auto name = actor->get_name();

                                if (name.find("Scene_Box_OnceOnly_") != std::string::npos || name.find("scene_box_brambles_") != std::string::npos)
                                {
                                    if (auto root_component = actor->root_component())
                                    {
                                        auto pos = root_component->m_relative_location;
                                        auto distance = g_features->movement.get_entity_coords()->distance(pos);
                                        if (distance > 100.f && distance < 2500.f)
                                        {
                                            if (!actor->harvested() && actor->allow_pick())
                                            {
                                                g_features->movement.teleport_with_loading(pos);
                                                g_notification_service->success(xorstr("Ellohim Teleport"), xorstr("Teleported to near supply pods"));
                                                return;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    });
                }

                ImGui::SameLine();

                if (ImGui::Button(BIG_TRANSLATE("Teleport to black nucleus"), ImVec2(160, 0)))
                {
                    g_fiber_pool->queue_job([]
                    {
                        for (auto level : (*g_pointers->m_world)->m_level)
                        {
                            for (auto actor : level->m_actor)
                            {
                                auto name = actor->get_name();

                                if (name.find("BP_Harvest_Gem_") != std::string::npos)
                                {
                                    if (auto root_component = actor->root_component())
                                    {
                                        auto pos = root_component->m_relative_location;
                                        g_features->movement.teleport_with_loading(pos);
                                        g_notification_service->success(xorstr("Ellohim Teleport"), xorstr("Teleported to near black nucleus"));
                                        return;
                                    }
                                }
                            }
                        }
                    });
                }

                if (ImGui::Button(xorstr("Teleport to Fire Link"), ImVec2(160, 0)))
                {
                    g_fiber_pool->queue_job([]
                    {
                        for (auto level : (*g_pointers->m_world)->m_level)
                        {
                            for (auto actor : level->m_actor)
                            {
                                auto name = actor->get_name();

                                if (name.find("BP_FireLink_Minigame") != std::string::npos)
                                {
                                    if (auto root_component = actor->root_component())
                                    {
                                        auto pos = root_component->m_relative_location;
                                        auto distance = g_features->movement.get_entity_coords()->distance(pos);
                                        if (distance > 500.f && distance < 2500.f)
                                        {
                                            if (!actor->harvested())
                                            {
                                                g_features->movement.teleport_with_loading(pos);
                                                g_notification_service->success(xorstr("Ellohim Teleport"), xorstr("Teleported to near fire link"));
                                                return;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    });
                }

                ImGui::SameLine();

                if (ImGui::Button(xorstr("Teleport to Flower Throw"), ImVec2(160, 0)))
                {
                    g_fiber_pool->queue_job([]
                        {
                            for (auto level : (*g_pointers->m_world)->m_level)
                            {
                                for (auto actor : level->m_actor)
                                {
                                    auto name = actor->get_name();

                                    if (name.find("BP_MiniGame_ThrowFlower_") != std::string::npos)
                                    {
                                        if (auto root_component = actor->root_component())
                                        {
                                            auto pos = root_component->m_relative_location;
                                            auto distance = g_features->movement.get_entity_coords()->distance(pos);
                                            if (distance > 500.f && distance < 2500.f)
                                            {
                                                if (!actor->harvested())
                                                {
                                                    g_features->movement.teleport_with_loading(pos);
                                                    g_notification_service->success(xorstr("Ellohim Teleport"), xorstr("Teleported to near flower"));
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        });
                }

                ImGui::SameLine();

                if (ImGui::Button(xorstr("Teleport to Chest Box"), ImVec2(160, 0)))
                {
                    g_fiber_pool->queue_job([]
                        {
                            for (auto level : (*g_pointers->m_world)->m_level)
                            {
                                for (auto actor : level->m_actor)
                                {
                                    auto name = actor->get_name();

                                    if (name.find("Scene_Box_Refresh_Wild_") != std::string::npos)
                                    {
                                        if (auto root_component = actor->root_component())
                                        {
                                            auto pos = root_component->m_relative_location;
                                            g_features->movement.teleport_with_loading(pos);
                                            g_notification_service->success(xorstr("Ellohim Teleport"), xorstr("Teleported to near chest"));
                                            return;
                                        }
                                    }
                                }
                            }
                        });
                }

                ImGui::PushItemWidth(200);
                ImGui::InputText(BIG_TRANSLATE("Location Name"), teleport_name, IM_ARRAYSIZE(teleport_name));
                ImGui::PopItemWidth();

                ImGui::SameLine();

                if (ImGui::Button(BIG_TRANSLATE("Save Location")))
                {
                    persist_teleport::save_location(*g_features->movement.get_entity_coords(), teleport_name);
                    ZeroMemory(teleport_name, sizeof(teleport_name));
                }

                ImGui::PushItemWidth(250);
                ImGui::Text(BIG_TRANSLATE("Saved Locations"));
                if (ImGui::ListBoxHeader("##empty", ImVec2(200, 200)))
                {
                    for (auto pair : teleport_locations)
                    {
                        if (ImGui::Selectable(pair.c_str(), selected_location == pair))
                            selected_location = pair;
                    }
                    ImGui::ListBoxFooter();
                }
                ImGui::PopItemWidth();

                ImGui::SameLine();
                ImGui::BeginGroup();

                ImGui::Text("Teleport Method");

                ImGui::PushItemWidth(150.f);
                ImGui::Combo(xorstr("##Teleport Method"), &selected_method, method, IM_ARRAYSIZE(method));
                ImGui::PopItemWidth();

                if (ImGui::Button(BIG_TRANSLATE("Load Location")))
                {
                    if (!selected_location.empty())
                    {
                        switch (selected_method)
                        {
                        case 0:
                            persist_teleport::load_location(selected_location);
                            break;
                        case 1:
                            persist_teleport::load_location_with_loading(selected_location);
                            break;
                        }
                    }
                }

                if (ImGui::Button(BIG_TRANSLATE("Delete Location")))
                {
                    if (!selected_location.empty())
                    {
                        persist_teleport::delete_location(selected_location);
                        selected_location.clear();
                    }
                }
                ImGui::EndGroup();
            }

            ImGui::EndTabItem();
        }
	}
}