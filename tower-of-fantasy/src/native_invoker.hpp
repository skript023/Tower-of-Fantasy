#pragma once
#include "class/fwddec.hpp"
#include "class/natives.hpp"

namespace big
{
	class NativeInvoker
	{
	public:
		explicit NativeInvoker();
		~NativeInvoker();

		template <typename T>
		T get_class(std::string name);
		UFunction* get_native(std::string_view name);
		UFunction* get_native(uint32_t name);
		static void execute_native_function(std::string className, std::string functionName, void* parameters);
		static void execute_native_function(UClass* classInstance, std::string functionName, void* parameters);
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
		UFunction* m_set_health;
		UFunction* m_server_set_character_level;
		UFunction* m_set_character_level;
		UFunction* m_server_set_location_and_rotation;
		UFunction* m_server_kick_player;
		UFunction* m_set_energy;
		UFunction* m_set_mana;
		UFunction* m_get_max_mana;
		UFunction* m_get_mana;
		UFunction* m_client_set_auto_combat;
		UFunction* m_k2_set_actor_location_and_rotation;
		UFunction* m_k2_set_actor_location;
		UFunction* m_k2_teleport_to;
		UFunction* m_k2_add_relative_location;
		UFunction* m_k2_add_local_offset;
		UFunction* m_k2_set_actor_relative_location;
		UFunction* m_k2_get_root_component;
		UFunction* m_get_forward_vector;
		UFunction* m_k2_on_reset;
		UFunction* m_server_set_rotation;
		UFunction* m_client_set_rotation;
		UFunction* m_server_require_big_secret;
	public:
		UClass* m_kismet_text_library;
	public:
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
		SetHP m_set_health_params{};
		ServerSetCharacterLevel m_server_set_character_level_params{};
		SetCharacterLevel m_set_character_level_params{};
		ServerSetLocationAndRotation m_server_set_location_and_rotation_params{};
	private:
		inline static UFunction* m_function;
		inline static UClass* m_class;
	};

	inline NativeInvoker* g_native_invoker;
}