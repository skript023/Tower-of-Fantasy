#pragma once
#include <class/vector.hpp>

namespace big
{
#pragma pack(push, 1)
	class RootComponent
	{
	public:
		char pad_000[0x124];
		Vector3 m_relative_location; //0x124
	};

	class AActor
	{
	public:
		char pad_0000[0x18];
		int m_name_index; //0x18
		char pad_001C[0x11C];
		class RootComponent* m_root_component; //0x138
		bool valid_root_component()
		{
			RootComponent* result;
			if (!ReadProcessMemory(GetCurrentProcess(), this->m_root_component, &result, sizeof(this->m_root_component), nullptr))
			{
				return false;
			}
			return true;
		}
	};

	class ULevel
	{
	public:
		char pad_0000[0x98];
		TArray<AActor*> m_actor; //0x98
	};
#pragma pack(pop)
}