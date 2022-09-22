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
		uint8_t m_is_actor_enable_collision; //0x0064
		uint8_t m_update_overlap_method_during_level_streaming; //0x0065
		uint8_t m_default_update_overlaps_method_during_level_streaming; //0x0066
		uint8_t m_remote_role; //0x0067
		FVector m_linear_velocity; //0x0068
		FVector m_angular_velocity; //0x0074
		FVector m_location; //0x0080
		Rotator m_rotation; //0x008C
		uint8_t m_simulate_pysic_sleep; //0x0098
		char pad_0099[3]; //0x0099
		int m_initial_life_span; //0x009C
		float m_custom_dilation; //0x00A0
		char pad_00A4[68]; //0x00A4
		class Owner* m_owner; //0x00E8
		int64_t m_net_driver_name; //0x00F0
		uint8_t m_role; //0x00F8
		uint8_t m_net_dormancy; //0x00F9
		uint8_t m_spawn_collision_handling; //0x00FA
		uint8_t m_auto_receive_input; //0x00FB
		int m_input_priority; //0x00FC
		class InputComponent* m_input_component; //0x0100
		int m_net_cull_distance_squared;//0x0108
		int m_net_tag; //0x010C
		int m_net_update_frequency; //0x0110
		int m_min_net_update_frequency; //0x0114
		int m_net_priority; //0x0118
		int m_padding; //0x011C
		class Instigator* m_instigator; //0x0120
		TArray<class Children*> m_children; //0x0128
		class RootComponent* m_root_component; //0x0138
		TArray<class ControllingMatineeActors*> m_controller_matinee_actors; //0x0140
		char pad_0150[8]; //0x0150
		TArray<class Layers*> m_layers; //0x0158
		int m_parent_componen; //0x0168
		char pad_016C[12]; //0x016C
		TArray<class Tags*> m_tags; //0x0178
		char pad_0188[280]; //0x0188
		class CapsuleComponent* m_capsule_component; //0x02A0
		char pad_02A8[0x4D8]; //0x02A8
		class SkillComponent* m_skill_component; //0x0780
		char pad_0788[0x2940]; //0x0788
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

			g_native_invoker->m_teleport_with_loading_params.m_location.x = dst.x;
			g_native_invoker->m_teleport_with_loading_params.m_location.y = dst.y;
			g_native_invoker->m_teleport_with_loading_params.m_location.z = dst.z + 400.f;

			g_native_invoker->m_teleport_with_loading_params.m_rotator = rot;

			process_event(teleport, &g_native_invoker->m_teleport_with_loading_params);
		}

		void server_teleport_with_loading(FVector dst, Rotator rot)
		{
			if (!g_native_invoker->m_server_teleport_with_loading)
				g_native_invoker->m_server_teleport_with_loading = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.TeleportWithLoading");

			g_native_invoker->m_teleport_with_loading_params.m_location.x = dst.x;
			g_native_invoker->m_teleport_with_loading_params.m_location.y = dst.y;
			g_native_invoker->m_teleport_with_loading_params.m_location.z = dst.z + 400.f;

			g_native_invoker->m_teleport_with_loading_params.m_rotator = rot;

			process_event(g_native_invoker->m_server_teleport_with_loading, &g_native_invoker->m_teleport_with_loading_params);
		}

		void server_teleport_to(FVector dst, Rotator rot)
		{
			if (!g_native_invoker->m_server_teleport_to)
				g_native_invoker->m_server_teleport_to = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ServerTeleportTo");

			g_native_invoker->m_teleport_with_loading_params.m_location.x = dst.x;
			g_native_invoker->m_teleport_with_loading_params.m_location.y = dst.y;
			g_native_invoker->m_teleport_with_loading_params.m_location.z = dst.z + 400.f;

			g_native_invoker->m_teleport_with_loading_params.m_rotator = rot;

			process_event(g_native_invoker->m_server_teleport_to, &g_native_invoker->m_teleport_with_loading_params);
		}

		void client_teleport_to(FVector dst, Rotator rot)
		{
			if (!g_native_invoker->m_client_teleport_to)
				g_native_invoker->m_client_teleport_to = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ClientTeleportTo");
			
			g_native_invoker->m_teleport_with_loading_params.m_location.x = dst.x;
			g_native_invoker->m_teleport_with_loading_params.m_location.y = dst.y;
			g_native_invoker->m_teleport_with_loading_params.m_location.z = dst.z + 400.f;

			g_native_invoker->m_teleport_with_loading_params.m_rotator = rot;

			process_event(g_native_invoker->m_client_teleport_to, &g_native_invoker->m_teleport_with_loading_params);
		}

		void client_teleport_with_loading(FVector dst, Rotator rot)
		{
			if (!g_native_invoker->m_client_teleport_with_loading)
				g_native_invoker->m_client_teleport_with_loading = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ClientTeleportTo");

			g_native_invoker->m_teleport_with_loading_params.m_location.x = dst.x;
			g_native_invoker->m_teleport_with_loading_params.m_location.y = dst.y;
			g_native_invoker->m_teleport_with_loading_params.m_location.z = dst.z + 400.f;

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

		void server_add_exp(int exp, int limit_index)
		{
			if (!g_native_invoker->m_server_add_exp)
				g_native_invoker->m_server_add_exp = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ServerAddExp");

			g_native_invoker->m_server_add_exp_params.m_value = exp;
			g_native_invoker->m_server_add_exp_params.m_limit_index = limit_index;

			process_event(g_native_invoker->m_set_character_exp, &g_native_invoker->m_server_add_exp_params);
		}

		void server_kick_player(FString playerName)
		{
			ServerKickPlayer params{};
			if (!g_native_invoker->m_server_kick_player)
				g_native_invoker->m_server_kick_player = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ServerKickPlayer");

			params.m_target = playerName;

			process_event(g_native_invoker->m_server_kick_player, &params);
		}

		void server_set_health(float health, EDamageReason damageReason)
		{
			if (!g_native_invoker->m_server_set_health)
				g_native_invoker->m_server_set_health = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.ServerSetHP");

			g_native_invoker->m_server_set_health_params.m_health = health;
			g_native_invoker->m_server_set_health_params.m_damage_reason = damageReason;

			process_event(g_native_invoker->m_server_set_health, &g_native_invoker->m_server_set_health_params);
		}

		void set_health(float health, EDamageReason damageReason, bool isReadDamage, float readDamage)
		{
			if (!g_native_invoker->m_set_health)
				g_native_invoker->m_set_health = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.SetHP");

			g_native_invoker->m_set_health_params.m_health = health;
			g_native_invoker->m_set_health_params.m_damage_reason = damageReason;
			g_native_invoker->m_set_health_params.m_is_read_damage = isReadDamage;
			g_native_invoker->m_set_health_params.m_read_damage = readDamage;

			process_event(g_native_invoker->m_set_health, &g_native_invoker->m_set_health_params);
		}

		void server_set_character_level(int level)
		{
			if (!g_native_invoker->m_server_set_character_level)
				g_native_invoker->m_server_set_character_level = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.ServerSetCharacterLevel");

			g_native_invoker->m_server_set_character_level_params.m_level = level;

			process_event(g_native_invoker->m_server_set_character_level, &g_native_invoker->m_server_set_character_level_params);
		}

		bool set_character_level(int level, bool refreshAttribute, bool ServerRep)
		{
			if (!g_native_invoker->m_set_character_level)
				g_native_invoker->m_set_character_level = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.SetCharacterLevel");

			g_native_invoker->m_set_character_level_params.m_level = level;
			g_native_invoker->m_set_character_level_params.m_refresh_attribute = refreshAttribute;
			g_native_invoker->m_set_character_level_params.m_server_rep = ServerRep;

			process_event(g_native_invoker->m_set_character_level, &g_native_invoker->m_set_character_level_params);

			return g_native_invoker->m_set_character_level_params.m_return;
		}

		void set_energy(float energy)
		{
			SetEnergy params{};

			if (!g_native_invoker->m_set_energy)
				g_native_invoker->m_set_energy = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.SetEnergy");

			params.m_energy = energy;

			process_event(g_native_invoker->m_set_energy, &params);
		}
		
		void set_mana(float mana)
		{
			SetEnergy params{};
			if (!g_native_invoker->m_set_mana)
				g_native_invoker->m_set_mana = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.SetMana");

			params.m_energy = mana;

			process_event(g_native_invoker->m_set_energy, &params);
		}

		float get_mana()
		{
			GetMaxMana params{};
			if (!g_native_invoker->m_get_mana)
				g_native_invoker->m_get_mana = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.GetMana");

			process_event(g_native_invoker->m_get_mana, &params);

			return params.m_return;
		}

		float get_max_mana()
		{
			GetMaxMana params{};
			if (!g_native_invoker->m_get_max_mana)
				g_native_invoker->m_get_max_mana = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.GetMaxMana");

			process_event(g_native_invoker->m_get_max_mana, &params);

			return params.m_return;
		}
		
		void server_set_location_and_rotation(FVector location, Rotator rotation, bool authoritative)
		{
			if (!g_native_invoker->m_server_set_location_and_rotation)
				g_native_invoker->m_server_set_location_and_rotation = g_native_invoker->get_native("Function HottaFramework.HottaCharacter.ServerSetLocationAndRotation");

			g_native_invoker->m_server_set_location_and_rotation_params.m_location.x = location.x;
			g_native_invoker->m_server_set_location_and_rotation_params.m_location.y = location.y;
			g_native_invoker->m_server_set_location_and_rotation_params.m_location.z = location.z + 400.f;

			g_native_invoker->m_server_set_location_and_rotation_params.m_rotation = rotation;
			g_native_invoker->m_server_set_location_and_rotation_params.m_close_server_accept_client_authoritative_position = authoritative;

			process_event(g_native_invoker->m_server_set_location_and_rotation, &g_native_invoker->m_server_set_location_and_rotation_params);
		}

		void client_set_auto_combat(bool activate)
		{
			ClientSetAutoCombat params{};
			if (!g_native_invoker->m_client_set_auto_combat)
				g_native_invoker->m_client_set_auto_combat = g_native_invoker->get_native("Function HottaFramework.HottaPlayerCharacter.ClientSetAutoCombat");
		
			params.m_enable = activate;

			process_event(g_native_invoker->m_client_set_auto_combat, &params);
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
		bool project_world_to_screen(FVector& WorldLocation, FVector2D& ScreenLocation, bool bPlayerViewportRelative = true)
		{
			WorldToScreenParam params{};
			if (!g_native_invoker->m_world_to_screen)
				g_native_invoker->m_world_to_screen = g_native_invoker->get_native("Function Engine.PlayerController.ProjectWorldLocationToScreen");
			
			params.m_world_location = WorldLocation;
			params.m_screen_location = ScreenLocation;
			params.m_viewport_relative = bPlayerViewportRelative;

			process_event(g_native_invoker->m_world_to_screen, &params);

			ScreenLocation = params.m_screen_location;
			return params.m_return;
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