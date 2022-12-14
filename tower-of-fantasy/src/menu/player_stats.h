#pragma once
#include "common.hpp"

namespace big
{
	class player_stat
	{
	public:
		static void render_menu(); 
		static void read();
	private:
		inline static bool critical_hack{ false };
		static inline const float default_move = 500.f;
		static inline const float default_swim = 150.f;
		static inline const float default_crouch = 250.f;
		inline static int level = 0;
		inline static char target[64];
	};
}