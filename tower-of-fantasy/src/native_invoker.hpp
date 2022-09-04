#pragma once
#include "class/fwddec.hpp"
#include "class/vector.hpp"

namespace big
{
	struct WorldToScreenParam
	{
		Vector3 world_location;
		Vector2 screen_location;
		bool m_viewport_relative;
		bool m_return;
	};

	class NativeInvoker
	{
	public:
		explicit NativeInvoker();
		~NativeInvoker();

	public:
		UFunction* m_world_to_screen;

	public:
		WorldToScreenParam m_world_to_screen_param{};
	};

	inline NativeInvoker* g_native_invoker;
}