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
			constexpr auto func = RAGE_JOAAT("Function Engine.SceneComponent.K2_AddRelativeLocation");

			if (!g_native_invoker->m_k2_add_relative_location)
				g_native_invoker->m_k2_add_relative_location = g_native_invoker->get_native(func);

			process_event(g_native_invoker->m_k2_add_relative_location, &params);

			SweepHitResult = params.m_sweep_hit_result;
		}

		void k2_add_local_offset(FVector DeltaLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorLocation params{};
			constexpr auto func = RAGE_JOAAT("Function Engine.SceneComponent.K2_AddLocalOffset");

			params.m_new_location = DeltaLocation;
			params.m_sweep = bSweep;
			params.m_teleport = bTeleport;

			if (!g_native_invoker->m_k2_add_local_offset)
				g_native_invoker->m_k2_add_local_offset = g_native_invoker->get_native(func);

			process_event(g_native_invoker->m_k2_add_local_offset, &params);

			SweepHitResult = params.m_sweep_hit_result;
		}

		/**
		 * \brief Get the forward (X) unit direction vector from this component, in world space.
		 * \return Forward coordinates
		 */
		Vector3 get_forward_vector()
		{
			GetForwardVector params{};
			constexpr auto native = RAGE_JOAAT("Function Engine.SceneComponent.GetForwardVector");
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
			constexpr auto native = RAGE_JOAAT("Function Engine.Actor.K2_GetRootComponent");
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

		/**
		 * \brief Move the actor instantly to the specified location.
		 * \param NewLocation - The new location to teleport the Actor to.
		 * \param NewRotation - The new rotation for the Actor.
		 * \return Whether the location was successfully set.
		 */
		bool k2_teleport_to(FVector pos, Rotator rot)
		{
			K2_TeleportTo params{};
			constexpr auto native = RAGE_JOAAT("Function Engine.Actor.K2_TeleportTo");

			if (!g_native_invoker->m_k2_teleport_to)
				g_native_invoker->m_k2_teleport_to = g_native_invoker->get_native(native);

			params.m_location.x = pos.x;
			params.m_location.y = pos.y;
			params.m_location.z = pos.z + 1.f;
			params.m_rotation = rot;

			process_event(g_native_invoker->m_k2_teleport_to, &params);

			return params.m_return;
		}

		/**
		 * \brief Move the actor instantly to the specified location.
		 * \param NewLocation - The new location to teleport the Actor to.
		 * \param
		 * \param bSweep - Whether we sweep to the destination location, triggering overlaps along the way and stopping short of the target if blocked by something. Only the root component is swept and checked for blocking collision, child components move without sweeping. If collision is off, this has no effect.
		 * \param
		 * \param bTeleport - Whether we teleport the physics state (if physics collision is enabled for this object). If true, physics velocity for this object is unchanged (so ragdoll parts are not affected by change in location). If false, physics velocity is updated based on the change in position (affecting ragdoll parts). If CCD is on and not teleporting, this will affect objects along the entire swept volume.
		 * \param
		 * \param SweepHitResult - The hit result from the move if swept.
		 * \return Whether the location was successfully set.
		 */
		bool k2_set_actor_location(FVector pos, bool Sweeped, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorLocation params{};
			constexpr auto native = RAGE_JOAAT("Function Engine.Actor.K2_SetActorLocationAndRotation");

			if (!g_native_invoker->m_k2_set_actor_location_and_rotation)
				g_native_invoker->m_k2_set_actor_location_and_rotation = g_native_invoker->get_native(native);

			params.m_new_location = pos;
			params.m_sweep = Sweeped;
			params.m_teleport = bTeleport;

			process_event(g_native_invoker->m_k2_set_actor_location_and_rotation, &params);
			SweepHitResult = params.m_sweep_hit_result;

			return params.m_return;
		}

		/**
		 * \brief Move the actor instantly to the specified location and rotation.
		 * \param NewLocation - The new location to teleport the Actor to.
		 * \param
		 * \param NewRotation - The new rotation for the Actor.
		 * \param
		 * \param bSweep - Whether we sweep to the destination location, triggering overlaps along the way and stopping short of the target if blocked by something. Only the root component is swept and checked for blocking collision, child components move without sweeping. If collision is off, this has no effect.
		 * \param
		 * \param bTeleport - Whether we teleport the physics state (if physics collision is enabled for this object). If true, physics velocity for this object is unchanged (so ragdoll parts are not affected by change in location). If false, physics velocity is updated based on the change in position (affecting ragdoll parts). If CCD is on and not teleporting, this will affect objects along the entire swept volume.
		 * \param
		 * \param SweepHitResult - The hit result from the move if swept.
		 * \return Whether the rotation was successfully set.
		 */
		bool k2_set_actor_location_and_rotation(FVector pos, Rotator rot, bool Sweeped, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorLocationAndRotation params{};
			constexpr auto native = RAGE_JOAAT("Function Engine.Actor.K2_SetActorLocationAndRotation");

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

		/**
		 * \brief Set the actor's RootComponent to the specified relative location.
		 * \param NewRelativeLocation - New relative location of the actor's root component
		 * \param
		 * \param bSweep - Whether we sweep to the destination location, triggering overlaps along the way and stopping short of the target if blocked by something. Only the root component is swept and checked for blocking collision, child components move without sweeping. If collision is off, this has no effect.
		 * \param
		 * \param bTeleport - Whether we teleport the physics state (if physics collision is enabled for this object). If true, physics velocity for this object is unchanged (so ragdoll parts are not affected by change in location). If false, physics velocity is updated based on the change in position (affecting ragdoll parts). If CCD is on and not teleporting, this will affect objects along the entire swept volume.
		 */
		void k2_set_relative_location(FVector NewRelativeLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport = false)
		{
			K2_SetActorRelativeLocation params{};

			params.m_new_location = NewRelativeLocation;
			params.m_sweep = bSweep;
			params.m_teleport = bTeleport;
			constexpr auto func = RAGE_JOAAT("Function Engine.Actor.K2_SetActorRelativeLocation");

			if (!g_native_invoker->m_k2_set_actor_relative_location)
				g_native_invoker->m_k2_set_actor_relative_location = g_native_invoker->get_native(func);

			process_event(g_native_invoker->m_k2_set_actor_relative_location, &params);

			SweepHitResult = params.m_sweep_hit_result;
		}

		/**
		 * \brief Event called when this Actor is reset to its initial state - used when restarting level without reloading.
		 */
		void k2_on_reset()
		{
			constexpr auto native = RAGE_JOAAT("Function Engine.Actor.K2_OnReset");

			if (!g_native_invoker->m_k2_on_reset)
				g_native_invoker->m_k2_on_reset = g_native_invoker->get_native(native);

			process_event(g_native_invoker->m_k2_on_reset, nullptr);
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