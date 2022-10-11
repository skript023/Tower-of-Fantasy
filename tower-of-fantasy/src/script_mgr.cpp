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

	template <typename F, typename ...Args>
	void script_mgr::execute_as_script(F&& callback, Args &&...args)
	{
		std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);
	}

	void script_mgr::tick()
	{
		execute_as_script(std::mem_fn(&script_mgr::tick_internal), this);
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
