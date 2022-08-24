#pragma once
#include <pointers.hpp>
#include "class/world.hpp"

namespace big::unreal_engine
{
	inline Player* get_local_player()
	{
		if (auto world = *g_pointers->m_world)
		{
			if (auto game_instance = world->m_game_instance)
			{
				if (auto local_player = game_instance->m_local_player)
				{
					if (auto player = local_player->m_player[0])
					{
						return player;
					}
				}
			}
		}

		return nullptr;
	}

	inline PlayerNavigation* get_player_pos()
	{
		if (auto navigation = *g_pointers->m_player_nav)
		{
			if (auto get_coords = navigation->m_get_navigation)
			{
				if (auto pos = get_coords->m_player_navigation)
				{
					return pos;
				}
			}
		}

		return nullptr;
	}

	inline bool game_state()
	{
		if (auto world = *g_pointers->m_world)
		{
			if (auto game_state = world->m_game_state)
			{
				if (auto state = game_state->m_game_state)
				{
					return state != 0;
				}
			}
		}

		return false;
	}

	inline Vector3 world_to_screen(Vector3 location)
	{

	}

	inline std::string get_name(int key)
	{
		uint32_t chunk_offset = uint32_t((int)key >> 16);
		auto name_offset = (unsigned short)key;

		auto name_pool_chunk = g_pointers->m_name[chunk_offset + 2];
		auto entry_offset = name_pool_chunk + (ULONG)(2 * name_offset);

		return std::string((char*)((uintptr_t)entry_offset + 2));
	}

	inline Vector3 get_entity()
	{
		auto level_array = (*g_pointers->m_world)->m_level;
		auto level_size = (*g_pointers->m_world)->m_level_size;

		for (int j = 0; j < level_size; j++)
		{
			auto level_data = level_array->m_level_array[j];
			if (level_data == nullptr) continue;

			auto actor_array = level_data->m_actor;
			auto actor_size = level_data->m_actor_count;

			for (int i = 0; i < actor_size; i++)
			{
				auto actor = actor_array->m_actor_array[i];
				if (actor == nullptr) continue;

				if (int id = actor->m_name_index)
				{
					auto name = get_name(id);
					if (name.find("Scene_Box_Refresh_Wild_") != std::string::npos ||
						name.find("BP_Harvest_Gem_") != std::string::npos ||
						name.find("Box_OnlyOnce_") != std::string::npos
						)
					{
						g_logger->info(name.c_str());
						if (auto root_component = actor->m_root_component)
						{
							auto pos = root_component->m_relative_location;

						}
					}
				}
			}
		}
	}
}