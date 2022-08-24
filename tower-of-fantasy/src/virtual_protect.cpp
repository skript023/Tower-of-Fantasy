#include "virtual_protect.hpp"
#include "pointers.hpp"

namespace big
{
	virtual_protect::virtual_protect() : 
		m_rapid_attack_protect("Rapid Attack", g_pointers->m_rapid_attack),
		m_cooldown_protect("No Cooldown", g_pointers->m_cooldown)
	{
		g_virtual_protect = this;
	}

	virtual_protect::~virtual_protect()
	{
		if (m_enable)
			disable();

		g_virtual_protect = nullptr;
	}

	void virtual_protect::enable()
	{
		m_rapid_attack_protect.enable();
		m_cooldown_protect.enable();

		m_enable = true;
	}

	void virtual_protect::disable()
	{
		m_rapid_attack_protect.disable();
		m_cooldown_protect.disable();
	}
}