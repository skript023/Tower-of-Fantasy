#include "fiber.hpp"
#include "script.hpp"
#include "utility/features/all.hpp"

namespace big
{
	void fiber::fiber_on_tick()
	{
		g_features->misc.infinite_energy(g_settings->player.infinite_energy);
		g_features->misc.infinite_mana(g_settings->player.infinite_mana);
	}
	void fiber::fiber_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				g_fiber.fiber_on_tick();
			} 
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}