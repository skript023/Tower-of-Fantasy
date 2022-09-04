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
                Vector2 location;
                unreal_engine::get_local_player()->m_player_controller->project_world_to_screen(*movement::get_entity_coords(), location, false);

                g_logger->info("Locations %f Screen Location %f", movement::get_entity_coords()->x, location.x);
            }

            ImGui::SameLine();

            if (ImGui::Button("Test FindOBJ"))
            {
                static auto fn = UObject::find_object<UFunction*>("Function Engine.PlayerController.ProjectWorldLocationToScreen");
                g_logger->info("function address : QRSL.exe+%X | Function Pointer : %X| Function name : %s", fn->Func, fn, fn->get_fullname().c_str());
            }
            
            ImGui::SameLine();

            if (ImGui::Button("Test get name"))
            {
                for (int i = 0; i < UObject::get_global_object()->num(); i++)
                {
                    auto object = UObject::get_global_object()->get_by_index(i);
                    if (object)
                    {
                        g_logger->info("Outer : 0x%X | UObject : 0x%X", object->m_outer, object);
                        g_logger->info("[%i]Name : %s", i, object->get_fullname().c_str());
                        if (object->get_fullname() == "Function Engine.PlayerController.ProjectWorldLocationToScreen")
                        {
                            g_logger->info("[%i]found : %s", i, object->get_fullname().c_str());
                        }
                    }
                }
                //g_logger->info("fullname : %s", UObject::get_global_object()->get_object_pointer(0)->m_object->get_fullname().c_str());
            }

            ImGui::SameLine();

            if (ImGui::Button("Test pointer name"))
            {
                for (int i = 0; i < UObject::get_global_object()->num(); i++)
                {
                    auto object = UObject::get_global_object()->get_object_pointer(i);
                    if (object->get_valid_object())
                    {
                        g_logger->info("[%i]FUObject : 0x%X | Dereference : 0x%X | UObject : %s", i, object, object->get_valid_object(), object->get_valid_object()->get_fullname().c_str());
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