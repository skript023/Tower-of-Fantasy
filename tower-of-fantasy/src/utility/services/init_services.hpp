#pragma once
#include "notification/notification_service.hpp"

namespace big
{
	class init_service;
	inline init_service* g_service{};

	class init_service
	{
	public:
		explicit init_service()
		{
			notification = std::make_unique<notification_service>();

			g_service = this;
		}

		~init_service()
		{
			notification.reset();

			g_service = nullptr;
		}

	private:
		std::unique_ptr<notification_service> notification;
	};
}