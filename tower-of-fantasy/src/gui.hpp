#pragma once
#include "common.hpp"
#include "class/vector.hpp"

namespace big
{
	class gui
	{
	public:
		void dx_init();
		void dx_on_tick();

		void script_init();
		void script_on_tick();
		static void script_func();
	public:
		bool m_opened{};
		std::map<std::string, Vector3> m_entity_list{};
	private:
		void get_entity();
		void script_on_tick_timed();
	};

	inline gui g_gui;
}
