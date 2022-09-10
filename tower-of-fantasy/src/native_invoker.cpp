#include "native_invoker.hpp"
#include "utility/unreal_engine_utility.hpp"

namespace big
{
	NativeInvoker::NativeInvoker():
		m_world_to_screen(UObject::find_object<UFunction*>("Function Engine.PlayerController.ProjectWorldLocationToScreen")),
		m_server_quest_update_progress(UObject::find_object<UFunction*>("Function HottaFramework.HottaPlayerCharacter.ServerQuestUpdateProgress")),
		m_server_buy_gha_integral(UObject::find_object<UFunction*>("Function HottaFramework.HottaPlayerCharacter.ServerBuyGHAIntegral")),
		m_server_projectile_actor_hit(UObject::find_object<UFunction*>("Function HottaFramework.MagicHandProjectile.Server_ProjectileActorHit")),
		m_server_projectile_actor(UObject::find_object<UFunction*>("Function HottaFramework.ProjectileBase.Server_ProjectileActorHit")),
		m_server_match_solo_league(UObject::find_object<UFunction*>("Function QRSL.QRSLPlayerCharacter.Server_MatchSoloLeague")),
		m_server_spawn_projectile(UObject::find_object<UFunction*>("Function HottaFramework.HottaSkillSystemComponent.ServerSpawnProjectile"))
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

}