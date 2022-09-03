#include "notification_service.hpp"
#include "fonts/font_icon.hpp"
#include "fonts/icon.h"

namespace big
{
	notification_service::notification_service()
	{
		g_notification_service = this;
	}

	notification_service::~notification_service()
	{
		g_notification_service = nullptr;
	}

	void notification_service::push(notification n)
	{
		this->notifications.emplace(std::hash<std::string>{}(n.message + n.title), n);
	}

	void notification_service::success(std::string title, std::string message)
	{
		this->push({ NotificationType::SUCCESS, ICON_FA_CHECK_CIRCLE " " + title, message, std::chrono::system_clock::now(), 3000.f , 1.f});
	}

	void notification_service::info(std::string title, std::string message)
	{
		this->push({ NotificationType::INFO, ICON_FA_INFO_CIRCLE " " + title, message, std::chrono::system_clock::now(), 3000.f , 1.f });
	}

	void notification_service::warning(std::string title, std::string message)
	{
		this->push({ NotificationType::WARNING, ICON_FA_EXCLAMATION_TRIANGLE " " + title, message, std::chrono::system_clock::now(), 3000.f , 1.f });
	}

	void notification_service::error(std::string title, std::string message)
	{
		this->push({ NotificationType::DANGER, ICON_FA_TIMES_CIRCLE " " + title, message, std::chrono::system_clock::now(), 3000.f , 1.f });
	}

	std::vector<notification> notification_service::get()
	{
		std::vector<notification> notifications_to_sent;
		std::vector<std::size_t> to_remove;
		for (auto& n : this->notifications)
		{
			std::chrono::time_point<std::chrono::system_clock> curTime = std::chrono::system_clock::now();
			const float time_diff = (float)std::chrono::duration_cast<std::chrono::milliseconds>(curTime - n.second.created_on).count();
			n.second.alpha = 1;
			if (n.second.destroy_in <= time_diff) 
			{
				n.second.alpha = 1.f - ((time_diff - n.second.destroy_in) / 600);
				n.second.alpha = n.second.alpha < 0.f ? 0.f : n.second.alpha;
			}

			if (n.second.alpha > 0.f)
				notifications_to_sent.push_back(n.second);
			else to_remove.push_back(n.first);
		}
		for (std::size_t k : to_remove)
			this->notifications.erase(k);

		return notifications_to_sent;
	}

	void notification_service::merge_icon_with_latest_font(float font_size, bool FontDataOwnedByAtlas)
	{
		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.FontDataOwnedByAtlas = FontDataOwnedByAtlas;

		g_settings->window.font_icon = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)font_icons, sizeof(font_icons), font_size, &icons_config, icons_ranges);
	}
}