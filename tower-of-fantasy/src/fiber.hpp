#pragma once

namespace big
{
	class fiber
	{
	public:
		void fiber_on_tick();
		static void fiber_func();
	};

	inline fiber g_fiber{};
}