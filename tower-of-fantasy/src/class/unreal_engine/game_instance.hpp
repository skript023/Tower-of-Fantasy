#pragma once
#include "../fwddec.hpp"
#include "pawn.hpp"
#include "attribute_set.hpp"
#include "character_movement.hpp"
#include "skill_component.hpp"
#include "camera_manager.hpp"

#include "native_invoker.hpp"

namespace big
{
	#pragma pack(push, 1)

	class Unk_1
	{
	public:
		char pad000[0x64];
		uint8_t no_clip;
	};

	class PlayerController : public UObject
	{
	public:
		char pad_0028[0x238];
		class Pawn* m_pawn; //0x260
		char pad_0268[72]; //0x268
		class Unk_1* m_unk; //0x2B0
		char pad_2B8[16]; //0x2B8
		class PlayerCameraManager* m_camera_manager; //0x2C8
	public:
		bool project_world_to_screen(FVector& WorldLocation, FVector2D& ScreenLocation, bool bPlayerViewportRelative = false)
		{
			auto fn = g_native_invoker->m_world_to_screen;
			
			g_native_invoker->m_world_to_screen_param.world_location = WorldLocation;
			g_native_invoker->m_world_to_screen_param.screen_location = ScreenLocation;
			g_native_invoker->m_world_to_screen_param.m_viewport_relative = bPlayerViewportRelative;

			process_event(fn, &g_native_invoker->m_world_to_screen_param);

			ScreenLocation = g_native_invoker->m_world_to_screen_param.screen_location;
			return g_native_invoker->m_world_to_screen_param.m_return;
		}
	};
	static_assert(sizeof(PlayerController) == 0x2D0);

	class LocalPlayer
	{
	public:
		char pad_0000[0x30];
		class PlayerController* m_player_controller;
	};

	class GameState
	{
	public:
		virtual ~GameState() = default;
		int m_game_state; 
	};

	class OwningGameInstance
	{
	public:
		char pad_0000[0x38]; //0x0000
		TArray<LocalPlayer*> m_local_player; //0x0038
	};

	#pragma pack(pop)
}