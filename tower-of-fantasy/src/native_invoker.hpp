#pragma once
#include "class/fwddec.hpp"
#include "class/vector.hpp"
#include "class/fname_pool.hpp"
#include "class/enums.hpp"

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
		EHottaCurrencyType m_currency_type;
		int m_amount;
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

	struct ClientUpdateAccumulateCurrencyArraySingle
	{
		EHottaCurrencyType m_currency_type;
		int m_amount;
	};

	struct ClientOnCurrencyAmountChanged
	{
		EHottaCurrencyType m_currency_type;
		int64_t m_add_amount;
		int64_t m_current_value;
		EHottaOutputPathType m_path_type;
		bool m_need_show_tips;
		bool m_need_show_in_chat;
	};

	struct ServerAddExp
	{
		int m_value;
		int m_limit_index;
	};

	struct ServerUpgradeItem
	{
		FName m_item_id;
		FName m_target_id;
		int m_target_count;
	};

	struct ServerCheckQuestRpcRequire
	{
		EQuestRpcRequireType m_require_type;
		FName m_quest_id;
		FName m_objective_id;
	};

	struct ServerRecordExploreProgress
	{
		FName m_drop_id;
		int m_drop_num;
	};

	struct ServerMatrixStrengthen
	{
		int m_slot_index;
		uint8_t m_contain_type;
	};

	struct ServerUpgradeStarLevel
	{
		int m_choose_item_slot;
		uint8_t m_contain_type;
	};

	struct ServerMatrixUnequiped
	{
		int m_weapon_slot;
		uint8_t m_contain_type;
		uint8_t m_matrix_slot;
	};

	class NativeInvoker
	{
	public:
		explicit NativeInvoker();
		~NativeInvoker();

		UFunction* get_native(std::string name);
		UFunction* get_native_ex(const char* name);
		std::string get_output_path_type(EHottaOutputPathType PathType);
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
		UFunction* m_server_add_exp;
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
		ClientUpdateAccumulateCurrencyArraySingle m_client_update_accumulate_currency_array_single_params{};
		ClientOnCurrencyAmountChanged m_client_on_currency_amount_changed_params{};
		ServerAddExp m_server_add_exp_params{};
	};

	inline NativeInvoker* g_native_invoker;
}