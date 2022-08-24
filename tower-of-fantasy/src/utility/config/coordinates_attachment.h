#pragma once
#include <class/vector.hpp>

namespace big
{
	static void to_json(nlohmann::json& j, const Vector3& attachment) 
	{
		j = nlohmann::json{ 
			{"position_x", attachment.x}, 
			{"position_y", attachment.y}, 
			{"position_z", attachment.z},
		};
	}

	static void from_json(const nlohmann::json& j, Vector3& attachment) 
	{
		j.at("position_x").get_to(attachment.x); 
		j.at("position_y").get_to(attachment.y); 
		j.at("position_z").get_to(attachment.z);
	}
}