// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CJR_Hierarchy.h"
#include "CJR_SpatialPose.h"

#include "CJR_HierarchyState.generated.h"

/**
 * A single pose for a collection of nodes
 * Makes algorithms easier to keep this as a sep. data type.
 */
UCLASS()
class ULAB_API UHierarchyPose final : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<USpatialPose*> Pose;

public:
	UHierarchyPose();
	~UHierarchyPose();

	void Init(const int NumPoses);

	void PoseReset(const int NodeCount);
	void PoseConvert(const int NodeCount, ESpatialPoseChannel Channel, ESpatialPoseEulerOrder Order);
	void PoseRestore(const int NodeCount, ESpatialPoseChannel Channel, ESpatialPoseEulerOrder Order);
	void PoseCopy(UHierarchyPose* PoseIn, const int NodeCount);
	void PoseConcat(UHierarchyPose* Other, const int NodeCount);
	void PoseLerp(UHierarchyPose* Other, const int NodeCount, const float U);

public: // Getters & Setters
	FORCEINLINE TArray<USpatialPose*> GetPose() const { return Pose; }
	FORCEINLINE void UpdatePose(USpatialPose* NewP, const int Index) { Pose[Index] = NewP; }
	FORCEINLINE void SetPose(const TArray<USpatialPose*> NewP) { Pose = NewP; }
};

typedef TArray<USpatialPose*> FSPosePool;
typedef TArray<UHierarchyPose*> FHPosePool;

/**
 * Pose Group
 */

UCLASS()
class ULAB_API UHierarchyPoseGroup final : public UObject
{
	GENERATED_BODY()

protected:
	// Pointer to Hierarchy
	UPROPERTY()
	UHierarchy* Hierarchy;

	// Hierarchical Spatial Poses
	UPROPERTY()
	TArray<UHierarchyPose*> HPose;

	// Spatial Poses
	UPROPERTY()
	TArray<USpatialPose*> Pose;

	// Channels
	UPROPERTY()
	TArray<ESpatialPoseChannel> Channel;

	// Preferred Euler Order
	UPROPERTY()
	ESpatialPoseEulerOrder Order;

	// Number of Hierarchical Poses
	UPROPERTY()
	int HPoseCount;

	// Total Number of Spatial Poses
	UPROPERTY()
	int PoseCount;

public:
	UHierarchyPoseGroup();
	~UHierarchyPoseGroup();

	void Init(UHierarchy* NewHier, const int NewCount, const ESpatialPoseEulerOrder NewOrder);
};

UCLASS()
class ULAB_API UHierarchyState final : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	UHierarchy* Hierarchy;

	UPROPERTY()
	UHierarchyPose* LocalSpace;

	UPROPERTY()
	UHierarchyPose* ObjectSpace;

	UPROPERTY()
	UHierarchyPose* ObjectSpaceInverse;

	UPROPERTY()
	UHierarchyPose* ObjectSpaceBindToCurrent;

public:
	UHierarchyState();
	~UHierarchyState();

	void Init(UHierarchy* Hier);

	void UpdateObjectInverse();
	void UpdateObjectBindToCurrent();

public:
	FORCEINLINE UHierarchy* GetHierarchy() const { return Hierarchy; }
	FORCEINLINE UHierarchyPose* GetLocal() const { return LocalSpace; }
	FORCEINLINE UHierarchyPose* GetObject() const { return ObjectSpace; }
	FORCEINLINE UHierarchyPose* GetObjectInv() const { return ObjectSpaceInverse; }
	FORCEINLINE UHierarchyPose* GetObjectBind() const { return ObjectSpaceBindToCurrent; }
};
