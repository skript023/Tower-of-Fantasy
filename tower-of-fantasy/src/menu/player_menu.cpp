#include "imgui.h"
#include "player_menu.h"
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
            if (ImGui::Checkbox("God mode", &g_settings->player.godmode))
                defense::godmode(g_settings->player.godmode);

            ImGui::Checkbox("Infinite Jump", &g_settings->player.infinite_jump);

            if (ImGui::Checkbox("No Cooldown", &g_settings->player.no_cooldown))
                attack::remove_cooldown(g_settings->player.no_cooldown);

            ImGui::EndGroup();

            ImGui::SameLine(200);

            ImGui::BeginGroup();

            if (ImGui::Checkbox("No Fall Damage", &g_settings->player.no_fall_damage))
                defense::remove_fall_damage(g_settings->player.no_fall_damage);

            if (ImGui::Checkbox("Freeze Player", &g_settings->player.freeze_entity))
                movement::freeze_entity(g_settings->player.freeze_entity);

            if (ImGui::Checkbox("Freeze Mobs", &g_settings->player.freeze_mobs))
                movement::freeze_mobs(g_settings->player.freeze_mobs);

            ImGui::EndGroup();

            ImGui::SameLine(400);

            ImGui::BeginGroup();

            ImGui::Checkbox("Infinite Dodge", &g_settings->player.infinite_dodge);

            ImGui::Checkbox("Rapid Attack", &g_settings->player.fast_attack);

            if (ImGui::Checkbox("No Clip", &g_settings->player.no_clip))
                movement::no_clip(g_settings->player.no_clip);

            ImGui::EndGroup();

            if (ImGui::CollapsingHeader("Teleport Option"))
            {
                auto teleport_locations = persist_teleport::list_locations();
                static std::string selected_location;
                static char teleport_name[50]{};

                ImGui::PushItemWidth(200);
                ImGui::InputText("Location Name", teleport_name, IM_ARRAYSIZE(teleport_name));
                ImGui::PopItemWidth();

                ImGui::SameLine();

                if (ImGui::Button("Save Location"))
                {
                    persist_teleport::save_location(movement::get_entity_coords(), teleport_name);
                    ZeroMemory(teleport_name, sizeof(teleport_name));
                }

                ImGui::PushItemWidth(250);
                ImGui::Text("Saved Locations");
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

                if (ImGui::Button("Load Location"))
                {
                    if (!selected_location.empty())
                    {
                        persist_teleport::load_location(selected_location);
                    }
                }
                if (ImGui::Button("Delete Location"))
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