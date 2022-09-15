#include "player_stats.h"
#include "imgui.h"
#include "utility/features/all.hpp"

namespace big
{
	void player_stat::render_menu()
	{
        if (ImGui::BeginTabItem("Player Stats"))
        {
            static int level_exp = 0;
            ImGui::InputInt("Player EXP", &level_exp);
            if (ImGui::Button("Add EXP"))
            {
                if (auto self = unreal_engine::get_hotta_character(); self)
                {
                    self->set_character_exp(level_exp);
                }
            }

            if (ImGui::CollapsingHeader("Player Stats"))
            {
                ImGui::InputInt("Player Level", player::player_level());

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

            ImGui::EndTabItem();
        }
	}
}