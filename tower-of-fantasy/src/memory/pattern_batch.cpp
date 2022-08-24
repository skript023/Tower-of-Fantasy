#include "../common.hpp"
#include "../logger.hpp"
#include "pattern_batch.hpp"
#include "range.hpp"

namespace memory
{
	using namespace big;

	void pattern_batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
	{
		m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
	}

	void pattern_batch::run(range region)
	{
		bool all_found = true;
		for (auto& entry : m_entries)
		{
			if (auto result = region.scan(entry.m_pattern))
			{
				if (entry.m_callback)
				{
					std::invoke(std::move(entry.m_callback), result);
					g_logger->file("Found '%s' QRSL.exe + %X", entry.m_name.c_str(), result.as<DWORD64>() - region.begin().as<DWORD64>());
				}
				else
				{
					all_found = false;
					g_logger->error("Failed to find '%s'.", entry.m_name.c_str());
				}
			}
			else
			{
				all_found = false;
				g_logger->error("Failed to find '%s'.", entry.m_name.c_str());
			}
		}

		m_entries.clear();
		if (!all_found)
		{
			throw std::runtime_error("Failed to find some patterns.");
		}
	}
}
