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
		
	}

	bool main_menu::get_authentication(const char* username, const char* password)
	{
		
	}

	void main_menu::main_window(const char* window_name)
	{
		if (ImGui::Begin(window_name))
		{
			ImGui::BeginTabBar("tabbar");
			player_menu::render_menu();
			teleport_menu::render_menu();
			player_stat::render_menu();
			setting_menu::render_menu();
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}