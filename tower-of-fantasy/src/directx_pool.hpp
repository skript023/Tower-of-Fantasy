#pragma once

namespace big
{
    class directx_pool
    {
    public:
        explicit directx_pool();
        ~directx_pool();

        void push(std::function<void()> jobs);
        void directx_tick();
    private:
        std::mutex m_mutex;
        std::stack<std::function<void()>> m_job_stack;
    };

    inline directx_pool* g_directx_pool{};
}