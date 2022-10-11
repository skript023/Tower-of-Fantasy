#pragma once
#include "common.hpp"
#include "function_types.hpp"
#include "class/fwddec.hpp"
#include "class/vector.hpp"

namespace big
{
	using d3d11_create_device_t = HRESULT(__stdcall*)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*, UINT, UINT, const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
	
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};
		uintptr_t m_base_address;
		void* m_swapchain_methods[19];

		GWorld** m_world{};
		Player** m_player{};
		TUObjectArray* m_object{};
		FUObjectArray* m_object_array{};
		FNamePool* m_name{};
		Engine** m_engine{};

		uintptr_t** m_view_matrix{};
		Navigation** m_player_nav{};
		functions::process_event_t m_process_event{};
		functions::ftext_to_fstring_t m_text_to_string{};
		functions::fname_t m_fname{};

		iVector2* m_screen{};

		uint8_t* m_cooldown;
		uint8_t* m_skip_button;
		float* xmmword_7FF67F73A040;
		void* m_ssr_stuff;
		PVOID m_player_navigation;
		PVOID m_task_queue;
		PVOID m_evasion_handler;
		PVOID m_attack_range;
		PVOID m_rapid_attack;
		PVOID dword_7FF681753804;
		PVOID m_crash_report;
		functions::get_bone_matrix_t m_get_bone_matrix{};
	private:
		bool get_swapchain();
		bool m_get_swapchain;
		bool directx_11();
		HWND m_window;
		IDXGISwapChain* m_swapchain;
		ID3D11Device* m_d3d_device;
		ID3D11DeviceContext* m_d3d_context;
		DWORD flags;
	private:
		bool directx_12();
		ID3D12Device* m_d3d12_device;
		ID3D12CommandQueue* m_command_queue;
		ID3D12CommandAllocator* m_command_allocator;
		ID3D12GraphicsCommandList* m_command_list;
		void* m_command_queue_methods[20];
		void* m_command_list_methods[61];
		void* m_command_allocator_methods[10];
		void* m_d3d12_device_methods[45];
	};

	inline pointers *g_pointers{};
}
