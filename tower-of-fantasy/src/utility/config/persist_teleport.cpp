#include "persist_teleport.h"
#include "utility/features/all.hpp"

namespace big
{
    void persist_teleport::load_location(std::string name)
    {
        auto locations = get_locations_json();
        if (locations[name].is_null())
            return;

        auto model_attachment = locations[name].get<Vector3>();

        if (auto self = unreal_engine::get_hotta_character(); self)
        {
            self->teleport_with_loading(model_attachment, Rotator(0, 0, 0));
        }
    }

    void persist_teleport::delete_location(std::string name)
    {
        auto locations = get_locations_json();
        if (locations[name].is_null())
            return;
        locations.erase(name);
        save_json(locations);
    }

    std::vector<std::string> persist_teleport::list_locations()
    {
        std::vector<std::string> return_value;
        auto json = get_locations_json();
        for (auto& item : json.items())
            return_value.push_back(item.key());
        return return_value;
    }

    void persist_teleport::save_location(Vector3 position, std::string name)
    {
        save(position, name);
    }

    void persist_teleport::save(Vector3 attachment, std::string name)
    {
        auto json = get_locations_json();
        json[name] = attachment;
        save_json(json);
    }

    void persist_teleport::save_json(nlohmann::json json)
    {
        auto file_path = get_locations_config();
        std::ofstream file(file_path, std::ios::out | std::ios::trunc);
        file << json.dump(4);
        file.close();
    }

    nlohmann::json persist_teleport::get_locations_json()
    {
        auto file_path = get_locations_config();
        nlohmann::json locations;
        std::ifstream file(file_path);

        if (!file.fail())
            file >> locations;

        return locations;
    }

    std::filesystem::path persist_teleport::get_locations_config()
    {
        auto file_path = std::filesystem::path(std::getenv("appdata"));
        file_path /= ENVIRONMENT;

        if (!std::filesystem::exists(file_path))
        {
            std::filesystem::create_directory(file_path);
        }
        else if (!std::filesystem::is_directory(file_path))
        {
            std::filesystem::remove(file_path);
            std::filesystem::create_directory(file_path);
        }

        file_path /= "Teleport.json";

        return file_path;
    }
}