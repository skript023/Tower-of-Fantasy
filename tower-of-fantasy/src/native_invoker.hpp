#pragma once
#include "class/fwddec.hpp"
#include "class/vector.hpp"

namespace big
{
	struct WorldToScreenParam
	{
		Vector3 world_location;
		Vector2 screen_location;
		bool m_viewport_relative;
		bool m_return;
	};

	struct ServerQuestUpdateProgress
	{
		std::string quest_id;
		std::string objective_id;
		int progress;
		bool is_add;
	};

	struct ServerBuyGHAIntegral
	{
		int currency_type;
	};

	class NativeInvoker
	{
	public:
		explicit NativeInvoker();
		~NativeInvoker();

	public:
		UFunction* m_world_to_screen;
		UFunction* m_server_quest_update_progress;
		UFunction* m_server_buy_gha_integral;
		UFunction* m_server_projectile_actor_hit;
		UFunction* m_server_projectile_actor;
	public:
		WorldToScreenParam m_world_to_screen_param{};
		ServerQuestUpdateProgress m_server_quest_update_progress_param{};
		ServerBuyGHAIntegral m_server_buy_gha_integral_params{};
	};

	inline NativeInvoker* g_native_invoker;
}