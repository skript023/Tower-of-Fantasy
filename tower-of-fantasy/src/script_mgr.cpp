#include "common.hpp"
#include "pointers.hpp"
#include "script_mgr.hpp"
#include "class/uobject.hpp"

namespace big
{
	void script_mgr::add_script(std::unique_ptr<script> script)
	{
		std::lock_guard lock(m_mutex);
		m_scripts.push_back(std::move(script));
	}

	void script_mgr::remove_all_scripts()
	{
		std::lock_guard lock(m_mutex);
		m_scripts.clear();
	}

	void script_mgr::tick()
	{
		std::invoke(std::mem_fn(&script_mgr::tick_internal), this);
	}

	void script_mgr::get_function(UObject* _this)
	{
		if (this->m_crossmap.size() <= 2162688)
		{
			this->m_crossmap.push_back({ _this->get_fullname(), _this });
		}
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);

		std::lock_guard lock(m_mutex);
		for (auto const &script : m_scripts)
		{
			script->tick();
		}
	}
}
