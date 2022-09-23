#include "hooking.hpp"
#include "script.hpp"

namespace big
{
	void hooks::draw_transition(class UCanvas* canvas)
	{
		TRY_CLAUSE
		{

			g_hooking->m_client_viewport_hook.get_original<decltype(&draw_transition)>(hooks::draw_transition_index)(canvas);
		} EXCEPT_CLAUSE
	}

	void hooks::post_render(class ViewportClient* UGameViewportClient, class UCanvas* canvas)
	{
		TRY_CLAUSE
		{

			g_hooking->m_client_viewport_hook.get_original<decltype(&post_render)>(hooks::post_render_index)(UGameViewportClient, canvas);
		} EXCEPT_CLAUSE
	}
}