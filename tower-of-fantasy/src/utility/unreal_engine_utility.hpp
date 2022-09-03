#pragma once
#include <pointers.hpp>
#include "class/world.hpp"
#include "class/fname_pool.hpp"

namespace big::unreal_engine
{
	inline LocalPlayer* get_local_player()
	{
		if (auto world = *g_pointers->m_world)
		{
			if (auto game_instance = world->m_game_instance)
			{
				if (auto local_player = game_instance->m_local_player[0])
				{
					return local_player;
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

	inline bool world_state()
	{
		if (auto world = *g_pointers->m_world)
		{
			if (auto game_state = world->m_game_state)
			{
				if (auto state = game_state->m_game_state)
				{
					return state == 8;
				}
			}
		}

		return false;
	}

	inline bool project_world_to_screen(Vector3 location, Vector2& screen_location, bool bPlayerViewportRelative = false)
	{
		static auto fn = UObject::find_object_by_index<UObject*>(9589);
		struct {
			Vector3 world_location;
			Vector2 screen_location;
			bool bPlayerViewportRelative;
			bool ReturnValue;
		} parms;
		parms = { location, screen_location, bPlayerViewportRelative};
		fn->process_event(fn, &parms);
		g_logger->info("Locations %f Relative Location %f", parms.screen_location.x, parms.world_location.x);
		screen_location = parms.screen_location;
		return parms.ReturnValue;
	}

	inline std::string get_name(int key)
	{
		if (!g_pointers->m_name->m_entry_allocator.is_valid_index(key))
		{
			g_logger->warning("key is invalid");
			return "";
		}

		auto fname_entry = g_pointers->m_name->m_entry_allocator.get_by_id(key);
		auto ret = fname_entry.get_ansi_name();
		return ret;
	}

	inline uintptr_t read_pointer(uintptr_t base_address, std::vector<DWORD> offsets)
	{
		uintptr_t ptr = *(uintptr_t*)(base_address);
		if (!ptr)
		{

			return NULL;
		}
		auto level = offsets.size();

		for (auto i = 0; i < level; i++)
		{
			if (i == level - 1)
			{
				ptr += offsets[i];
				if (!ptr) return NULL;
				return ptr;
			}
			else
			{
				ptr = *(uint64_t*)(ptr + offsets[i]);
				if (!ptr) return NULL;
			}
		}

		return ptr;
	}
}