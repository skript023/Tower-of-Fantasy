#pragma once
#include "common.hpp"

namespace big
{
	class player_menu
	{
	public:
		static void render_menu();
	private:
		static inline float m_exp_multiplier{};
		static inline int selected_method{ 0 };
		static inline const char* const method[]{ "Teleport Standard", "Teleport With Loading" };
	};
}
/*
if (g_settings->player.ssr_stuff)
{
	*g_pointers->m_ssr_stuff = 1;//APawn+0xCC8+0x810 APawn->CurrentWeapon->AWeaponBase : AItemActor.CanUseAutoPickUp
}
else if(!g_settings->player.ssr_stuff)
{
	*g_pointers->m_ssr_stuff = 2064;
}
*/