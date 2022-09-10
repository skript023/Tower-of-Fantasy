#pragma once

namespace big
{
	class thread_pool
	{
		std::atomic<bool> m_accept_jobs;
		std::condition_variable m_data_condition;

		std::stack<std::function<void()>> m_job_stack;
		std::mutex m_lock;
		std::vector<std::thread> m_thread_pool;

		std::thread m_managing_thread;

		std::mutex m_main_lock;
		std::condition_variable m_condition{};
	public:
		thread_pool();
		~thread_pool();

		void destroy();
		void push(std::function<void()> func);
	public:
		void hold();
	private:
		void create();
		void done();
		void run();
	};

	inline thread_pool* g_thread_pool{};
}
