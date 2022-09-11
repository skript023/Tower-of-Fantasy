#pragma once
#include "class/fwddec.hpp"
#include "class/vector.hpp"
#include "class/fname_pool.hpp"

namespace big
{
	struct WorldToScreenParam
	{
		Vector3 m_world_location;
		Vector2 m_screen_location;
		bool m_viewport_relative;
		bool m_return;
	};

	struct ServerQuestUpdateProgress
	{
		FName m_quest_id;
		FName m_objective_id;
		int m_progress;
		bool m_is_add;
	};

	struct ServerBuyGHAIntegral
	{
		int m_currency_type;
	};

	struct Server_MatchSoloLeague
	{
		bool m_is_battle_ai;
	};

	struct Server_PayTransferServerReq
	{
		int m_server_id;
	};

	struct ServerSpawnExtraEquipedWeapon
	{
		int64_t m_weapon_item;
	};

	struct ServerUnlockAvatar
	{
		uint8_t m_in_avatar_type;
		int64_t m_in_avatar_id;
		bool m_in_permanent_unlock;
		float m_in_expiration_time;
	};

	struct TeleportWithLoading
	{
		FVector m_location;
		Rotator m_rotator;
	};

	struct SpawnArtifactArrow
	{
		float m_duration_time;
	};

	struct ClientSetTreasureOpened
	{
		FName m_treasure_box_id;
		bool m_static;
		int64_t m_open_time;
	};
	
	struct ServerResetTreasureBox
	{
		FName m_treasure_box_id;
		bool m_static;
	};

	struct SetCharacterExp
	{
		int m_new_exp;
		bool m_return_value;
	};

	struct ServerRecordAbnormalJumpSectionData
	{
		std::string m_collect_info;
		std::string m_comment2;
		uint8_t m_anti_type;
	};

	class NativeInvoker
	{
	public:
		explicit NativeInvoker();
		~NativeInvoker();

		UFunction* get_native(std::string name);
		UFunction* get_native_ex(const char* name);
	public:
		UFunction* m_world_to_screen;
		UFunction* m_server_quest_update_progress;
		UFunction* m_server_buy_gha_integral;
		UFunction* m_server_projectile_actor_hit;
		UFunction* m_server_projectile_actor;
		UFunction* m_server_match_solo_league;
		UFunction* m_server_spawn_projectile;
		UFunction* m_server_cheat_max_suppressor_level;
		UFunction* m_server_change_role_info_sex;
		UFunction* m_server_pay_transfer_server_req;
		UFunction* m_server_spawn_extra_equiped_weapon;
		UFunction* m_server_unlock_avatar;
		UFunction* m_teleport_with_loading;
		UFunction* m_server_teleport_with_loading;
		UFunction* m_server_teleport_to;
		UFunction* m_client_teleport_to;
		UFunction* m_client_teleport_with_loading;
		UFunction* m_client_add_tower_energy;
		UFunction* m_spawn_artifact_arrow;
		UFunction* m_update_cur_skill_evade_bean_count;
		UFunction* m_server_reset_treasure_box;
		UFunction* m_set_character_exp;
	public:
		WorldToScreenParam m_world_to_screen_param{};
		ServerQuestUpdateProgress m_server_quest_update_progress_param{};
		ServerBuyGHAIntegral m_server_buy_gha_integral_params{};
		Server_MatchSoloLeague m_server_match_solo_league_params{};
		TeleportWithLoading m_teleport_with_loading_params{};
		SpawnArtifactArrow m_spawn_artifact_arrow_params{};
		ClientSetTreasureOpened m_client_set_treasure_opened_params{};
		ServerResetTreasureBox m_server_reset_treasure_box_params{};
		SetCharacterExp m_set_character_exp_params{};
	};

	inline NativeInvoker* g_native_invoker;
}