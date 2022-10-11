#pragma once
#include "common.hpp"
#include "script.hpp"
#include "class/fwddec.hpp"

namespace big
{
	class script_mgr
	{
	public:
		explicit script_mgr() = default;
		~script_mgr() = default;

		void add_script(std::unique_ptr<script> script);
		void remove_all_scripts();
		template <typename F, typename ...Args>
		void execute_as_script(F&& callback, Args &&...args);
		
		void tick();
	private:
		void tick_internal();
	private:
		std::recursive_mutex m_mutex;
		std::vector<std::unique_ptr<script>> m_scripts;
	public:
		struct NativeFunction 
		{ 
			std::string name; 
			UObject* object; 
		};
		std::vector<NativeFunction> m_crossmap;
		
	};

	inline script_mgr g_script_mgr;
}
