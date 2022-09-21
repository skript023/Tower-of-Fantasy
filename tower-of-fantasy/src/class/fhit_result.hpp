#pragma once
#include "fname_pool.hpp"
#include "vector.hpp"
#include "enums.hpp"
#include "weak_object.hpp"

namespace big
{
	struct FHitResult
	{
		/** \brief Indicates if this hit was a result of blocking collision. If false, there was no hit or it was an overlap/touch instead. */
		uint32_t bBlockingHit : 1;

		/**
		 * \brief Whether the trace started in penetration, i.e. with an initial blocking overlap.
		 * In the case of penetration, if PenetrationDepth > 0.f, then it will represent the distance along the Normal vector that will result in
		 * minimal contact between the swept shape and the object that was hit. In this case, ImpactNormal will be the normal opposed to movement at that location
		 * (ie, Normal may not equal ImpactNormal). ImpactPoint will be the same as Location, since there is no single impact point to report.
		 */
		uint32_t bStartPenetrating : 1;

		/**
		 * \brief 'Time' of impact along trace direction (ranging from 0.0 to 1.0) if there is a hit, indicating time between TraceStart and TraceEnd.
		 * For swept movement (but not queries) this may be pulled back slightly from the actual time of impact, to prevent precision problems with adjacent geometry.
		 */
		float Time;

		/** \brief The distance from the TraceStart to the ImpactPoint in world space. This value is 0 if there was an initial overlap (trace started inside another colliding object). */
		float Distance;

		/**
		 * \brief The location in world space where the moving shape would end up against the impacted object, if there is a hit. Equal to the point of impact for line tests.
		 * Example: for a sphere trace test, this is the point where the center of the sphere would be located when it touched the other object.
		 * For swept movement (but not queries) this may not equal the final location of the shape since hits are pulled back slightly to prevent precision issues from overlapping another surface.
		 */
		FVector_NetQuantize Location;

		/**
		 * \brief Location in world space of the actual contact of the trace shape (box, sphere, ray, etc) with the impacted object.
		 * Example: for a sphere trace test, this is the point where the surface of the sphere touches the other object.
		 * @note: In the case of initial overlap (bStartPenetrating=true), ImpactPoint will be the same as Location because there is no meaningful single impact point to report.
		 */
		FVector_NetQuantize ImpactPoint;

		/**
		 * \brief Normal of the hit in world space, for the object that was swept. Equal to ImpactNormal for line tests.
		 * This is computed for capsules and spheres, otherwise it will be the same as ImpactNormal.
		 * Example: for a sphere trace test, this is a normalized vector pointing in towards the center of the sphere at the point of impact.
		 */
		FVector_NetQuantizeNormal Normal;

		/**
		 * \brief Normal of the hit in world space, for the object that was hit by the sweep, if any.
		 * For example if a box hits a flat plane, this is a normalized vector pointing out from the plane.
		 * In the case of impact with a corner or edge of a surface, usually the "most opposing" normal (opposed to the query direction) is chosen.
		 */
		FVector_NetQuantizeNormal ImpactNormal;

		/**
		 * \brief Start location of the trace.
		 * For example if a sphere is swept against the world, this is the starting location of the center of the sphere.
		 */
		FVector_NetQuantize TraceStart;

		/**
		 * \brief End location of the trace; this is NOT where the impact occurred (if any), but the furthest point in the attempted sweep.
		 * For example if a sphere is swept against the world, this would be the center of the sphere if there was no blocking hit.
		 */
		FVector_NetQuantize TraceEnd;

		/**
		  * \brief If this test started in penetration (bStartPenetrating is true) and a depenetration vector can be computed,
		  * this value is the distance along Normal that will result in moving out of penetration.
		  * If the distance cannot be computed, this distance will be zero.
		  */
		float PenetrationDepth;

		/** Extra data about item that was hit (hit primitive specific). */
		int32_t Item;

		/**
		 * \brief Physical material that was hit.
		 * \param Must set bReturnPhysicalMaterial on the swept PrimitiveComponent or in the query params for this to be returned.
		 */
		TWeakObjectPtr<class UPhysicalMaterial> PhysMaterial;

