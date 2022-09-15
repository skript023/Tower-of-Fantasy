#pragma once
#include "player_movement.hpp"
#include "defense_stats.hpp"
#include "attack_stats.hpp"
#include "misc.hpp"
#include "../player.hpp"

namespace big
{
	class Features;
	inline Features* g_features{};

	class Features
	{
	public:
		MiscOption misc{};
		AttackOption attack{};
		DefenseOption defense{};
		MovementOption movement{};

		explicit Features()
		{
			g_features = this;
		}
		~Features()
		{
			g_features = nullptr;
		}
	};
}