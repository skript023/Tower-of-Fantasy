#include "main_menu.hpp"
#include "gui.hpp"
#include "thread_pool.hpp"
#include "utility/ecryption.h"
#include "utility/services/all.hpp"
#include "utility/networking/http_request.hpp"
#include "utility/joaat.hpp"

#include "player_menu.h"
#include "player_stats.h"
#include "setting_menu.h"
#include "teleport_menu.h"

#include <objbase.h>      // include the base COM header
#include <netlistmgr.h>

// Instruct linker to link to the required COM libraries
#pragma comment(lib, "ole32.lib")

namespace big
{
	bool main_menu::check_network_status()
	{
		INTERNET_STATUS connectedStatus = INTERNET_STATUS::CONNECTION_ERROR;
		connectedStatus = get_internet_status();
		switch (connectedStatus)
		{
		case INTERNET_STATUS::CONNECTED:
			return true;
		case INTERNET_STATUS::DISCONNECTED:
			return false;
		case INTERNET_STATUS::CONNECTED_TO_LOCAL:
			return false;
		case INTERNET_STATUS::CONNECTION_ERROR:
			return false;
		}
		return false;
	}

	INTERNET_STATUS main_menu::get_internet_status()
	{
		INTERNET_STATUS connectedStatus = INTERNET_STATUS::CONNECTION_ERROR;
		HRESULT hr = S_FALSE;

		try
		{
			hr = CoInitialize(NULL);
			if (SUCCEEDED(hr))
			{
				INetworkListManager* pNetworkListManager;
				hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL, __uuidof(INetworkListManager), (LPVOID*)&pNetworkListManager);
				if (SUCCEEDED(hr))
				{
					NLM_CONNECTIVITY nlmConnectivity = NLM_CONNECTIVITY::NLM_CONNECTIVITY_DISCONNECTED;
					VARIANT_BOOL isConnected = VARIANT_FALSE;
					hr = pNetworkListManager->get_IsConnectedToInternet(&isConnected);
					if (SUCCEEDED(hr))
					{
						if (isConnected == VARIANT_TRUE)
							connectedStatus = INTERNET_STATUS::CONNECTED;
						else
							connectedStatus = INTERNET_STATUS::DISCONNECTED;
					}

					if (isConnected == VARIANT_FALSE && SUCCEEDED(pNetworkListManager->GetConnectivity(&nlmConnectivity)))
					{
						if (nlmConnectivity & (NLM_CONNECTIVITY_IPV4_LOCALNETWORK | NLM_CONNECTIVITY_IPV4_SUBNET | NLM_CONNECTIVITY_IPV6_LOCALNETWORK | NLM_CONNECTIVITY_IPV6_SUBNET))
						{
							connectedStatus = INTERNET_STATUS::CONNECTED_TO_LOCAL;
						}
					}

					pNetworkListManager->Release();
				}
			}

			CoUninitialize();
		}
		catch (...)
		{
			connectedStatus = INTERNET_STATUS::CONNECTION_ERROR;
		}

		return connectedStatus;
	}

	bool main_menu::create_session(uint32_t status)
	{
		constexpr auto result = RAGE_JOAAT("Success");
		if (status == result)
		{
			return true;
		}
		return false;
	}

	bool main_menu::get_authentication(const char* username, const char* password)
	{
		if (!check_network_status())
		{
			g_notification_service->error("Ellohim Authentication", "Login failed, you are not connected to internet");
			return false;
		}
		try
		{
			http::Request request{ std::format("http://external-view.000webhostapp.com/ellohim_system.php?username={}&password={}&IGN={}&rockstar_id={}&player_ip={}", username, password, "Rega Fadnur Pradana", 999999999, "127.0.0.1")};
			const auto response = request.send("GET");

			auto get_result = std::string{ response.body.begin(), response.body.end() };
			get_result.erase(std::remove_if(get_result.begin(), get_result.end(), [](unsigned char x) {return std::isspace(x); }), get_result.end());
			g_main_window.login_status = get_result.empty() ? 0 : stoi(get_result);
			g_notification_service->success("Ellohim Authentication", "Your credential sucessfully authenticated.");
			return true;
		}
		catch (const std::exception& e)
		{
			g_notification_service->error("Ellohim Authentication", "Login Failed : Your Username or Password Incorrect");
			g_logger->error(e.what());
			g_main_window.login_status = RAGE_JOAAT("Request failed, couldn't connect to server");
			return false;
		}
	}

	void main_menu::main_window(const char* window_name)
	{
		if (ImGui::Begin(window_name))
		{
			if (false)
			{
				ImGui::PushItemWidth(200);
				ImGui::Text("Username");
				ImGui::InputText(xorstr("##Username"), m_username, IM_ARRAYSIZE(m_username));
				ImGui::Text("Password");
				ImGui::InputText(xorstr("##Password"), m_password, IM_ARRAYSIZE(m_password), ImGuiInputTextFlags_Password);
				ImGui::PopItemWidth();
				if (ImGui::Button(xorstr(ICON_FA_SIGN_IN_ALT " Login")))
				{
					g_thread_pool->push([]
					{
						if (strcmp(m_username, "tumbal") == 0 && strcmp(m_password, "123") == 0)
						{
							login_status = RAGE_JOAAT("Success");
							g_notification_service->success("Ellohim Authentication", "Login Success : Mod Menu Running!");
						}
					});
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr(ICON_FA_POWER_OFF " Quit")))
				{
					g_running = false;
				}
			}

			if (true)
			{
				ImGui::BeginTabBar("tabbar");
				player_menu::render_menu();
				teleport_menu::render_menu();
				player_stat::render_menu();
				setting_menu::render_menu();
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}