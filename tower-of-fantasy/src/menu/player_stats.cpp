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

                ImGui::InputFloat("Attack Multiplier", attack::attack_multiplier(), 1.0f, 1.5f);

                ImGui::InputFloat("Pysical Attack", attack::pysical_attack(), 1.0f, 1.5f);

                ImGui::InputFloat("Critical Damage", attack::critical_damage(), 1.0f, 1.5f);

                ImGui::InputFloat("Critical Rate", attack::critical_rate(), 1.0f, 1.5f);

                ImGui::InputFloat("Fire Attack", attack::fire_attack(), 1.0f, 1.5f);

                ImGui::InputFloat("Thunder Attack", attack::thunder_attack(), 1.0f, 1.5f);

                ImGui::InputFloat("Ice Attack", attack::ice_attack(), 1.0f, 1.5f);

                ImGui::InputFloat("Super Power Attack", attack::super_power_attack(), 1.0f, 1.5f);

                ImGui::InputFloat("Health", defense::health(), 1.0f, 1.5f);

                ImGui::InputFloat("Max Health", defense::max_health(), 1.0f, 1.5f);

                ImGui::InputFloat("Energy Recovery Multiplier", defense::energy_recover_multiplier(), 1.0f, 1.5f);

                ImGui::InputFloat("Pysical Defense", defense::pysical_defense(), 1.0f, 1.5f);

                ImGui::InputFloat("Fire Defense", defense::fire_defense(), 1.0f, 1.5f);

                ImGui::InputFloat("Thunder Defense", defense::thunder_defense(), 1.0f, 1.5f);

                ImGui::InputFloat("Ice Defense", defense::ice_defense(), 1.0f, 1.5f);

                ImGui::InputFloat("Super Power Defense", defense::super_power_defense(), 1.0f, 1.5f);

                ImGui::InputFloat("Movement Speed", movement::player_movement_speed(), 1.0f, 1.5f);

                ImGui::InputFloat("Swim Speed", movement::player_swim_speed(), 1.0f, 1.5f);

                ImGui::InputFloat("Crouch Speed", movement::player_crouch_speed(), 1.0f, 1.5f);

                ImGui::InputFloat("Gravity", movement::player_gravity(), 1.0f, 1.5f);
            }

            ImGui::EndTabItem();
        }
	}
}