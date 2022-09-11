#pragma once
#include "../fwddec.hpp"
#include "../uobject.hpp"
#include "pawn.hpp"
#include "attribute_set.hpp"
#include "character_movement.hpp"
#include "skill_component.hpp"
#include "camera_manager.hpp"

#include "native_invoker.hpp"

namespace big
{
	#pragma pack(push, 1)

	/**
	* \brief class QRSLCharacter
	*/
	class Character : public UObject
	{
	public:
		void server_match_solo_league(bool isBattleAI)
		{
			if (!g_native_invoker->m_server_match_solo_league)
				g_native_invoker->m_server_match_solo_league = g_native_invoker->get_native("Function QRSL.QRSLPlayerCharacter.Server_MatchSoloLeague");

			g_native_invoker->m_server_match_solo_league_params.m_is_battle_ai = isBattleAI;

			process_event(g_native_invoker->m_server_match_solo_league, &g_native_invoker->m_server_match_solo_league_params);
		}
	};

	/**
	* \brief class AHottaCharacter
	*/
	class AcknowledgedPawn : public UObject
	{
	public:
		char pad0028[0x3C]; //0x0000
		uint8_t no_clip; //0x0064
		char pad_0065[0x3063]; //0x0065
		class QuestComponent* m_quest_component; //0x30C8
		char pad_30D0[0x2210]; //0x30D0
		class AvatarUnlockDataArray* m_avatar_unlock; //0x52E0
	public:
		void server_quest_update_progress(FName QuestID, FName ObjectiveID, int progress, bool is_add)
		{
			if (!g_native_invoker->m_server_quest_update_progress)
				g_native_invoker->m_server_quest_update_progress = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ServerQuestUpdateProgress");
			
			g_native_invoker->m_server_quest_update_progress_param.m_quest_id = QuestID;
			g_native_invoker->m_server_quest_update_progress_param.m_objective_id = ObjectiveID;
			g_native_invoker->m_server_quest_update_progress_param.m_progress = progress;
			g_native_invoker->m_server_quest_update_progress_param.m_is_add = is_add;

			process_event(g_native_invoker->m_server_quest_update_progress, &g_native_invoker->m_server_quest_update_progress_param);
		}

		void teleport_with_loading(FVector dst, Rotator rot)
		{
			static auto teleport = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.TeleportWithLoading");

			g_native_invoker->m_teleport_with_loading_params.m_location = dst;
			g_native_invoker->m_teleport_with_loading_params.m_rotator = rot;

			process_event(teleport, &g_native_invoker->m_teleport_with_loading_params);
		}

		void server_teleport_with_loading(FVector dst, Rotator rot)
		{
			if (!g_native_invoker->m_server_teleport_with_loading)
				g_native_invoker->m_server_teleport_with_loading = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.TeleportWithLoading");

			g_native_invoker->m_teleport_with_loading_params.m_location = dst;
			g_native_invoker->m_teleport_with_loading_params.m_rotator = rot;

			process_event(g_native_invoker->m_server_teleport_with_loading, &g_native_invoker->m_teleport_with_loading_params);
		}

		void client_teleport_to(FVector dst, Rotator rot)
		{
			if (!g_native_invoker->m_client_teleport_to)
				g_native_invoker->m_client_teleport_to = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ClientTeleportTo");
			
			g_native_invoker->m_teleport_with_loading_params.m_location = dst;
			g_native_invoker->m_teleport_with_loading_params.m_rotator = rot;

			process_event(g_native_invoker->m_client_teleport_to, &g_native_invoker->m_teleport_with_loading_params);
		}

		void client_teleport_with_loading(FVector dst, Rotator rot)
		{
			if (!g_native_invoker->m_client_teleport_with_loading)
				g_native_invoker->m_client_teleport_with_loading = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ClientTeleportTo");

			g_native_invoker->m_teleport_with_loading_params.m_location = dst;
			g_native_invoker->m_teleport_with_loading_params.m_rotator = rot;

			process_event(g_native_invoker->m_client_teleport_with_loading, &g_native_invoker->m_teleport_with_loading_params);
		}

		void update_evade_count()
		{
			auto self = g_native_invoker;
			if (!self->m_update_cur_skill_evade_bean_count)
				self->m_update_cur_skill_evade_bean_count = self->get_native("Function HottaFramework.HottaPlayerCharacter.UpdateCurSkillEvadeBeanCount");

			process_event(self->m_update_cur_skill_evade_bean_count, nullptr);
		}

		bool set_character_exp(int exp)
		{
			if (!g_native_invoker->m_set_character_exp)
				g_native_invoker->m_set_character_exp = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.SetCharacterExp");

			g_native_invoker->m_set_character_exp_params.m_new_exp = exp;

			process_event(g_native_invoker->m_set_character_exp, &g_native_invoker->m_set_character_exp_params);

			return g_native_invoker->m_set_character_exp_params.m_return_value;
		}
	};
	static_assert(sizeof(AcknowledgedPawn) == 0x52E8);

	class PlayerController : public UObject
	{
	public:
		char pad_0028[0x238];
		class Pawn* m_pawn; //0x260
		char pad_0268[8]; //0x268
		Character* m_character; //0x270
		char pad_0278[56]; //0x278
		class AcknowledgedPawn* m_acknowledge_pawn; //0x2B0
		char pad_2B8[16]; //0x2B8
		class PlayerCameraManager* m_camera_manager; //0x2C8
	public:
		bool project_world_to_screen(FVector& WorldLocation, FVector2D& ScreenLocation, bool bPlayerViewportRelative = false)
		{
			if (!g_native_invoker->m_world_to_screen)
				g_native_invoker->m_world_to_screen = g_native_invoker->get_native("Function Engine.PlayerController.ProjectWorldLocationToScreen");
			
			g_native_invoker->m_world_to_screen_param.m_world_location = WorldLocation;
			g_native_invoker->m_world_to_screen_param.m_screen_location = ScreenLocation;
			g_native_invoker->m_world_to_screen_param.m_viewport_relative = bPlayerViewportRelative;

			process_event(g_native_invoker->m_world_to_screen, &g_native_invoker->m_world_to_screen_param);

			ScreenLocation = g_native_invoker->m_world_to_screen_param.m_screen_location;
			return g_native_invoker->m_world_to_screen_param.m_return;
		}
	};
	static_assert(sizeof(PlayerController) == 0x2D0);

	class LocalPlayer : public UObject
	{
	public:
		char pad_0028[8];
		class PlayerController* m_player_controller;
	};
	static_assert(sizeof(LocalPlayer) == 0x38);

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