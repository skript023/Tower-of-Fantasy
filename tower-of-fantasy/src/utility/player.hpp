#pragma once
#include "unreal_engine_utility.hpp"

/*
[D3DRHIPreference]
bPreferD3D12InGame=False

*/

namespace big::player
{
	inline int* player_level()
	{
		if (auto player = unreal_engine::get_local_player())
		{
			return &player->m_player_controller->m_pawn->m_level;
		}

		return nullptr;
	}
}