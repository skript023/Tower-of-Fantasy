#include "hooking.hpp"
#include "native_invoker.hpp"
#include <script_mgr.hpp>
#include <class/uobject.hpp>
#include <class/vector.hpp>
#include "utility/services/all.hpp"
#include <utility/ecryption.h>

namespace big
{
	void APIENTRY hooks::process_event(UObject* _this, UFunction* function, void* parms)
	{
		if (g_running)
		{
			if (function->get_name() == "ClientSetTreasureOpened")
			{
				auto params = static_cast<ClientSetTreasureOpened*>(parms);

				auto func = g_native_invoker->get_native_ex("Function HottaFramework.HottaPlayerStatusComponent.ServerResetTreasureBox");

				g_native_invoker->m_server_reset_treasure_box_params.m_static = params->m_static;
				g_native_invoker->m_server_reset_treasure_box_params.m_treasure_box_id = params->m_treasure_box_id;
				g_notification_service->success(xorstr("Ellohim Reset Chest"), xorstr("Chest Successully Reset"));

				return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, func, &g_native_invoker->m_server_reset_treasure_box_params);
			}
		}

		return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
	}
}