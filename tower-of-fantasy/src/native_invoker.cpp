#include "native_invoker.hpp"
#include "utility/unreal_engine_utility.hpp"

namespace big
{
	NativeInvoker::NativeInvoker():
		m_world_to_screen(UObject::find_object<UFunction*>("Function Engine.PlayerController.ProjectWorldLocationToScreen"))
	{
		g_native_invoker = this;
	}

	NativeInvoker::~NativeInvoker()
	{
		g_native_invoker = nullptr;
	}

}