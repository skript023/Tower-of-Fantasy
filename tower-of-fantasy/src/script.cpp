#pragma once
#include "common.hpp"
#include "logger.hpp"
#include "script.hpp"

namespace big
{
	void script::script_exception_handler(PEXCEPTION_POINTERS exp)
	{
		g_logger->warning("Script Got Exception");
		g_stackwalker.ShowCallstack(GetCurrentThread(), exp->ContextRecord);
	}

	script::script(func_t func, std::optional<std::size_t> stack_size) :
		m_func(func),
		m_script_fiber(nullptr),
		m_main_fiber(nullptr)
	{
		m_script_fiber = CreateFiber(stack_size.has_value() ? stack_size.value() : 0, [](void* param)
		{
			auto this_script = static_cast<script*>(param);
			this_script->fiber_func();
		}, this);
	}

	script::~script()
	{
		if (m_script_fiber)
			DeleteFiber(m_script_fiber);
	}

	void script::tick()
	{
		m_main_fiber = GetCurrentFiber();
		if (!m_wake_time.has_value() || m_wake_time.value() <= std::chrono::high_resolution_clock::now())
		{
			SwitchToFiber(m_script_fiber);
		}
	}

	void script::yield(std::optional<std::chrono::high_resolution_clock::duration> time)
	{
		if (time.has_value())
		{
			m_wake_time = std::chrono::high_resolution_clock::now() + time.value();
		}
		else
		{
			m_wake_time = std::nullopt;
		}

		SwitchToFiber(m_main_fiber);
	}

	script* script::get_current()
	{
		return static_cast<script*>(GetFiberData());
	}

	void script::fiber_func()
	{
		TRY_CLAUSE
		{
			m_func();
		}
			EXCEPT_CLAUSE

			[]() {
			g_logger->info("Script finished!");
		}();

		while (true)
		{
			yield();
		}
	}
}
