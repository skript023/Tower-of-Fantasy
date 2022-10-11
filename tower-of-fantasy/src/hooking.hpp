#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
#include "vmt_hook.hpp"
#include "class/uobject.hpp"

namespace big
{
	struct hooks
	{
		static constexpr auto swapchain_num_funcs = 19;
		static constexpr auto swapchain_present_index = 8;
		static constexpr auto swapchain_draw_indexed_index = 12;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static constexpr auto viewport_num_funcs = 150;
		static constexpr auto post_render_index = 98;
		static constexpr auto draw_transition_index = 99;
		static HRESULT APIENTRY swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags);
		static HRESULT APIENTRY swapchain_resizebuffers(IDXGISwapChain *this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);
		static void APIENTRY swapchain_draw_indexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		static BOOL set_cursor_pos(int x, int y);
		static void* convert_thread_to_fiber(void* param);

		static void APIENTRY process_event(UObject* _this, UFunction* function, void* parms);
		static __int64 __fastcall evasion_handler(EvadeBeanParam* a1);
		static __int64 __fastcall attack_range(__int64 a1, __int64 a2, __int64 a3);
		static int8_t __fastcall fast_attack(__int64 a1, float* a2, signed __int64* a3);
		static bool __fastcall crash_report(uint16_t* a1, wchar_t* a2);

		static void post_render(class GameViewport* _this, class UCanvas* canvas);
		static void draw_transition(class GameViewport* _this, class UCanvas* canvas);
	};

	struct minhook_keepalive
	{
		minhook_keepalive();
		~minhook_keepalive();
	};

	class hooking
	{
		friend hooks;
	public:
		explicit hooking();
		~hooking();

		void enable();
		void disable();
	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		WNDPROC m_og_wndproc;

		detour_hook m_convert_thread_to_fiber_hook;
		detour_hook m_swapchain_present_hook;
		detour_hook m_swapchain_resizebuffers_hook;
		detour_hook m_set_cursor_pos_hook;
		detour_hook m_process_event_hook;
		detour_hook m_evasion_handler_hook;
		detour_hook m_rapid_attack_hook;
	};

	inline hooking *g_hooking{};
}
