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

	class AActorArray
	{
	public:
		char pad_0000[0x18];
		int m_name_index; //0x18
		char pad_001C[0x11C];
		class RootComponent* m_root_component; //0x138
	};

	class AActor
	{
	public:
		class AActorArray* m_actor_array[1024];
	};

	class LevelArray
	{
	public:
		char pad_0000[0x98];
		class AActor* m_actor; //0x98
		int m_actor_count; //0xA0
	};

	class ULevel
	{
	public:
		class LevelArray* m_level_array[1024];
	};
#pragma pack(pop)
}