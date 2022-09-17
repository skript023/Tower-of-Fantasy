#include "common.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "thread_pool.hpp"
#include "settings.hpp"
#include "virtual_protect.hpp"
#include "script_mgr.hpp"
#include "translation.hpp"
#include "native_invoker.hpp"
#include "directx_pool.hpp"
#include "utility/services/init_services.hpp"

DWORD APIENTRY main_thread(LPVOID)
{
	using namespace big;

	while (!FindWindow(L"UnrealWindow", L"Tower of Fantasy  "))
		std::this_thread::sleep_for(1s);

	auto logger_instance = std::make_unique<logger>();
	try
	{
		g_logger->raw(R"kek(
 _______                        ____   __   ______          _                  
|__   __|                      / __ \ / _| |  ____|        | |                 
   | | _____      _____ _ __  | |  | | |_  | |__ __ _ _ __ | |_ __ _ ___ _   _ 
   | |/ _ \ \ /\ / / _ \ '__| | |  | |  _| |  __/ _` | '_ \| __/ _` / __| | | |
   | | (_) \ V  V /  __/ |    | |__| | |   | | | (_| | | | | || (_| \__ \ |_| |
   |_|\___/ \_/\_/ \___|_|     \____/|_|   |_|  \__,_|_| |_|\__\__,_|___/\__, |
                                                                          __/ |
                                                                         |___/ 
)kek");
		auto translation_instance = std::make_unique<TranslationManager>();
		g_translation_manager->load_translation("English");
		g_logger->info("Translation initialized.");

		auto settings_instance = std::make_unique<settings>();
		g_settings->load();
		g_logger->info("Settings initialized.");

		auto pointers_instance = std::make_unique<pointers>();
		g_logger->info("Pointers initialized.");

		auto virtual_protect_instance = std::make_unique<virtual_protect>();
		g_virtual_protect->enable();
		g_logger->info("Virtual Protect initialized.");

		auto renderer_instance = std::make_unique<renderer>();
		auto directx_warper = std::make_unique<directx_pool>();
		g_logger->info("Renderer initialized.");

		auto hooking_instance = std::make_unique<hooking>();
		g_logger->info("Hooking initialized.");

		auto fiber_instance = std::make_unique<fiber_pool>(10);
		g_logger->info("Fiber Pool initialized.");

		auto thread_pool_instance = std::make_unique<thread_pool>();
		g_logger->info("Thread Pool initialized.");

		auto native_instance = std::make_unique<NativeInvoker>();
		g_logger->info("Native Function initialized.");

		auto service_instance = std::make_unique<init_service>();
		g_logger->info("Service initialized.");

		g_thread_pool->push(gui::script_func);
		g_logger->info("Scripts registered.");

		g_hooking->enable();
		g_logger->info("Hooking enabled.");

		g_thread_pool->hold();

		g_hooking->disable();
		g_logger->info("Hooking disabled.");

		std::this_thread::sleep_for(1000ms);

		hooking_instance.reset();
		g_logger->info("Hooking uninitialized.");

		g_thread_pool->destroy();
		g_logger->info("Destroyed thread pool.");

		thread_pool_instance.reset();
		g_logger->info("Thread Pool uninitialized.");

		fiber_instance.reset();
		g_logger->info("Fiber Pool uninitialized.");

		native_instance.reset();
		g_logger->info("Native Function uninitialized.");

		service_instance.reset();
		g_logger->info("Service uninitialized.");

		renderer_instance.reset();
		g_logger->info("Renderer uninitialized.");

		virtual_protect_instance.reset();
		g_logger->info("Virtual Protect uninitialized");

		pointers_instance.reset();
		g_logger->info("Pointers uninitialized.");

		g_settings->attempt_save();
		settings_instance.reset();
		g_logger->info("Settings saved and uninitialized.");

		translation_instance.reset();
		g_logger->info("Translation uninitialized.");
	}
	catch (std::exception const& ex)
	{
		g_logger->info(ex.what());
		MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
	}

	g_logger->info("Farewell!");
	logger_instance.reset();

	CloseHandle(g_main_thread);
	FreeLibraryAndExitThread(g_hmodule, 0);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;

	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_main_thread = CreateThread(nullptr, 0, &main_thread, nullptr, 0, &g_main_thread_id);
		break;
	case DLL_PROCESS_DETACH:
		g_running = false;
		break;
	}

	return true;
}
