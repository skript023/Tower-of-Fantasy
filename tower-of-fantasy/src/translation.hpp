#pragma once
#include <nlohmann/json.hpp>
#include "utility/joaat.hpp"

namespace big
{
	class TranslationManager;
	inline TranslationManager* g_translation_manager;

	class TranslationManager
	{
	public:
		explicit TranslationManager():
			m_file_path(std::getenv("appdata"))
		{
			m_file_path += "\\" ENVIRONMENT "\\Translations\\";

			try
			{
				if (!std::filesystem::exists(m_file_path))
					std::filesystem::create_directory(m_file_path);
			}
			catch (std::filesystem::filesystem_error const&)
			{
			}

			g_translation_manager = this;
		}

		~TranslationManager()
		{
			g_translation_manager = nullptr;
		}

		/**
		 * \brief Loads a translation file
		 * \param name The stem of the translation file
		 */
		void load_translation(const char* name)
		{
			m_translations.clear();
			try
			{
				auto filename = std::format("{}.big", name);
				auto filepath = std::filesystem::path(m_file_path).append(filename);

				std::ifstream file(filepath);
				if (file.good())
				{
					std::stringstream str;
					std::string line;
					while (std::getline(file, line))
					{
						str << line << '\n';
					}

					nlohmann::json json = nlohmann::json::parse(str, nullptr, false);
					auto objects = json.get<std::unordered_map<std::string, nlohmann::json>>();

					for (auto&& [key, value] : objects)
					{
						m_translations.emplace(rage::joaat(key.c_str()), value.get<std::string>());
					}
				}
			}
			catch (nlohmann::detail::exception const&)
			{
				g_logger->info("Failed to parse %s translations.", name);
			}
		}

		/**
		 * \brief Loads a translation file
		 * \param label The hash of the label
		 * \return The translation string, or a placeholder string
		 */
		const char* get_translation(std::uint32_t label)
		{
			if (auto it = m_translations.find(label); it != m_translations.end())
			{
				return &(it->second)[0];
			}
			else
			{
				static char buf[64];

				std::fill(std::begin(buf), std::end(buf), '\0');
				std::snprintf(&buf[0], sizeof(buf) - 1, "Unknown (0x%08X)", label);

				return &buf[0];
			}
		}

		/**
		 * \brief Gets the directory of the translations
		 * \return const char*
		 */
		std::filesystem::path get_translation_directory()
		{
			return m_file_path;
		}

	private:
		std::unordered_map<std::uint32_t, std::string> m_translations;
		std::filesystem::path m_file_path;
	};
}

#define BIG_TRANSLATE_IMPL(label) (::big::g_translation_manager->get_translation(RAGE_JOAAT(label)))
#define BIG_TRANSLATE(label) BIG_TRANSLATE_IMPL(label)