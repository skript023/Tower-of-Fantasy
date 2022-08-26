#pragma once
#include "common.hpp"
#include <imgui.h>

namespace big
{
	class renderer
	{
	public:
		explicit renderer();
		~renderer();

		bool m_init = false;
		bool init(IDXGISwapChain* swapchain);
		void imgui_init();

		void on_present();
		void pre_reset();
		void post_reset(IDXGISwapChain* this_);

		void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	private:
		void draw_overlay();
		void render_esp(bool activate);
	public:
		ImFont* m_font;
		ImFont* m_monospace_font;

		HWND m_window = NULL;
	private:
		ID3D11Device* m_d3d_device = nullptr;
		ID3D11DeviceContext* m_d3d_context = nullptr;
		ID3D11RenderTargetView* m_d3d_render_target = nullptr;
		iVector2 m_resolution;
	};

	inline renderer *g_renderer{};
}
