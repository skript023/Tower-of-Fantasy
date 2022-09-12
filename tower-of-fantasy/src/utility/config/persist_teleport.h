#pragma once
#include "coordinates_attachment.h"

namespace big
{
	class persist_teleport
	{
	public:
		static void load_location_with_loading(std::string name);

		static void load_location(std::string name);

		static void delete_location(std::string name);

		static std::vector<std::string> list_locations();

		static void save_location(Vector3 position, std::string name);

		static void save(Vector3 attachment, std::string name);

		static void save_json(nlohmann::json json);

		static nlohmann::json get_locations_json();

		static std::filesystem::path get_locations_config();

	};
}