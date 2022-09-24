#include "hooking.hpp"
#include "utility/services/all.hpp"
#include <utility/ecryption.h>

namespace big
{
	bool hooks::crash_report(uint16_t* a1, wchar_t* a2)
	{
		FString call(a2);
		g_notification_service->warning(xorstr("Crash Report"), call.to_string());

		return g_hooking->m_crash_report_hook.get_original<decltype(&crash_report)>()(a1, a2);
	}
}