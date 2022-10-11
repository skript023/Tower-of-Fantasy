#pragma once
#include "common.hpp"

namespace big
{
	class player_menu
	{
	public:
		static void render_menu();
	private:
		inline static float m_exp_multiplier{};
		inline static int selected_bygon_level{ 0 };
		inline static const char* const bygon_level[]{ "Select Level", "Level 1","Level 2","Level 3","Level 4","Level 5","Level 6","Level 7","Level 8","Level 9","Level 10","Level 11","Level 12","Level 13","Level 14","Level 15","Level 16","Level 17","Level 18","Level 19","Level 20","Level 21","Level 22","Level 23","Level 24","Level 25","Level 26","Level 27","Level 28","Level 29","Level 20","Level 30"};
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