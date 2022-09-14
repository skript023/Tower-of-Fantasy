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
		char pad_0130[1500]; //0x0130
		bool m_is_allow_pick; //0x070C
		char pad_070D[69]; //0x070D
		bool m_is_harvested; //0x0752
		char pad_0753[426]; //0x0753
		bool m_can_client_open; //0x08FD

		bool fresh_box()
		{
			if (!m_is_harvested && m_is_allow_pick && m_can_client_open)
			{
				return true;
			}
			return false;
		}
	};
	static_assert(sizeof(RootComponent) == 0x8FE);

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
	const auto test = sizeof(AActor);
	static_assert(sizeof(AActor) == 0x140);

	class ULevel
	{
	public:
		char pad_0000[0x98];
		TArray<AActor*> m_actor; //0x98
	};
#pragma pack(pop)
}