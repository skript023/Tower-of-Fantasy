#pragma once
#include <class/vector.hpp>

namespace big
{
#pragma pack(push, 1)
	class Owner
	{
	public:
		char padding[0x1240];
		FText m_decriptive_name;
	};

	class RootComponent
	{
	public:
		char pad_000[0x124];
		Vector3 m_relative_location; //0x124
	};
	static_assert(sizeof(RootComponent) == 0x130);

	class AActor : public UObject
	{
	public:
		char pad_0028[192];
		class Owner* m_owner; //0xE8
		char pad_00F0[72]; //0xF0
		class RootComponent* m_root_component; //0x138
		char pad_0140[1484]; //0x0140
		bool m_is_allow_pick; //0x070C
		char pad_070D[69]; //0x070D
		short m_has_harvested; //0x0752
		char pad_0754[188]; //0x0754
		bool m_can_use_auto_pickup; //0x0810
		char pad_0811[236]; //0x0811
		bool m_can_client_open; //0x08FD

		Owner* owner()
		{
			if (IsBadReadPtr(this->m_owner, sizeof(this->m_owner)))
			{
				return nullptr;
			}
			return this->m_owner;
		}

		RootComponent* root_component()
		{
			if (IsBadReadPtr(this->m_root_component, sizeof(this->m_root_component)))
			{
				return nullptr;
			}
			return this->m_root_component;
		}

		bool harvested()
		{
			return this->m_has_harvested != 0;
		}

		bool allow_pick()
		{
			return this->m_is_allow_pick;
		}

		bool client_can_open()
		{
			return this->m_can_client_open;
		}

		void can_use_auto_pickup(bool activate)
		{
			if (IsBadReadPtr(&this->m_can_use_auto_pickup), sizeof(&this->m_can_use_auto_pickup))
			{
				return;
			}
			this->m_can_use_auto_pickup = activate;
		}
	};
	const auto test = sizeof(AActor);
	static_assert(sizeof(AActor) == 0x8FE);

	class ULevel
	{
	public:
		char pad_0000[0x98];
		TArray<AActor*> m_actor; //0x98
	};
#pragma pack(pop)
}