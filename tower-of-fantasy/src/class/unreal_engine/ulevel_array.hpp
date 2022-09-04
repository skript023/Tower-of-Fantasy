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

	class AActor : public UObject
	{
	public:
		char pad_0028[0x110];
		class RootComponent* m_root_component; //0x138
		RootComponent* root_component()
		{
			if (IsBadReadPtr(this->m_root_component, sizeof(this->m_root_component)))
			{
				return nullptr;
			}
			return this->m_root_component;
		}
	};
	static_assert(sizeof(AActor) == 0x140);

	class ULevel
	{
	public:
		char pad_0000[0x98];
		TArray<AActor*> m_actor; //0x98
	};
#pragma pack(pop)
}