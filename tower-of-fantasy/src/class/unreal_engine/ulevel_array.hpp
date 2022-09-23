#pragma once
#include <class/vector.hpp>
#include "native_invoker.hpp"

namespace big
{
#pragma pack(push, 1)
	class Owner
	{
	public:
		char padding[0x1240];
		FText m_decriptive_name;
	};

	class RootComponent : public UObject
	{
	public:
		char pad_0028[252];
		Vector3 m_relative_location; //0x124

		void k2_add_relative_location(FVector DeltaLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorLocation params{};

			params.m_new_location = DeltaLocation;
			params.m_sweep = bSweep;
			params.m_teleport = bTeleport;
			const std::string func = "Function Engine.SceneComponent.K2_AddRelativeLocation";

			if (!g_native_invoker->m_k2_add_relative_location)
				g_native_invoker->m_k2_add_relative_location = g_native_invoker->get_native(func);

			process_event(g_native_invoker->m_k2_add_relative_location, &params);

			SweepHitResult = params.m_sweep_hit_result;
		}

		void k2_add_local_offset(FVector DeltaLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorLocation params{};
			static const std::string func = "Function Engine.SceneComponent.K2_AddLocalOffset";

			params.m_new_location = DeltaLocation;
			params.m_sweep = bSweep;
			params.m_teleport = bTeleport;

			if (!g_native_invoker->m_k2_add_local_offset)
				g_native_invoker->m_k2_add_local_offset = g_native_invoker->get_native(func);

			process_event(g_native_invoker->m_k2_add_local_offset, &params);

			SweepHitResult = params.m_sweep_hit_result;
		}

		Vector3 get_forward_vector()
		{
			GetForwardVector params{};
			const std::string native = "Function Engine.SceneComponent.GetForwardVector";
			if (!g_native_invoker->m_get_forward_vector)
				g_native_invoker->m_get_forward_vector = g_native_invoker->get_native(native);

			process_event(g_native_invoker->m_get_forward_vector, &params);

			return params.m_return;
		}
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
		char pad_08FE[0x942];
		FText m_decriptive_name; //0x1240

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

		RootComponent* k2_get_root_component()
		{
			K2_GetRootComponent params{};
			const std::string native = "Function Engine.Actor.K2_GetRootComponent";
			if (!g_native_invoker->m_k2_get_root_component)
				g_native_invoker->m_k2_get_root_component = g_native_invoker->get_native(native);

			process_event(g_native_invoker->m_k2_get_root_component, &params);

			return params.m_return;
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
			if (IsBadReadPtr(&this->m_can_use_auto_pickup, sizeof(&this->m_can_use_auto_pickup)))
			{
				return;
			}
			this->m_can_use_auto_pickup = activate;
		}

		bool k2_teleport_to(FVector pos, Rotator rot)
		{
			K2_TeleportTo params{};
			const std::string native = "Function Engine.Actor.K2_TeleportTo";

			if (!g_native_invoker->m_k2_teleport_to)
				g_native_invoker->m_k2_teleport_to = g_native_invoker->get_native(native);

			params.m_location.x = pos.x;
			params.m_location.y = pos.y;
			params.m_location.z = pos.z + 1.f;
			params.m_rotation = rot;

			process_event(g_native_invoker->m_k2_teleport_to, &params);

			return params.m_return;
		}

		bool k2_set_actor_location(FVector pos, bool Sweeped, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorLocation params{};
			const std::string native = "Function Engine.Actor.K2_SetActorLocationAndRotation";

			if (!g_native_invoker->m_k2_set_actor_location_and_rotation)
				g_native_invoker->m_k2_set_actor_location_and_rotation = g_native_invoker->get_native(native);

			params.m_new_location = pos;
			params.m_sweep = Sweeped;
			params.m_teleport = bTeleport;

			process_event(g_native_invoker->m_k2_set_actor_location_and_rotation, &params);
			SweepHitResult = params.m_sweep_hit_result;

			return params.m_return;
		}

		bool k2_set_actor_location_and_rotation(FVector pos, Rotator rot, bool Sweeped, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorLocationAndRotation params{};
			const std::string native = "Function Engine.Actor.K2_SetActorLocationAndRotation";

			if (!g_native_invoker->m_k2_set_actor_location_and_rotation)
				g_native_invoker->m_k2_set_actor_location_and_rotation = g_native_invoker->get_native(native);

			params.m_new_location = pos;
			params.m_new_rotation = rot;
			params.m_sweep = Sweeped;
			params.m_teleport = bTeleport;

			process_event(g_native_invoker->m_k2_set_actor_location_and_rotation, &params);

			SweepHitResult = params.m_sweep_hit_result;

			return params.m_return;
		}

		void k2_set_relative_location(FVector NewRelativeLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorRelativeLocation params{};

			params.m_new_location = NewRelativeLocation;
			params.m_sweep = bSweep;
			params.m_teleport = bTeleport;
			const std::string func = "Function Engine.Actor.K2_SetActorRelativeLocation";

			if (!g_native_invoker->m_k2_set_actor_relative_location)
				g_native_invoker->m_k2_set_actor_relative_location = g_native_invoker->get_native(func);

			process_event(g_native_invoker->m_k2_set_actor_relative_location, &params);

			SweepHitResult = params.m_sweep_hit_result;
		}
	};
	const auto test = sizeof(AActor);
	static_assert(sizeof(AActor) == 0x1258);

	class ULevel
	{
	public:
		char pad_0000[0x98];
		TArray<AActor*> m_actor; //0x98
	};
#pragma pack(pop)
}