#include "native_invoker.hpp"
#include "utility/unreal_engine_utility.hpp"

namespace big
{
	NativeInvoker::NativeInvoker():
		m_world_to_screen(get_native("Function Engine.PlayerController.ProjectWorldLocationToScreen")),
		m_server_quest_update_progress(get_native("Function HottaFramework.HottaPlayerCharacter.ServerQuestUpdateProgress")),
		m_server_buy_gha_integral(get_native("Function HottaFramework.HottaPlayerCharacter.ServerBuyGHAIntegral")),
		m_server_projectile_actor_hit(get_native("Function HottaFramework.MagicHandProjectile.Server_ProjectileActorHit")),
		m_server_projectile_actor(get_native("Function HottaFramework.ProjectileBase.Server_ProjectileActorHit")),
		m_server_spawn_projectile(get_native("Function HottaFramework.HottaSkillSystemComponent.ServerSpawnProjectile")),
		m_server_cheat_max_suppressor_level(get_native("Function QRSL.QRSLPlayerCharacter.ServerCheatMaxSuppressorLevel")),
		m_server_match_solo_league(get_native("Function QRSL.QRSLPlayerCharacter.Server_MatchSoloLeague")),
		m_server_change_role_info_sex(get_native("Function QRSL.QRSLPlayerCharacter.ServerChangeRoleInfoSex")),
		m_server_pay_transfer_server_req(get_native("Function QRSL.QRSLPlayerCharacter.Server_PayTransferServerReq")),
		m_server_spawn_extra_equiped_weapon(get_native("Function HottaFramework.HottaPlayerCharacter.ServerSpawnExtraEquipedWeapon")),
		m_server_unlock_avatar(get_native("Function HottaFramework.HottaPlayerCharacter.ServerUnlockAvatar")),
		m_teleport_with_loading(get_native("Function HottaFramework.HottaPlayerCharacter.TeleportWithLoading")),
		m_server_teleport_with_loading(get_native("Function HottaFramework.HottaPlayerCharacter.ServerTeleportWithLoading")),
		m_server_teleport_to(get_native("Function HottaFramework.HottaPlayerCharacter.ServerTeleportTo")),
		m_client_teleport_to(get_native("Function HottaFramework.HottaPlayerCharacter.ClientTeleportTo")),
		m_client_teleport_with_loading(get_native("Function HottaFramework.HottaPlayerCharacter.ClientTeleportWithLoading")),
		m_client_add_tower_energy(get_native("Function HottaFramework.HottaPlayerCharacter.ClientAddTowerEnergy")),
		m_spawn_artifact_arrow(get_native("Function HottaFramework.HottaSkillSystemComponent.SpawnArtifactArrow")),
		m_update_cur_skill_evade_bean_count(get_native("Function HottaFramework.HottaPlayerCharacter.UpdateCurSkillEvadeBeanCount")),
		m_server_reset_treasure_box(get_native("Function HottaFramework.HottaPlayerStatusComponent.ServerResetTreasureBox")),
		m_set_character_exp(get_native("Function HottaFramework.HottaPlayerCharacter.SetCharacterExp")),
		m_server_add_exp(get_native("Function HottaFramework.HottaPlayerCharacter.ServerAddExp"))
	{
		g_native_invoker = this;
	}

	NativeInvoker::~NativeInvoker()
	{
		g_native_invoker = nullptr;
	}

	UFunction* NativeInvoker::get_native(std::string name)
	{
		if (auto function = UObject::find_object<UFunction*>(name); function)
		{
			return function;
		}
		return nullptr;
	}

	UFunction* NativeInvoker::get_native_ex(const char* name)
	{
		if (auto function = UObject::find_object<UFunction*>(std::string(name)); function)
		{
			return function;
		}
		return nullptr;
	}
}