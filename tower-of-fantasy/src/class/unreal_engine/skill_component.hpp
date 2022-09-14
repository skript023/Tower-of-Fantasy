#pragma once
#include "../fwddec.hpp"
#include "native_invoker.hpp"

namespace big
{
	#pragma pack(push, 1)

	class SkillComponent : public UObject
	{
	public:
		char pad_0028[0xD40];
		int m_weapon_selected_index; //0x0D68
		char pad_0D6C[2196]; //0x0D6C
		int m_weapon_type; //0x1600
		float m_max_health; //0x1604
		float m_max_energy; //0x1608
		float m_pysical_attack; //0x160C
		float m_fire_attack; //0x1610
		float m_thunder_attack; //0x1614
		float m_ice_attack; //0x1618
		float m_super_power_atk; //0x161C
		float m_pysical_deff; //0x1620
		float m_fire_deff; //0x1624
		float m_thunder_deff; //0x1628
		float m_ice_deff; //0x162C
		float m_super_power_deff; //0x1630
		float m_critical; //0x1634
		float m_critical_deff; //0x1638
		char pad_163C[0x8]; //0x163C
		float m_mount_speed; //0x1644
		float m_health; //0x1648
		char pad_164C[0x4];
		float m_energy; //0x1650
		float psycal_def_ignore; //0x1654
		float ice_def_ignore; //0x1658
		float fire_def_ignore; //0x165C
		float thunder_def_ignore; //0x1660
		float super_power_def_ignore; //0x1664
		float m_critical_damage; //0x1668 
		float m_energy_recovery; //0x166C
		char pad_1670[0x40]; //0x1670
		float m_critical_rate; //0x16B0

	public:
		void spawn_artifac_arrow(float duration)
		{
			if (!g_native_invoker->m_spawn_artifact_arrow)
				g_native_invoker->m_spawn_artifact_arrow = g_native_invoker->get_native("Function HottaFramework.HottaSkillSystemComponent.SpawnArtifactArrow");

			g_native_invoker->m_spawn_artifact_arrow_params.m_duration_time = duration;

			process_event(g_native_invoker->m_spawn_artifact_arrow, &g_native_invoker->m_spawn_artifact_arrow_params);
		}
	};
	static_assert(sizeof(SkillComponent) == 0x16B4);

	#pragma pack(pop)
}