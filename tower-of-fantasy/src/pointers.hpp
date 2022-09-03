#pragma once
#include "common.hpp"
#include "function_types.hpp"
#include "class/fwddec.hpp"
#include "class/vector.hpp"

namespace big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};
		DWORD64 m_base_address;
		void* m_swapchain_methods[19];

		GWorld** m_world{};
		Player** m_player{};
		TUObjectArray* m_object{};
		FUObjectArray* m_object_array{};
		FNamePool* m_name{};

		uintptr_t** m_view_matrix{};
		Navigation** m_player_nav{};
		functions::process_event_t m_process_event{};

		iVector2* m_screen{};

		uint8_t* m_cooldown;
		uint8_t* m_rapid_attack;
		uint8_t* m_skip_button;
		PVOID m_player_navigation;
		PVOID m_task_queue;

		functions::get_bone_matrix_t m_get_bone_matrix{};
	private:
		bool get_swapchain();
		bool directx_11();
		bool directx_12();
		bool swapchain_found = false;
		HWND m_window;
		IDXGISwapChain* m_swapchain;
		ID3D11Device* m_d3d_device;
		ID3D11DeviceContext* m_d3d_context;
		DWORD flags;
	};

	inline pointers *g_pointers{};
}
