#include "player_stats.h"
#include "imgui.h"
#include "utility/features/all.hpp"

namespace big
{
	void player_stat::render_menu()
	{
        if (ImGui::BeginTabItem("Player Stats"))
        {
            ImGui::SliderInt("Player Level", player::player_level(), 0, 100);

            ImGui::SliderFloat("Attack Multiplier", attack::attack_multiplier(), 0.0f, 9999.f);

            ImGui::SliderFloat("Pysical Attack", attack::pysical_attack(), 0.0f, 9999.f);

            ImGui::SliderFloat("Critical Damage", attack::critical_damage(), 0.0f, 9999.f);

            ImGui::SliderFloat("Critical Rate", attack::critical_rate(), 0.0f, 100.f);

            ImGui::SliderFloat("Movement Speed", movement::player_movement_speed(), default_move, 9999.f);

            ImGui::SliderFloat("Swim Speed", movement::player_swim_speed(), default_swim, 9999.f);

            ImGui::SliderFloat("Crouch Speed", movement::player_crouch_speed(), default_crouch, 9999.f);

            ImGui::SliderFloat("Gravity", movement::player_gravity(), 0.f, 9999.f);

            ImGui::EndTabItem();
        }
	}
}