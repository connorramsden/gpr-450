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
	USpatialPose* Pose;

public:
	UHierarchyPose();
	~UHierarchyPose();

	void Init();

	void PoseReset(const int NodeCount);
	void PoseConvert();
	void PoseRestore();
	void PoseCopy();
	void PoseConcat();
	void PoseLerp();

public: // Getters & Setters
	FORCEINLINE USpatialPose* GetPose() const { return Pose; }
	FORCEINLINE void SetPose(USpatialPose* NewP) { Pose = NewP; }
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
	FHPosePool HPose;

	// Spatial Poses
	UPROPERTY()
	FSPosePool Pose;

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

	void Init(UHierarchy* NewHier, const int PoseCount, const ESpatialPoseEulerOrder NewOrder);
};

UCLASS()
class ULAB_API UHierarchyState final : public UObject
{
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

	void Init();

	void UpdateObjectInverse();
	void UpdateObjectBindToCurrent();
};
