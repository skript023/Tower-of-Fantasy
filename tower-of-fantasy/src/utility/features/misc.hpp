#pragma once
#include "../unreal_engine_utility.hpp"

namespace big
{
	class MiscOption
	{
		struct EntityList
		{
			Vector2 m_position;
			Vector3 m_relative_location;
			std::string name;
		};
		std::vector<EntityList> m_entity_list{};
	public:
		bool* attribute_initialized();
		void skip_button(bool activate);
		void get_entity_list(bool activate);
		void render_esp(bool activate);
	};
}