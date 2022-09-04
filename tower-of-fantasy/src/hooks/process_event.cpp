#include "hooking.hpp"
#include <script_mgr.hpp>
#include <class/uobject.hpp>
#include <class/vector.hpp>

namespace big
{
	void APIENTRY hooks::process_event(UObject* _this, UFunction* function, void* parms)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{

			}

			return g_hooking->m_process_event_hook.get_original<decltype(&process_event)>()(_this, function, parms);
		} EXCEPT_CLAUSE
	}
}