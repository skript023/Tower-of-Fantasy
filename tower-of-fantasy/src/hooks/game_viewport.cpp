#include "hooking.hpp"
#include "script.hpp"
#include "class/unreal_engine/ucanvas.hpp"

namespace big
{
	void hooks::draw_transition(GameViewport* _this, UCanvas* canvas)
	{
		TRY_CLAUSE
		{

			//return g_hooking->m_client_viewport_hook.get_original<decltype(&draw_transition)>(hooks::draw_transition_index)(_this, canvas);
		} EXCEPT_CLAUSE
	}

	void hooks::post_render(GameViewport* _this, UCanvas* canvas)
	{
		TRY_CLAUSE
		{


			//return g_hooking->m_client_viewport_hook.get_original<decltype(&post_render)>(hooks::post_render_index)(_this, canvas);
		} EXCEPT_CLAUSE
	}
}