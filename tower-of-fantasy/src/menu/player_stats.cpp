#include "player_stats.h"
#include "imgui.h"
#include "utility/features/all.hpp"
#include <utility/ecryption.h>

namespace big
{
	void player_stat::render_menu()
	{
        if (ImGui::BeginTabItem("Player Stats"))
        {
            if (ImGui::Checkbox(xorstr("Critical Hack"), &critical_hack))
            {
                if (critical_hack)
                {
                    *g_features->attack.critical_rate() = 100.f;
                    *g_features->attack.critical_damage() += 25.f;
                }
            }
            if (ImGui::CollapsingHeader(xorstr("Other")))
            {
                ImGui::InputInt("Player Level ", &level);
                if (ImGui::Button(xorstr("Set Level")))
                {
                    if (auto self = unreal_engine::get_hotta_character())
                    {
                        self->server_set_character_level(level);
                        if (self->set_character_level(level, false, false))
                        {
                            g_logger->info("Set level to %d", level);
                        }
                    }
                }

                ImGui::InputText(xorstr("Target"), target, IM_ARRAYSIZE(target));
                if (ImGui::Button(xorstr("Kick Player")))
                {
                    if (auto self = unreal_engine::get_hotta_character())
                    {
                        self->server_kick_player(FString(target));
                    }
                }
            }
            if (unreal_engine::game_state())
            {
                if (ImGui::CollapsingHeader("Player Stats"))
                {
                    ImGui::InputInt("Player Level", player::player_level());

                    ImGui::InputFloat("Current EXP Multiplier", g_features->defense.server_current_exp_mult(), 1.0f, 1.5f);

                    ImGui::InputFloat("Attack Multiplier", g_features->attack.attack_multiplier(), 1.0f, 1.5f);

                    ImGui::InputFloat("Pysical Attack", g_features->attack.pysical_attack(), 1.0f, 1.5f);

                    ImGui::InputFloat("Critical Damage", g_features->attack.critical_damage(), 1.0f, 1.5f);

                    ImGui::InputFloat("Critical Rate", g_features->attack.critical_rate(), 1.0f, 1.5f);

                    ImGui::InputFloat("Fire Attack", g_features->attack.fire_attack(), 1.0f, 1.5f);

                    ImGui::InputFloat("Thunder Attack", g_features->attack.thunder_attack(), 1.0f, 1.5f);

                    ImGui::InputFloat("Ice Attack", g_features->attack.ice_attack(), 1.0f, 1.5f);

                    ImGui::InputFloat("Super Power Attack", g_features->attack.super_power_attack(), 1.0f, 1.5f);

                    ImGui::InputFloat("Health", g_features->defense.health(), 1.0f, 1.5f);

                    ImGui::InputFloat("Max Health", g_features->defense.max_health(), 1.0f, 1.5f);

                    ImGui::InputFloat("Energy Recovery Multiplier", g_features->defense.energy_recover_multiplier(), 1.0f, 1.5f);

                    ImGui::InputFloat("Pysical Defense", g_features->defense.pysical_defense(), 1.0f, 1.5f);

                    ImGui::InputFloat("Fire Defense", g_features->defense.fire_defense(), 1.0f, 1.5f);

                    ImGui::InputFloat("Thunder Defense", g_features->defense.thunder_defense(), 1.0f, 1.5f);

                    ImGui::InputFloat("Ice Defense", g_features->defense.ice_defense(), 1.0f, 1.5f);

                    ImGui::InputFloat("Super Power Defense", g_features->defense.super_power_defense(), 1.0f, 1.5f);

                    ImGui::InputFloat("Movement Speed", g_features->movement.player_movement_speed(), 1.0f, 1.5f);

                    ImGui::InputFloat("Swim Speed", g_features->movement.player_swim_speed(), 1.0f, 1.5f);

                    ImGui::InputFloat("Crouch Speed", g_features->movement.player_crouch_speed(), 1.0f, 1.5f);

                    ImGui::InputFloat("Gravity", g_features->movement.player_gravity(), 1.0f, 1.5f);
                }
            }

            ImGui::EndTabItem();
        }
	}
}