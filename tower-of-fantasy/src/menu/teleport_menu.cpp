#include "teleport_menu.h"
#include "translation.hpp"
#include "script.hpp"

#include "utility/services/all.hpp"
#include "utility/ecryption.h"
#include "utility/features/all.hpp"
#include "utility/config/persist_teleport.h"

namespace big
{
	void teleport_menu::render_menu()
	{
		if (ImGui::BeginTabItem("Teleport"))
		{
            if (ImGui::Button(xorstr("Teleport Forward"), ImVec2(160, 0)))
            {
                g_features->movement.teleport_forward();
            }

            ImGui::Combo(xorstr("##List Teleport"), &selected_teleport, target, IM_ARRAYSIZE(target));
            if (ImGui::Button(xorstr("Teleport player to items"), ImVec2(160, 0)))
            {
                switch (selected_teleport)
                {
                case 0:
                    g_features->movement.teleport_to_entity("Scene_Box_OnceOnly_", true);
                    break;
                case 1:
                    g_features->movement.teleport_to_entity("scene_box_brambles_", true);
                    break;
                case 2:
                    g_features->movement.teleport_to_entity("BP_Harvest_Gem_", false);
                    break;
                case 3:
                    g_features->movement.teleport_to_entity("BP_FireLink_Minigame", true);
                    break;
                case 4:
                    g_features->movement.teleport_to_entity("BP_MiniGame_ThrowFlower_", true);
                    break;
                case 5:
                    g_features->movement.teleport_to_entity("Scene_Box_Refresh_Wild_", false);
                    break;
                case 6:
                    g_features->movement.teleport_to_entity("BP_MiniGame_FlyFlower", false);
                    break;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Teleport items to player"), ImVec2(160, 0)))
            {
                switch (selected_teleport)
                {
                case 0:
                    g_features->movement.vacuum_items("Scene_Box_OnceOnly_", true);
                    break;
                case 1:
                    g_features->movement.vacuum_items("scene_box_brambles_", true);
                    break;
                case 2:
                    g_features->movement.vacuum_items("BP_Harvest_Gem_", false);
                    break;
                case 3:
                    g_features->movement.vacuum_items("BP_FireLink_Minigame", false);
                    break;
                case 4:
                    g_features->movement.vacuum_items("BP_MiniGame_ThrowFlower_", false);
                    break;
                case 5:
                    g_features->movement.vacuum_items("Scene_Box_Refresh_Wild_", false);
                    break;
                case 6:
                    g_features->movement.vacuum_items("BP_MiniGame_FlyFlower", false);
                    break;
                }
            }

			if (ImGui::CollapsingHeader(xorstr("Custom Teleport")))
			{
                auto teleport_locations = persist_teleport::list_locations();
                static std::string selected_location;
                static char teleport_name[50]{};
                if (unreal_engine::game_state() && g_features->movement.get_entity_coords())
                {
                    ImGui::Text(std::format("Coordinates -> X : {:.2f} Y : {:.2f} Z : {:.2f}", g_features->movement.get_entity_coords()->x, g_features->movement.get_entity_coords()->y, g_features->movement.get_entity_coords()->z).c_str());
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

                ImGui::PushItemWidth(165.f);
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