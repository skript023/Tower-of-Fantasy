#include "hooking.hpp"
#include "native_invoker.hpp"
#include <script_mgr.hpp>
#include <class/uobject.hpp>
#include <class/vector.hpp>
#include "utility/services/all.hpp"
#include <utility/ecryption.h>
#include "utility/joaat.hpp"
#include "renderer.hpp"

namespace big
{
	void APIENTRY hooks::process_event(UObject* _this, UFunction* function, void* parms)
	{
		if (g_running)
		{
			if (g_settings->system.log_process_event)
			{
				g_logger->info("Function name %s", function->get_fullname().c_str());
			}

			if (function->get_name() == "ReceiveTick")
			{
				g_script_mgr.tick();
			}
			if (function->get_name() == "ClientSetTreasureOpened")
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
			}
			if (function->get_name() == "ServerRecordAbnormalJumpSectionData")
			{
				auto params = static_cast<ServerRecordAbnormalJumpSectionData*>(parms);

				g_notification_service->success(xorstr("Server Record Abnormal Jump Section Data"),
					std::format("Your action suspected as tempering => Data Info : {} Comment Info : {} Type : {}",
						params->m_collect_info,
						params->m_comment2,
						params->m_anti_type));
			}
			if (function->get_name() == "ServerCheckQuestRpcRequire")
			{
				auto params = static_cast<ServerCheckQuestRpcRequire*>(parms);

				g_logger->info("Quest ID : %s Object ID : %s", params->m_quest_id.get_name().c_str(), params->m_objective_id.get_name().c_str());
			}
			if (function->get_name() == "ClientOnCurrencyAmountChanged")
			{
				auto params = static_cast<ClientOnCurrencyAmountChanged*>(parms);

				if (params->m_add_amount < 0)
				{
					params->m_add_amount = 1000000;
					params->m_path_type = EHottaOutputPathType::Add_Rewared;

					g_notification_service->success(xorstr("Ellohim Currency"), xorstr("No currency used"));

					return;
				}

				g_notification_service->success(xorstr("Ellohim Currency"),
					std::format("Currency Successullfy Added {}",
						params->m_add_amount));
			}
			if (function->get_name() == "ServerUpgradeItem")
			{
				auto params = static_cast<ServerUpgradeItem*>(parms);
				g_notification_service->success(xorstr("Ellohim Item Upgrade"),
					std::format("Item Upgrade {} Successfully {}",
						params->m_target_id.get_name(),
						params->m_target_count));

			}
			if (function->get_name() == "ServerMatrixUnequiped")
			{
				auto params = static_cast<ServerMatrixUnequiped*>(parms);
				for (int i = 0; i <= 20; i++)
				{
					g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
				}
				g_notification_service->success(xorstr("Ellohim Matrix Unequiped"),
					std::format("Matrix unequiped slot index {} successfull contain type {} weapon slot {}",
						params->m_matrix_slot, params->m_contain_type, params->m_weapon_slot));
			}
			if (function->get_name() == "ServerUpgradeStarLevel")
			{
				auto params = static_cast<ServerUpgradeStarLevel*>(parms);
				for (int i = 0; i <= 6; i++)
				{
					g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
				}

				g_notification_service->success(xorstr("Ellohim Star Upgrade"),
					std::format("Star upgrade slot index {} successfull contain type {}",
						params->m_choose_item_slot, params->m_contain_type));
			}
			if (function->get_name() == "ServerMatrixUpgradeStar")
			{
				auto params = static_cast<ServerMatrixStrengthen*>(parms);
				for (int i = 0; i <= 6; i++)
				{
					g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
				}
				g_notification_service->success(xorstr("Ellohim Matrix Star Upgrade"),
					std::format("Matrix star upgrade slot index {} successfull contain type {}",
						params->m_slot_index, params->m_contain_type));
			}
			if (function->get_name() == "ServerMatrixUpgradeStar")
			{
				auto params = static_cast<ServerMatrixStrengthen*>(parms);
				for (int i = 0; i <= 6; i++)
				{
					g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
				}
				g_notification_service->success(xorstr("Ellohim Matrix Star Upgrade"),
					std::format("Matrix star upgrade slot index {} successfull contain type {}",
						params->m_slot_index, params->m_contain_type));
			}
			if (function->get_name() == "ServerMatrixStrengthen")
			{
				for (int i = 0; i <= 15; i++)
				{
					g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
				}
				g_notification_service->success(xorstr("Ellohim matrix upgrade"), xorstr("Matrix upgrade successfully multiplied 15 times"));
			}
			if (function->get_name() == "ServerEquipStrengthen")
			{
				for (int i = 0; i <= 10; i++)
				{
					g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
				}
				g_notification_service->success(xorstr("Ellohim equipment strengthen"), xorstr("Weapon upgrade successfull"));
			}
			if (function->get_name() == "ServerEquipWeapon")
			{
				for (int i = 0; i <= 10; i++)
				{
					g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
				}
				g_notification_service->success(xorstr("Ellohim equipment"), xorstr("Weapon equiped succesfully"));
			}
			if (function->get_name() == "ServerRecordExploreProgress")
			{
				auto params = static_cast<ServerRecordExploreProgress*>(parms);
				g_notification_service->success(xorstr("Ellohim Exploration Progress"),
					std::format("Item name {} quantity {}",
						params->m_drop_id.get_name(), params->m_drop_num));

				params->m_drop_num = 10000;
			}
		}

		return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
	}
}