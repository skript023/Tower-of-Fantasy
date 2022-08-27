#pragma once

#include <SDKDDKVer.h>
#include <Windows.h>
#include <D3D11.h>
#include <d3d12.h>
#include "utility/includes/d3dx9.h"
#include <wrl/client.h>

#include <cinttypes>
#include <cstddef>
#include <cstdint>

#include <chrono>
#include <ctime>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <atomic>
#include <mutex>
#include <thread>

#include <memory>
#include <new>

#include <sstream>
#include <string>
#include <string_view>

#include <algorithm>
#include <functional>
#include <utility>

#include <stack>
#include <vector>

#include <typeinfo>
#include <type_traits>

#include <exception>
#include <stdexcept>

#include <any>
#include <optional>
#include <variant>

#include <regex>
#include <tlhelp32.h>

#include <nlohmann/json.hpp>
#include <StackWalker.h>

#include "logger.hpp"
#include "settings.hpp"

#define MOD_NAME "Ellohim Private Menu"

#define PRODUCT_NAME "Ellohim"

#define DISTANCE_SPAWN 10

#define CUSTOM_HUD "Madang Hese Udud Hese Teu Boga Duit Wuhan Kontol"

#define ENVIRONMENT "Tower of Fantasy"

namespace big
{
	using namespace std::chrono_literals;
	
	template <typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	inline HMODULE g_hmodule{};
	inline HANDLE g_main_thread{};
	inline DWORD g_main_thread_id{};
	inline std::atomic_bool g_running{ true };

	inline std::mutex g_thread_holder{};
	inline std::condition_variable g_condition{};
	inline std::unique_lock<std::mutex> g_mutex_lock;

	struct stackwalker : public StackWalker
	{
		using StackWalker::StackWalker;

		void OnOutput(LPCSTR szText) override
		{
			g_logger->error(szText);
		}
	};

	inline stackwalker g_stackwalker;
}
