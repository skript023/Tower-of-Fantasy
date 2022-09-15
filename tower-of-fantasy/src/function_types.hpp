#pragma once
#include "common.hpp"
#include "class/vector.hpp"
#include "class/uobject.hpp"
#include "class/enums.hpp"

namespace big::functions
{
	using get_bone_matrix_t = Vector4(*)(int bone_index);
	using process_event_t = void(__fastcall*)(UObject* __this,UFunction* function, void* parms);
	using ftext_to_fstring_t = FString*(__fastcall*)(FText* text);
	using fname_t = FName(__fastcall*)(wchar_t*, EFindName);
}
