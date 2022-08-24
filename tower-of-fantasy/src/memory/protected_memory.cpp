#include "protected_memory.hpp"

namespace big
{
	protected_memory::protected_memory(std::string name, void* target) : m_name(name), m_target(target)
	{
		
	}

	void protected_memory::enable()
	{
		if (VirtualProtect(m_target, sizeof(m_target) * 2, PAGE_EXECUTE_READWRITE, &m_original))
		{
			g_logger->file("Virtual protect at '%X' changed to PAGE_EXCECUTE_READWRITE", reinterpret_cast<std::uintptr_t>(m_target));
		}
		else
		{
			throw std::runtime_error(std::format("Failed to change virtual protect '{}' at 0x{:X}", m_name, reinterpret_cast<std::uintptr_t>(m_target)));
		}
	}

	void protected_memory::disable()
	{
		if (m_target)
		{
			VirtualProtect(m_target, sizeof(m_target) * 2, m_original, &m_disable_original);
		}

		g_logger->file("Restore original '%s'.", m_name.c_str());
	}
}