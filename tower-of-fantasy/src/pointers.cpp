#include "common.hpp"
#include "logger.hpp"
#include "pointers.hpp"
#include "memory/all.hpp"

namespace big
{
	pointers::pointers(): m_base_address(memory::module("QRSL.exe").begin().as<uintptr_t>())
	{
		memory::pattern_batch main_batch;

		while (!swapchain_found)
		{
			swapchain_found = this->get_swapchain();
			std::this_thread::sleep_for(0ms);
		}
		
		main_batch.add("GWorld", "48 8B 1D ? ? ? ? 48 85 DB 74 3B 41 B0 01", [this](memory::handle ptr)
		{
			m_world = ptr.add(3).rip().as<decltype(m_world)>();
		});

		main_batch.add("GObject", "48 8B 05 ? ? ? ? C1 F9 10 48 63 C9 48 8B 14 C8 4B 8D 0C 40 4C 8D 04 CA", [this](memory::handle ptr)
		{
			m_object = ptr.add(3).rip().as<decltype(m_object)>();//7FF6818412D8
		});

		main_batch.add("GName", "48 8D 05 ? ? ? ? EB 13 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 0F 10 03 4C 8D 44 24", [this](memory::handle ptr)
		{
			m_name = ptr.add(3).rip().as<decltype(m_name)>();
		});

		main_batch.add("FUObjectArray", "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 28 E9 ? ? ? ? 48 83 EC 28 48 8D 0D ? ? ? ? FF 15 ? ? ? ?", [this](memory::handle ptr)
		{
			m_object_array = ptr.add(3).rip().as<decltype(m_object_array)>();
		});

		main_batch.add("Screen Resolution", "8B 0D ? ? ? ? 8B 05 ? ? ? ? 41 89 4E 04 E9 ? ? ? ? 32 C9", [this](memory::handle ptr)
		{
			m_screen = ptr.add(8).rip().as<decltype(m_screen)>();
		});

		main_batch.add("Matrix", "48 8B 05 ? ? ? ? 48 85 C0 74 0B 48 89 58 08 48 8B 05 ? ? ? ? 48 89 03", [this](memory::handle ptr)
		{
			m_view_matrix = ptr.add(3).rip().as<decltype(m_view_matrix)>();
		});

		main_batch.add("Cooldown", "74 ? 83 79 08 ? 7F", [this](memory::handle ptr)
		{
			m_cooldown = ptr.as<decltype(m_cooldown)>();
		});

		main_batch.add("Player Navigation", "48 89 05 ? ? ? ? E8 ? ? ? ? 48 8B 45 38 48 89 05 ? ? ? ? 48 85 DB", [this](memory::handle ptr)
		{
			m_player_nav = ptr.add(3).rip().as<decltype(m_player_nav)>();
		});

		main_batch.add("Rapid Attack", "0F 28 C2 74 12 F3 0F 10 4F ? F3 0F 5C 4C 24 ? 0F 2F D1", [this](memory::handle ptr)
		{
			m_rapid_attack = ptr.add(2).as<decltype(m_rapid_attack)>();
		});

		main_batch.add("Local Player", "48 89 3D ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 89 05 ? ? ? ? 40 88 3D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? E9", [this](memory::handle ptr)
		{
			m_player = ptr.add(3).rip().as<decltype(m_player)>();
		});

		main_batch.add("UObjectt::ProcessEvent", "E8 ? ? ? ? 48 8B 74 24 ? 48 8B 5C 24 ? 48 8B 6C 24 ? 48 83 C4 20 5F C3 40 57", [this](memory::handle ptr)
		{
			m_process_event = ptr.add(1).rip().as<decltype(m_process_event)>();
		});

		main_batch.add("Task Queue", "41 56 41 57 48 63 01 4C 8B D2 48 89 6C 24 ? 4D 8B F1 41 8B 69 08 4C 8B F9 4D 8B 09 44 8B DD", [this](memory::handle ptr)
		{
			m_task_queue = ptr.as<decltype(m_task_queue)>();
		});

		main_batch.add("GetFName", "48 89 5C 24 ? 57 48 83 EC 30 48 8B D9 48 89 54 24 ? 33 C9 41 8B F8 4C 8B CA 48 85 D2 74 15 48 C7 C0", [this](memory::handle ptr)
		{
			
		});

		main_batch.add("Get Bone Matrix", "E8 ? ? ? ? 48 8B CB 0F 10 00 0F 11 83 ? ? ? ? 0F 10 48 10 0F 11 8B ? ? ? ? 0F 10 40 20 0F 11 83", [this](memory::handle ptr)
		{
			m_get_bone_matrix = ptr.as<decltype(m_get_bone_matrix)>();
		});

		main_batch.add("Skip Cutscene Button", "74 ? 41 83 BE ? ? ? ? ? 75 ? 49 8B CE", [this](memory::handle ptr)
		{
			m_skip_button = ptr.as<decltype(m_skip_button)>();
		});

		main_batch.add("SSR Stealer", "80 39 1D 75 2C 48 8B 41 08 48 63 49 10 4C 8D 04 49 4E 8D 0C 80 49 3B C1 74 14 48 8B 0A 0F 1F", [this](memory::handle ptr)
		{
			m_ssr_stuff = ptr.sub(13).as<decltype(m_ssr_stuff)>();
		});

		main_batch.run(memory::module(nullptr));

		this->m_hwnd = FindWindowW(L"UnrealWindow", L"Tower of Fantasy  ");
		if (!this->m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}

	bool pointers::get_swapchain()
	{
		return directx_11();
	}

	bool pointers::directx_11()
	{
		WNDCLASSEX windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = DefWindowProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = NULL;
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = L"Kiero";
		windowClass.hIconSm = NULL;

		::RegisterClassEx(&windowClass);

		this->m_window = ::CreateWindow(windowClass.lpszClassName, L"Kiero DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

		if (this->m_window == NULL)
		{
			return false;
		}

		HMODULE D3D11Module = ::GetModuleHandle(L"d3d11.dll");
		if (D3D11Module == NULL)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		void* D3D11CreateDeviceAndSwapChain = ::GetProcAddress(D3D11Module, "D3D11CreateDeviceAndSwapChain");
		if (D3D11CreateDeviceAndSwapChain == NULL)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1, };

		DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = this->m_window;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr = ((long(__stdcall*)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*, UINT, UINT, const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**))(D3D11CreateDeviceAndSwapChain))(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 2, D3D11_SDK_VERSION, &swapChainDesc, &this->m_swapchain, &this->m_d3d_device, &featureLevel, &this->m_d3d_context);
		if (FAILED(hr))
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		::memcpy(this->m_swapchain_methods, *(void***)this->m_swapchain, sizeof(m_swapchain_methods));

		this->m_swapchain->Release();
		this->m_swapchain = NULL;

		this->m_d3d_device->Release();
		this->m_d3d_device = NULL;

		this->m_d3d_context->Release();
		this->m_d3d_context = NULL;

		::DestroyWindow(this->m_window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		return true;
	}

	bool pointers::directx_12()
	{
		WNDCLASSEX windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = DefWindowProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = NULL;
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = L"Kiero";
		windowClass.hIconSm = NULL;

		::RegisterClassEx(&windowClass);

		this->m_window = ::CreateWindow(windowClass.lpszClassName, L"Kiero DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

		if (this->m_window == NULL)
		{
			return false;
		}

		HMODULE D3D12Module = ::GetModuleHandle(L"d3d12.dll");
		HMODULE DXGIModule = ::GetModuleHandle(L"dxgi.dll");
		if (D3D12Module == NULL || DXGIModule == NULL)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		void* CreateDXGIFactory = GetProcAddress(DXGIModule, "CreateDXGIFactory");
		if (CreateDXGIFactory == NULL)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		IDXGIFactory* Factory;
		if (((long(__stdcall*)(const IID&, void**))(CreateDXGIFactory))(__uuidof(IDXGIFactory), (void**)&Factory) < 0) 
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		IDXGIAdapter* Adapter;
		if (Factory->EnumAdapters(0, &Adapter) == DXGI_ERROR_NOT_FOUND) {
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		void* D3D12CreateDevice = GetProcAddress(D3D12Module, "D3D12CreateDevice");
		if (D3D12CreateDevice == NULL) {
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		ID3D12Device* Device;
		if (((long(__stdcall*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**))(D3D12CreateDevice))(Adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)&Device) < 0) {
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		D3D12_COMMAND_QUEUE_DESC QueueDesc;
		QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		QueueDesc.Priority = 0;
		QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		QueueDesc.NodeMask = 0;

		ID3D12CommandQueue* CommandQueue;
		if (Device->CreateCommandQueue(&QueueDesc, __uuidof(ID3D12CommandQueue), (void**)&CommandQueue) < 0)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		ID3D12CommandAllocator* CommandAllocator;
		if (Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&CommandAllocator) < 0) 
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		ID3D12GraphicsCommandList* CommandList;
		if (Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, CommandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&CommandList) < 0)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		DXGI_RATIONAL RefreshRate;
		RefreshRate.Numerator = 60;
		RefreshRate.Denominator = 1;

		DXGI_MODE_DESC BufferDesc;
		BufferDesc.Width = 100;
		BufferDesc.Height = 100;
		BufferDesc.RefreshRate = RefreshRate;
		BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC SampleDesc;
		SampleDesc.Count = 1;
		SampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
		SwapChainDesc.BufferDesc = BufferDesc;
		SwapChainDesc.SampleDesc = SampleDesc;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.BufferCount = 2;
		SwapChainDesc.OutputWindow = this->m_window;
		SwapChainDesc.Windowed = 1;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (Factory->CreateSwapChain(CommandQueue, &SwapChainDesc, &this->m_swapchain) < 0)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		memcpy(this->m_swapchain_methods, *(void***)this->m_swapchain, sizeof(this->m_swapchain_methods));

		std::this_thread::sleep_for(1s);

		Device->Release();
		Device = NULL;

		CommandQueue->Release();
		CommandQueue = NULL;

		CommandAllocator->Release();
		CommandAllocator = NULL;

		CommandList->Release();
		CommandList = NULL;

		this->m_swapchain->Release();
		this->m_swapchain = NULL;

		::DestroyWindow(this->m_window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		return true;
	}
}