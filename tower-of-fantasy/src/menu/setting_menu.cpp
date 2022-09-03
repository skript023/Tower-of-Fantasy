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
                unreal_engine::project_world_to_screen(*movement::get_entity_coords(), location);
                g_logger->info("Locations %f Relative Location %f", location.x, location.x);
            }

            ImGui::SameLine();

            if (ImGui::Button("Test FindOBJ"))
            {
                static auto fn = UObject::find_object_by_index<UFunction*>(9589);
                g_logger->info("function address : %X | Function name : %s", fn, " None");
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