#pragma once
#include "logger.hpp"
#include "imgui.h"
#include <regex>
#include "utility/joaat.hpp"
#include "utility/networking/subprocess.hpp"

namespace big
{
	class settings;
	inline settings* g_settings{};

	class settings {
		nlohmann::json default_options;
		nlohmann::json options;

		struct window
		{
			ImU32 color = 3357612055;
			float gui_scale = 1.f;

			ImFont* font_title;
			ImFont* font_sub_title;
			ImFont* font_normal;
			ImFont* font_small;
			ImFont* font_icon;
		};

		struct system
		{
			int token { g_settings->get_token() };
			bool log_process_event{ false };
		};

		struct player_option
		{
			bool infinite_jump{ false };
			bool godmode{ false };
			bool no_cooldown{ false };
			bool freeze_entity{ false };
			bool no_fall_damage{ false };
			bool freeze_mobs{ false };
			bool infinite_dodge{ false };
			bool cant_jump{ false };
			bool no_clip{ false };
			bool esp{ false };
			bool skip_button{ false };
			bool skateboard{ false };
			bool reset_box{ false };

			float attack_multiplier{ 0.0f };
			float pysical_attack{ 0.0f };

			float critical_rate{ 0.f };
			float critical_base{ 0.f };
			float critical_damage{ 0.f };

			float movement_speed{ 500.f };
			float crouch_speed{ 150.f };
			float swim_speed{ 250.f };
			float gravity{ 2.346999884f };

			int player_level{ 0 };
		};
	public:
		settings()
		{
			g_settings = this;
		}
		~settings()
		{
			g_settings = nullptr;
		}

		player_option player{};
		window window{};
		system system{};

		void from_json(const nlohmann::json& j)
		{
			this->player.godmode = j["player"]["godmode"];
			this->player.infinite_jump = j["player"]["infinite_jump"];
			this->player.attack_multiplier = j["player"]["attack_multiplier"];
			this->player.critical_damage = j["player"]["critical_damage"];
			this->player.movement_speed = j["player"]["movement_speed"];
			this->player.crouch_speed = j["player"]["crouch_speed"];
			this->player.no_cooldown = j["player"]["no_cooldown"];
			this->player.freeze_entity = j["player"]["freeze_entity"];
			this->player.no_fall_damage = j["player"]["no_fall_damage"];
			this->player.player_level = j["player"]["player_level"];
			this->player.swim_speed = j["player"]["swim_speed"];
			this->player.gravity = j["player"]["gravity"];
			this->player.freeze_mobs = j["player"]["freeze_mobs"];
			this->player.infinite_dodge = j["player"]["infinite_dodge"];
			this->player.cant_jump = j["player"]["cant_jump"];
			this->player.no_clip = j["player"]["no_clip"];
			this->player.esp = j["player"]["esp"];
			this->player.skip_button = j["player"]["skip_button"];
			this->player.skateboard = j["player"]["skateboard"];
			this->player.reset_box = j["player"]["reset_box"];

			this->system.token = j["system"]["token"];
			this->system.log_process_event = j["system"]["log_process_event"];
		}

		nlohmann::json to_json()
		{
			return nlohmann::json
			{
				{
					"player", {
						{ "godmode", this->player.godmode },
						{ "infinite_jump", this->player.infinite_jump },
						{ "attack_multiplier", this->player.attack_multiplier },
						{ "critical_damage", this->player.critical_damage },
						{ "movement_speed", this->player.movement_speed },
						{ "crouch_speed", this->player.crouch_speed },
						{ "no_cooldown", this->player.no_cooldown },
						{ "freeze_entity", this->player.freeze_entity },
						{ "no_fall_damage", this->player.no_fall_damage },
						{ "player_level", this->player.player_level },
						{ "swim_speed", this->player.swim_speed },
						{ "gravity", this->player.gravity },
						{ "freeze_mobs", this->player.freeze_mobs },
						{ "infinite_dodge", this->player.infinite_dodge },
						{ "cant_jump", this->player.cant_jump },
						{ "no_clip", this->player.no_clip },
						{ "esp", this->player.esp },
						{ "skip_button", this->player.skip_button },
						{ "skateboard", this->player.skateboard },
						{ "reset_box", this->player.reset_box }
					}
				},
				{
					"system",{
						{ "token", this->system.token},
						{ "log_process_event", this->system.log_process_event }
					}
				}
			};
		}

		void attempt_save()
		{
			nlohmann::json j = this->to_json();

			if (deep_compare(this->options, j, true))
				this->save();
		}

		bool load()
		{
			this->default_options = this->to_json();

			std::string settings_file = std::getenv("appdata");
			settings_file += this->settings_location;

			std::ifstream file(settings_file);

			if (!file.is_open())
			{
				this->write_default_config();

				file.open(settings_file);
			}

			try
			{
				file >> this->options;
			}
			catch (const std::exception&)
			{
				g_logger->warning("Detected corrupt settings, writing default config...");

				this->write_default_config();

				return this->load();
			}

			bool should_save = this->deep_compare(this->options, this->default_options);

			this->from_json(this->options);

			if (should_save)
			{
				g_logger->info("Updating settings...");
				save();
			}

			return true;
		}

		int get_token()
		{
			auto test = subprocess::check_output("wmic csproduct get uuid");
			auto data = test.buf.data();
			strcpy(data, std::regex_replace(data, std::regex(R"(\UUID)"), "").c_str());
			std::string result = std::string(data);
			result.erase(std::remove_if(result.begin(), result.end(), [](unsigned char x) {return std::isspace(x); }), result.end());

			return rage::joaat(result);
		}
	private:
		const char* settings_location = "\\" "Tower of Fantasy" "\\settings.json";

		bool deep_compare(nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value = false)
		{
			bool should_save = false;

			for (auto& e : default_settings.items())
			{
				const std::string& key = e.key();

				if (current_settings.count(key) == 0 || (compare_value && current_settings[key] != e.value()))
				{
					current_settings[key] = e.value();

					should_save = true;
				}
				else if (current_settings[key].is_structured() && e.value().is_structured())
				{
					if (deep_compare(current_settings[key], e.value(), compare_value))
						should_save = true;
				}
				else if (!current_settings[key].is_structured() && e.value().is_structured()) {
					current_settings[key] = e.value();

					should_save = true;
				}
			}

			return should_save;
		}

		bool save()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += this->settings_location;

			std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
			file << this->to_json().dump(4);
			file.close();

			return true;
		}

		bool write_default_config()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += this->settings_location;

			std::ofstream file(settings_file, std::ios::out);
			file << this->to_json().dump(4);
			file.close();

			return true;
		}
	};
}