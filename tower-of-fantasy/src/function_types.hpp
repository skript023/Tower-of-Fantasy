#pragma once
#include "common.hpp"
#include "class/vector.hpp"
#include "class/uobject.hpp"

namespace big::functions
{
	using get_bone_matrix_t = Vector4(*)(int bone_index);
	using process_event_t = void(*)(UObject* __this,UFunction* function, void* parms);
}
