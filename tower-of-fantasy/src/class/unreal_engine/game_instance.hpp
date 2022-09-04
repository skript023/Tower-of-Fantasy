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

	class AcknowledgedPawn : public UObject
	{
	public:
		char pad0028[0x3C]; //0x0000
		uint8_t no_clip; //0x0064

	public:
		void m_server_quest_update_progress(std::string QuestID, std::string ObjectiveID, int progress, bool is_add)
		{
			g_native_invoker->m_server_quest_update_progress_param.quest_id = QuestID;
			g_native_invoker->m_server_quest_update_progress_param.objective_id = ObjectiveID;
			g_native_invoker->m_server_quest_update_progress_param.progress = progress;
			g_native_invoker->m_server_quest_update_progress_param.is_add = is_add;

			process_event(g_native_invoker->m_server_quest_update_progress, &g_native_invoker->m_server_quest_update_progress_param);
		}
	};
	static_assert(sizeof(AcknowledgedPawn) == 0x65);

	class PlayerController : public UObject
	{
	public:
		char pad_0028[0x238];
		class Pawn* m_pawn; //0x260
		char pad_0268[72]; //0x268
		class AcknowledgedPawn* m_acknowledge_pawn; //0x2B0
		char pad_2B8[16]; //0x2B8
		class PlayerCameraManager* m_camera_manager; //0x2C8
	public:
		bool project_world_to_screen(FVector& WorldLocation, FVector2D& ScreenLocation, bool bPlayerViewportRelative = false)
		{
			g_native_invoker->m_world_to_screen_param.world_location = WorldLocation;
			g_native_invoker->m_world_to_screen_param.screen_location = ScreenLocation;
			g_native_invoker->m_world_to_screen_param.m_viewport_relative = bPlayerViewportRelative;

			process_event(g_native_invoker->m_world_to_screen, &g_native_invoker->m_world_to_screen_param);

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