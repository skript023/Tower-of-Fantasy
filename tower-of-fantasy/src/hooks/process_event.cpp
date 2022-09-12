#include "hooking.hpp"
#include "native_invoker.hpp"
#include <script_mgr.hpp>
#include <class/uobject.hpp>
#include <class/vector.hpp>
#include "utility/services/all.hpp"
#include <utility/ecryption.h>
#include "utility/joaat.hpp"

namespace big
{
	void APIENTRY hooks::process_event(UObject* _this, UFunction* function, void* parms)
	{
		if (g_running)
		{
			switch (rage::joaat(function->get_name()))
			{
				case RAGE_JOAAT("ClientSetTreasureOpened"):
				{
					if (g_settings->player.reset_box)
					{
						auto params = static_cast<ClientSetTreasureOpened*>(parms);

						if (!g_native_invoker->m_server_reset_treasure_box)
							g_native_invoker->m_server_reset_treasure_box = g_native_invoker->get_native("Function HottaFramework.HottaPlayerStatusComponent.ServerResetTreasureBox");

						g_native_invoker->m_server_reset_treasure_box_params.m_static = params->m_static;
						g_native_invoker->m_server_reset_treasure_box_params.m_treasure_box_id = params->m_treasure_box_id;
						g_notification_service->success(xorstr("Ellohim Reset Chest"), std::format("{} Chest Successully Reset", params->m_treasure_box_id.get_name()));

						return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, g_native_invoker->m_server_reset_treasure_box, &g_native_invoker->m_server_reset_treasure_box_params);
					}
					break;
				}
				case RAGE_JOAAT("ServerRecordAbnormalJumpSectionData"):
				{
					auto params = static_cast<ServerRecordAbnormalJumpSectionData*>(parms);

					g_notification_service->success(xorstr("Server Record Abnormal Jump Section Data"), std::format("Your action detected by anti-cheat -> Data Info : {} Comment Info : {} Type : {}", params->m_collect_info, params->m_comment2, params->m_anti_type));
					
					break;
				}
				case RAGE_JOAAT("Server_ProjectileActorHit"):
				{
					if (g_settings->player.rapid_shoot)
					{
						for (int i = 0; i <= 100; i++)
						{
							g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
						}
					}
					break;
				}
				case RAGE_JOAAT("ServerCheckQuestRpcRequire"):
				{
					auto params = static_cast<ServerCheckQuestRpcRequire*>(parms);

					g_logger->info("Quest ID : %s Object ID : %s", params->m_quest_id.get_name().c_str(), params->m_objective_id.get_name().c_str());
					break;
				}
				case RAGE_JOAAT("ClientUpdateAccumulateCurrencyArraySingle"):
				{
					auto params = static_cast<ClientUpdateAccumulateCurrencyArraySingle*>(parms);

					if (params->m_amount < 0)
					{
						params->m_amount = 0;
					}

					if (params->m_currency_type == EHottaCurrencyType::FakeDiamond)
					{
						if (params->m_amount < 0)
						{
							params->m_currency_type = EHottaCurrencyType::Gold;
						}
					}

					g_notification_service->success(xorstr("Ellohim Currency"), std::format("Currency Successullfy Accumulated {}", params->m_amount));

					break;
				}
				case RAGE_JOAAT("ClientOnCurrencyAmountChanged"):
				{
					auto params = static_cast<ClientOnCurrencyAmountChanged*>(parms);

					if (params->m_add_amount < 0)
					{
						params->m_add_amount = 0;
					}

					if (params->m_currency_type == EHottaCurrencyType::FakeDiamond)
					{
						if (params->m_add_amount < 0)
						{
							params->m_currency_type = EHottaCurrencyType::Gold;
						}
					}

					g_notification_service->success(xorstr("Ellohim Currency"), std::format("Currency Successullfy Added {}", params->m_add_amount));

					break;
				}
				case RAGE_JOAAT("ServerUpgradeItem"):
				{
					auto params = static_cast<ServerUpgradeItem*>(parms);
					g_notification_service->success(xorstr("Ellohim Item Upgrade"), std::format("Item Upgrade {} Successfully {}", params->m_target_id.get_name(), params->m_target_count));
					break;
				}
			}
		}

		return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
	}
}