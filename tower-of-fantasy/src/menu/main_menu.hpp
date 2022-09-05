#pragma once

namespace big
{
	enum class INTERNET_STATUS
	{
		CONNECTED,
		DISCONNECTED,
		CONNECTED_TO_LOCAL,
		CONNECTION_ERROR
	};

	class main_menu
	{
	public:
		static void main_window(const char* window_name);
	private:
		static bool create_session(uint32_t status);
		static bool get_authentication(const char* username, const char* password);
		static bool check_network_status();
		static INTERNET_STATUS get_internet_status();
	protected:
		static inline uint32_t login_status;
		static inline char m_username[64];
		static inline char m_password[64];
	};

	inline main_menu g_main_window;
}