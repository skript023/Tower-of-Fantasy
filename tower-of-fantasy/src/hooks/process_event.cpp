#include "hooking.hpp"
#include "native_invoker.hpp"
#include <script_mgr.hpp>
#include <class/uobject.hpp>
#include <class/vector.hpp>
#include "utility/services/all.hpp"
#include <utility/ecryption.h>
#include "utility/joaat.hpp"
#include "renderer.hpp"
#include <utility/features/all.hpp>

namespace big
{
	void APIENTRY hooks::process_event(UObject* _this, UFunction* function, void* parms)
	{
		if (g_running)
		{
			if (g_settings->system.log_process_event)
			{
				g_logger->info("Function name %s Object name %s", function->get_fullname().c_str(), _this->get_fullname().c_str());
			}

			if (function->get_name() == "ReceiveTick" || function->get_name() == "Received_NotifyTick")
			{
				
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
					std::format("Your action suspected as cheater => Data Info : {} Comment Info : {} Type : {}",
						params->m_collect_info,
						params->m_comment2,
						params->m_anti_type));
			}
			if (function->get_name() == "ServerCheckQuestRpcRequire")
			{
				auto params = static_cast<ServerCheckQuestRpcRequire*>(parms);

				g_notification_service->warning(xorstr("Server Side RPC Check"), 
					std::format("Quest ID : {} Objective ID : {}", 
						params->m_quest_id.get_name(), 
						params->m_objective_id.get_name()));
			}
			if (function->get_name() == "ClientOnCurrencyAmountChanged")
			{
				auto params = static_cast<ClientOnCurrencyAmountChanged*>(parms);

				if (params->m_add_amount < 0)
				{
					params->m_add_amount = 1000000;
					params->m_path_type = EHottaOutputPathType::Add_DailyGift;

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

				g_notification_service->success(xorstr("Ellohim Matrix Unequiped"),
					std::format("Matrix unequiped slot index {} successfull contain type {} weapon slot {}",
						(int8_t)params->m_weapon_matrix_slot, (int8_t)params->m_contain_type, params->m_weapon_slot));
			}
			if (function->get_name() == "ServerMatrixEquiped")
			{
				auto params = static_cast<ServerMatrixEquiped*>(parms);

				g_notification_service->success(xorstr("Ellohim Matrix Unequiped"),
					std::format("Matrix unequiped slot index {} successfull contain type {} weapon slot {}",
						(int8_t)params->m_weapon_matrix_slot, (int8_t)params->m_contain_type, params->m_weapon_slot));
			}
			if (function->get_name() == "ServerUpgradeStarLevel")
			{
				auto params = static_cast<ServerUpgradeStarLevel*>(parms);

				g_notification_service->success(xorstr("Ellohim Star Upgrade"),
					std::format("Star upgrade slot index {} successfull contain type {}",
						params->m_choose_item_slot, (int8_t)params->m_contain_type));
			}
			if (function->get_name() == "ServerMatrixUpgradeStar")
			{
				auto params = static_cast<ServerMatrixStrengthen*>(parms);

				g_notification_service->success(xorstr("Ellohim Matrix Star Upgrade"),
					std::format("Matrix star upgrade slot index {} successfull contain type {}",
						params->m_slot_index, (int8_t)params->m_contain_type));

			}
			if (function->get_name() == "ServerMatrixUpgradeStar")
			{
				auto params = static_cast<ServerMatrixStrengthen*>(parms);

				g_notification_service->success(xorstr("Ellohim Matrix Star Upgrade"),
					std::format("Matrix star upgrade slot index {} successfull contain type {}",
						params->m_slot_index, (int8_t)params->m_contain_type));
			}
			if (function->get_name() == "ServerMatrixStrengthen")
			{
				auto params = static_cast<ServerMatrixStrengthen*>(parms);
				ServerMatrixStrengthen new_params{};
				g_notification_service->success(xorstr("Ellohim matrix upgrade"), 
					std::format("Matrix upgrade slot index {} successfull contain type {}",
						params->m_slot_index, (int8_t)params->m_contain_type));

				new_params.m_slot_index = params->m_slot_index;
				new_params.m_contain_type = EItemContainType::ITEMCONTAIN_TYPE_TRADE_BUY;

				g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, &new_params);
			
			}
			if (function->get_name() == "ServerEquipStrengthen")
			{
				g_notification_service->success(xorstr("Ellohim equipment strengthen"), xorstr("Equipment upgrade successfull"));
			}
			if (function->get_name() == "ServerEquipWeapon")
			{
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
			if (function->get_name() == "ServerSetHaveFallDamage")
			{
				auto params = static_cast<ServerSetHaveFallDamage*>(parms);
				params->m_in_have_fall_damage = false;

				g_notification_service->success(xorstr("Ellohim Server Fall Damage"), xorstr("Fall damage has been adjusted succesfully"));

				return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
			}
			if (function->get_name() == "ServerSetHP")
			{
				auto params = static_cast<ServerSetHP*>(parms);

				params->m_health = *g_features->defense.max_health();

				g_notification_service->success(xorstr("Ellohim Player Health"), xorstr("Health has been adjusted succesfully"));

				return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
			}
			if (function->get_name() == "SetHP")
			{
				auto params = static_cast<SetHP*>(parms);

				g_notification_service->success(xorstr("Ellohim Player Health"), xorstr("Health has been adjusted succesfully"));
				return;
			}
			if (function->get_name() == "ServerSetCharacterLevel")
			{
				auto params = static_cast<ServerSetCharacterLevel*>(parms);

				//params->m_level += 5;
				g_notification_service->success(xorstr("Ellohim Level"), xorstr("Level has been adjusted succesfully"));
			}
			if (function->get_name() == "ServerLotteryExtract")
			{
				auto params = static_cast<ServerLotteryExtract*>(parms);

				g_notification_service->success(xorstr("Ellohim Gacha"), std::format("Gacha using {} resource discount {}", params->m_extract_count, params->m_is_discount ? "true" : "false"));
				
			}
			if (function->get_name() == "ServerPickItem")
			{
				auto params = static_cast<ServerPickItem*>(parms);

				params->m_amount = 1000000;
			}
			if (function->get_name() == "ServerOpenTreasureBox")
			{
				auto params = static_cast<ServerOpenTreasureBox*>(parms);

				g_notification_service->success(xorstr("Ellohim Treasure"), std::format("Opening chest {} with {} quality - recover time {} - open time {}", 
					params->m_tresure_id.get_name(), 
					params->m_quality, 
					params->m_recover_time, 
					params->m_open_time));
			}
			if (function->get_name() == "ServerApplyEffectContainerWithTargetDatas")
			{
				g_notification_service->success(xorstr("Ellohim Apply Effect"), xorstr("Effect has been applied succesfully"));
			}
			if (function->get_name() == "ReceivePointDamage")
			{
				auto params = static_cast<ReceivePointDamage*>(parms);
				g_notification_service->success(xorstr("Ellohim Ability"), xorstr("Damage has been received succesfully"));
				//female_player_C
			}
			if (function->get_name() == "ReceiveAnyDamage")
			{
				g_notification_service->success(xorstr("Ellohim Ability"), xorstr("Damage has been received succesfully"));
			}
			if (function->get_name() == "ReceivePointDamage")
			{
				g_notification_service->success(xorstr("Ellohim Ability"), xorstr("Damage has been received succesfully"));
			}
		}

		return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
	}
}