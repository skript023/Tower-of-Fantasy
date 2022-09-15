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

            ImGui::Checkbox(BIG_TRANSLATE("Infinite Jump"), &g_settings->player.infinite_jump);

            if (ImGui::Checkbox(BIG_TRANSLATE("No Cooldown"), &g_settings->player.no_cooldown))
                g_features->attack.remove_cooldown(g_settings->player.no_cooldown);

            ImGui::Checkbox(BIG_TRANSLATE("ESP"), &g_settings->player.esp);

            ImGui::EndGroup();

            ImGui::SameLine(200);

            ImGui::BeginGroup();

            if (ImGui::Checkbox("No Fall Damage", &g_settings->player.no_fall_damage))
                g_features->defense.remove_fall_damage(g_settings->player.no_fall_damage);

            if (ImGui::Checkbox("Freeze Player", &g_settings->player.freeze_entity))
                g_features->movement.freeze_entity(g_settings->player.freeze_entity);

            if (ImGui::Checkbox("Freeze Mobs", &g_settings->player.freeze_mobs))
                g_features->movement.freeze_mobs(g_settings->player.freeze_mobs);

            ImGui::Checkbox(BIG_TRANSLATE("Rapid Shoot"), &g_settings->player.rapid_shoot);

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(xorstr("For Projectile Weapon Only"));

            ImGui::EndGroup();

            ImGui::SameLine(400);

            ImGui::BeginGroup();

            ImGui::Checkbox(BIG_TRANSLATE("Infinite Dodge"), &g_settings->player.infinite_dodge);

            ImGui::Checkbox(BIG_TRANSLATE("Rapid Attack"), &g_settings->player.fast_attack);

            if (ImGui::Checkbox(BIG_TRANSLATE("No Clip"), &g_settings->player.no_clip))
                g_features->movement.no_clip(g_settings->player.no_clip);

            ImGui::Checkbox(BIG_TRANSLATE("Reset Box"), &g_settings->player.reset_box);

            ImGui::EndGroup();

            ImGui::BeginGroup();
            if (ImGui::Button(BIG_TRANSLATE("AI Only PVP"), ImVec2(120, 0)))
            {
                unreal_engine::get_local_player()->m_player_controller->m_character->server_match_solo_league(true);
            }

            ImGui::EndGroup();

            ImGui::SameLine();

            ImGui::BeginGroup();

            if (ImGui::Button(BIG_TRANSLATE("Auto Quest"), ImVec2(120, 0)))
            {
                g_thread_pool->push([]
                {
                    if (auto const self = unreal_engine::get_hotta_character(); self)
                    {
                        for (auto& quest : self->m_quest_component->quest_in_progress())
                        {
                            for (auto& objective : quest.object_progress())
                            {
                                g_notification_service->success(xorstr("Ellohim Auto Quest"), std::format("{} Quest has been completed", quest.m_quest_id.get_name()));
                                self->server_quest_update_progress(quest.m_quest_id, objective.m_objective_id, objective.m_needed_amount, true);
                            }

                        }

                        for (auto& quest : self->m_quest_component->accepted_quest())
                        {
                            for (auto& objective : quest.object_progress())
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

            if (ImGui::Button(BIG_TRANSLATE("Spawn Projectile"), ImVec2(120, 0)))
            {
                THREAD_POOL_BEGIN()
                {
                    if (auto pawn = unreal_engine::get_pawn(); pawn)
                    {
                        if (auto self = pawn->m_skill_component; self)
                        {
                            self->spawn_artifac_arrow(100.f);
                        }
                    }
                } THREAD_POOL_END
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
                        for (auto level : (*g_pointers->m_world)->m_level.to_vector())
                        {
                            for (auto actor : level->m_actor.to_vector())
                            {
                                auto name = actor->get_name();

                                if (name.find("Scene_Box_OnceOnly_") != std::string::npos)
                                {
                                    if (!actor->harvested())
                                    {
                                        if (auto root_component = actor->root_component())
                                        {
                                            auto pos = root_component->m_relative_location;
                                            auto distance = g_features->movement.get_entity_coords()->distance(pos);
                                            if (distance > 150.f && distance < 700.f)
                                            {
                                                g_features->movement.teleport_to(pos);
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
                    g_thread_pool->push([]
                        {
                            for (auto level : (*g_pointers->m_world)->m_level.to_vector())
                            {
                                for (auto actor : level->m_actor.to_vector())
                                {
                                    auto name = actor->get_name();

                                    if (name.find("BP_Harvest_Gem_") != std::string::npos)
                                    {
                                        if (auto root_component = actor->root_component())
                                        {
                                            auto pos = root_component->m_relative_location;
                                            auto distance = g_features->movement.get_entity_coords()->distance(pos);
                                            if (distance > 150.f && distance < 700.f)
                                            {
                                                g_features->movement.teleport_to(pos);
                                                g_notification_service->success(xorstr("Ellohim Teleport"), xorstr("Teleported to near black nucleus"));
                                                return;
                                            }
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