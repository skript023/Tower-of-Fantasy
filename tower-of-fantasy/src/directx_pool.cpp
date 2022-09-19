#include "directx_pool.hpp"

namespace big
{
    directx_pool::directx_pool()
    {
        g_directx_pool = this;
    }

    directx_pool::~directx_pool()
    {
        g_directx_pool = nullptr;
    }

    void directx_pool::push(std::function<void()> jobs)
    {
        if (jobs)
		{
			std::lock_guard lock(m_mutex);
			m_job_stack.push(std::move(jobs));
		}
    }

    void directx_pool::directx_tick()
    {
        std::unique_lock lock(m_mutex);
		if (!m_job_stack.empty())
		{
			auto job = std::move(m_job_stack.top());
            m_job_stack.pop();
			lock.unlock();

			std::invoke(std::move(job));
		}
    }
}