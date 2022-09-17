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

	struct Conv_TextToString
	{
		struct FText m_in_text;
		struct FString m_return_value;
	};

	struct Server_ProjectileActorHit
	{
		void* m_self;
		void* m_target;
		struct SimpleHit* m_simple_hit;
		char padding[88];
		struct PredictionKey* m_prediction_key;
	};

	struct SetProjectileTrackActor
	{
		void* m_actor;
	};

	struct ServerSetHP
	{
		float m_health;
		EDamageReason m_damage_reason;
	};

	struct ServerSetCharacterLevel
	{
		int m_level;
	};

	struct ServerSetLocationAndRotation
	{
		FVector m_location;
		Rotator m_rotation;
		bool m_close_server_accept_client_authoritative_position;
	};

	struct ServerSetHaveFallDamage
	{
		bool m_in_have_fall_damage;
	};

	struct ServerKickPlayer
	{
		FString m_target;
	};

	struct ServerLotteryExtract
	{
		FName m_module_name;
		int m_extract_count;
		bool m_is_discount;
	};

	struct ServerPickItem
	{
		FName m_item_id;
		int m_amount;
		class ItemActor* m_owner;
		int m_slot;
	};

	class NativeInvoker
	{
	public:
		explicit NativeInvoker();
		~NativeInvoker();

		UFunction* get_native(std::string name);
		static void execute_native_function(std::string className, std::string functionName, void* parameters);

		template <typename T>
		T get_class(std::string name);

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
		UFunction* m_server_set_health;
		UFunction* m_server_set_character_level;
		UFunction* m_server_set_location_and_rotation;
		UFunction* m_server_kick_player;
	public:
		UClass* m_kismet_text_library;
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
		Conv_TextToString m_convert_text_to_string_params{};
		SetProjectileTrackActor m_set_projectile_track_actor_params{};
		ServerSetHP m_server_set_health_params{};
		ServerSetCharacterLevel m_server_set_character_level_params{};
		ServerSetLocationAndRotation m_server_set_location_and_rotation_params{};
	private:
		inline static UFunction* m_function;
		inline static UClass* m_class;
	};

	inline NativeInvoker* g_native_invoker;
}