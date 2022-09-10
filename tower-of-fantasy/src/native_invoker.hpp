#pragma once
#include "class/fwddec.hpp"
#include "class/vector.hpp"

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
		int64_t m_quest_id;
		int64_t m_objective_id;
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

	class NativeInvoker
	{
	public:
		explicit NativeInvoker();
		~NativeInvoker();

		UFunction* get_native(std::string name);
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
	public:
		WorldToScreenParam m_world_to_screen_param{};
		ServerQuestUpdateProgress m_server_quest_update_progress_param{};
		ServerBuyGHAIntegral m_server_buy_gha_integral_params{};
		Server_MatchSoloLeague m_server_match_solo_league_params{};
		TeleportWithLoading m_teleport_with_loading_params{};
	};

	inline NativeInvoker* g_native_invoker;
}