		/** \brief Actor hit by the trace. */
		TWeakObjectPtr<class AActor> Actor;

		/** \brief PrimitiveComponent hit by the trace. */
		TWeakObjectPtr<class UPrimitiveComponent> Component;

		/** \brief Name of bone we hit (for skeletal meshes). */
		FName BoneName;

		/** \brief Face index we hit (for complex hits with triangle meshes). */
		int32_t FaceIndex;

		char padding[0xC];

		FHitResult()
		{
			Init();
		}

		explicit FHitResult(float InTime)
		{
			Init();
			Time = InTime;
		}

		explicit FHitResult(EForceInit InInit)
		{
			Init();
		}

		explicit FHitResult(ENoInit NoInit)
		{
		}

		explicit FHitResult(FVector Start, FVector End)
		{
			Init(Start, End);
		}

		/** Initialize empty hit result with given time. */
		FORCEINLINE void Init()
		{
			ZeroMemory(this, sizeof(FHitResult));
			Time = 1.f;
		}

		/** Initialize empty hit result with given time, TraceStart, and TraceEnd */
		FORCEINLINE void Init(FVector Start, FVector End)
		{
			ZeroMemory(this, sizeof(FHitResult));
			Time = 1.f;
			TraceStart = Start;
			TraceEnd = End;
		}

		/** Ctor for easily creating "fake" hits from limited data. */
		FHitResult(class AActor* InActor, class UPrimitiveComponent* InComponent, FVector const& HitLoc, FVector const& HitNorm);

		/** Reset hit result while optionally saving TraceStart and TraceEnd. */
		FORCEINLINE void Reset(float InTime = 1.f, bool bPreserveTraceData = true)
		{
			const FVector SavedTraceStart = TraceStart;
			const FVector SavedTraceEnd = TraceEnd;
			Init();
			Time = InTime;
			if (bPreserveTraceData)
			{
				TraceStart = SavedTraceStart;
				TraceEnd = SavedTraceEnd;
			}
		}

		/** Utility to return the Actor that owns the Component that was hit. */
		AActor* GetActor() const;

		/** Utility to return the Component that was hit. */
		UPrimitiveComponent* GetComponent() const;

		/** Optimized serialize function */
		bool NetSerialize(class FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

		/** Return true if there was a blocking hit that was not caused by starting in penetration. */
		FORCEINLINE bool IsValidBlockingHit() const
		{
			return bBlockingHit && !bStartPenetrating;
		}

		/** Static utility function that returns the first 'blocking' hit in an array of results. */
		static FHitResult* GetFirstBlockingHit(TArray<FHitResult>& InHits)
		{
			for (uint32_t HitIdx = 0; HitIdx < InHits.size(); HitIdx++)
			{
				if (InHits[HitIdx].bBlockingHit)
				{
					return &InHits[HitIdx];
				}
			}
			return nullptr;
		}

		/** Static utility function that returns the number of blocking hits in array. */
		static int32_t GetNumBlockingHits(const TArray<FHitResult>& InHits)
		{
			int32_t NumBlocks = 0;
			for (uint32_t HitIdx = 0; HitIdx < InHits.size(); HitIdx++)
			{
				if (InHits[HitIdx].bBlockingHit)
				{
					NumBlocks++;
				}
			}
			return NumBlocks;
		}

		/** Static utility function that returns the number of overlapping hits in array. */
		static int32_t GetNumOverlapHits(const TArray<FHitResult>& InHits)
		{
			return (InHits.size() - GetNumBlockingHits(InHits));
		}

		/**
		 * Get a copy of the HitResult with relevant information reversed.
		 * For example when receiving a hit from another object, we reverse the normals.
		 */
		static FHitResult GetReversedHit(const FHitResult& Hit)
		{
			FHitResult Result(Hit);
			Result.Normal = -Result.Normal;
			Result.ImpactNormal = -Result.ImpactNormal;
			return Result;
		}

		FString ToString() const;
	}; //size : 0x80 | size must be 0x8C
	static_assert(sizeof(FHitResult) == 0x8C);
}