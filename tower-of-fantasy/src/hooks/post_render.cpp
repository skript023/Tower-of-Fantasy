#include "hooking.hpp"
#include "script.hpp"

namespace big
{
	void hooks::post_render(class ViewportClient* UGameViewportClient, class UCanvas* canvas)
	{
		g_logger->info("Post render hooked");

		//return g_hooking->m_post_render_hook.get_original<decltype(&post_render)>(hooks::post_render_index)(UGameViewportClient, canvas);
	}
}