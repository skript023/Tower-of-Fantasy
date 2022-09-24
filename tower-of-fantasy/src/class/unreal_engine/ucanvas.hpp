#pragma once
#include "pointers.hpp"
#include "../fwddec.hpp"
#include "../vector.hpp"
#include "../natives.hpp"
#include "utility/unreal_engine_utility.hpp"
#include "utility/features/all.hpp"

namespace big
{
	class UCanvas : public UObject
	{
	public:
		inline void k2_draw_text(void* RenderFont, FString& RenderText, FVector2D ScreenPosition, FVector2D Scale, FLinearColor& RenderColor, float Kerning, FLinearColor& ShadowColor, FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, FLinearColor& OutlineColor)
		{
			K2_DrawText params{};
			if (!m_k2_draw_text)
				m_k2_draw_text = UObject::find_object<UFunction*>("Function Engine.Canvas.K2_DrawText");

			params = { RenderFont , RenderText, ScreenPosition, Scale, RenderColor, Kerning, ShadowColor, ShadowOffset, bCentreX, bCentreY, bOutlined, OutlineColor };
			process_event(m_k2_draw_text, &params);
		}

		inline void k2_draw_line(FVector2D source, FVector2D destination, float thickness, FLinearColor RenderColor)
		{
			K2_DrawLine params{ source, destination, thickness, RenderColor };
			if (!m_k2_draw_line)
				m_k2_draw_line = UObject::find_object<UFunction*>("Function Engine.Canvas.K2_DrawLine");

			process_event(m_k2_draw_line, &params);
		}

		inline void k2_draw_box(FVector2D pos, FVector2D size, float thickness, FLinearColor RenderColor)
		{
			K2_DrawBox params{};
			if (!m_k2_draw_box)
				m_k2_draw_box = UObject::find_object<UFunction*>("Function Engine.Canvas.K2_DrawBox");

			params = { pos, size, thickness, RenderColor };
			process_event(m_k2_draw_box, &params);
		}

		inline void draw_filled_rect(const FVector2D& initial_pos, float w, float h, const FLinearColor& RenderColor)
		{
			for (float i = 0.f; i < h; i += 1.f)
				this->k2_draw_line(FVector2D(initial_pos.x, initial_pos.y + i), FVector2D(initial_pos.x + w, initial_pos.y + i), 1.f, RenderColor);
		}

		inline void draw_rect(const FVector2D& initial_pos, float w, float h, const FLinearColor& RenderColor, float thickness = 1.f)
		{
			this->k2_draw_line(FVector2D(initial_pos.x, initial_pos.y), FVector2D(initial_pos.x + w, initial_pos.y), thickness, RenderColor);
			this->k2_draw_line(FVector2D(initial_pos.x, initial_pos.y), FVector2D(initial_pos.x, initial_pos.y + h), thickness, RenderColor);
			this->k2_draw_line(FVector2D(initial_pos.x + w, initial_pos.y), FVector2D(initial_pos.x + w, initial_pos.y + h), thickness, RenderColor);
			this->k2_draw_line(FVector2D(initial_pos.x, initial_pos.y + h), FVector2D(initial_pos.x + w, initial_pos.y + h), thickness, RenderColor);
		}

		inline void draw_esp(bool activate)
		{
			if (activate)
			{
				for (auto level : (*g_pointers->m_world)->m_level)
				{
					if (!level) continue;
					for (auto actor : level->m_actor)
					{
						if (!actor) continue;
						auto name = actor->get_name();

						if (auto root_component = actor->root_component())
						{
							auto pos = root_component->m_relative_location;

							if (auto local_player = unreal_engine::get_local_player())
							{
								if (auto self = local_player->m_player_controller; self)
								{
									Vector2 location;
									if (self->project_world_to_screen(pos, location))
									{
										auto distance = g_features->movement.get_entity_coords() != nullptr ? g_features->movement.get_entity_coords()->distance(pos) : 0.f;
										FLinearColor red = { 1.f, 0.f, 0.f, 1.f };
										FLinearColor white = { 1.f, 1.f, 1.f, 1.f };
										FLinearColor green = { 0.f, 1.f, 0, 1.f };
										FLinearColor shadow(0.f, 0.f, 0.f, 0.f);
										FLinearColor outline(0.f, 0.f, 0.f, 1.f);
										float width = static_cast<float>(g_pointers->m_screen->x / 2);
										float height = static_cast<float>(g_pointers->m_screen->y / 2);
										FString names(std::format("{} [{:.2f}]m", name, distance).c_str());

										if (name.find("Scene_Box_Refresh_Wild_") != std::string::npos ||
											name.find("BP_FireLink_Minigame") != std::string::npos ||
											name.find("BP_MiniGame_ThrowFlower_") != std::string::npos ||
											name.find("BP_Minigame_NanoMetal_") != std::string::npos ||
											name.find("BP_Minigame_ElementAttack_Volcano_") != std::string::npos ||
											name.find("BP_MiniGame_FlyFlower") != std::string::npos ||
											name.find("BP_Harvest_Gem_") != std::string::npos
											)
										{
											this->k2_draw_line(Vector2(width, 0), Vector2(location.x, location.y), 1.f, red);
											this->k2_draw_text((*g_pointers->m_engine)->m_font, names, Vector2(location.x, location.y), Vector2(1.f, 1.f), white, 0.f, shadow, Vector2(1.f, 1.f), true, true, true, outline);

											if (distance < 100.f) this->k2_draw_box(FVector2D(location.x, location.y), FVector2D(100.f, 50.f), 2.f, green);
										}
										else if (name.find("Scene_Box_OnceOnly_") != std::string::npos ||
											name.find("scene_box_brambles_") != std::string::npos
											)
										{
											if (!actor->harvested() && actor->allow_pick())
											{
												this->k2_draw_line(Vector2(width, 0), Vector2(location.x, location.y), 1.f, red);
												this->k2_draw_text((*g_pointers->m_engine)->m_font, names, Vector2(location.x, location.y), Vector2(1.f, 1.f), white, 0.f, shadow, Vector2(1.f, 1.f), true, true, true, outline);

												if (distance < 100.f) this->k2_draw_box(FVector2D(location.x, location.y), FVector2D(100.f, 50.f), 2.f, green);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	private:
		UFunction* m_k2_draw_text;
		UFunction* m_k2_draw_line;
		UFunction* m_k2_draw_box;
	};
}