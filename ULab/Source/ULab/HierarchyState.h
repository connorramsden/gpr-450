// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "Hierarchy.h"
#include "SpatialPose.h"

#include "HierarchyState.generated.h"

typedef TArray<FSpatialPose> SPosePool;
typedef SpatialPoseEulerOrder PoseOrder;

// A simpe wrapper for a generic array of spatial poses
USTRUCT(BlueprintType)
struct ULAB_API FHierarchyPose
{
	GENERATED_BODY()

protected:
	SPosePool Pool;

public:
	FORCEINLINE SPosePool GetPosePool() { return Pool; }
public:
	FHierarchyPose();
	~FHierarchyPose();
};

USTRUCT(BlueprintType)
struct ULAB_API FHierarchyPoseGroup
{
	GENERATED_BODY()

protected:
	// The hierarchy associated with this spatial data (organization of poses)
	// The pool itself describes the spatial properties of this hierarchy
	FHierarchy Hierarchy;

	// Actual array of individual node poses
	// Similar to a keyframe pol for all poses for this hierarhy & nodes
	// TLDR: Set of all poses for all nodes
	SPosePool SpatialPosePool;

	// An array of hierarchical poses (referencing ^ spatial poses)
	// Similar to a keyframe pool for the whole hierarchy. 
	// Organizes individual node poses.
	TArray<FHierarchyPose> HierarchicalPoses;

	// Array of transforamtion channels for each node in the hierarchy
	TArray<SpatialPoseChannel> Channels;

	// Global flag for the pool that describes the concatenation order
	PoseOrder EulerOrder;

	// # of Hierarchical Poses
	int HPoseCount;

	// Total # of Spatial Poses
	// HPoseCount * HNumNodes
	int SPoseCount;

public:
	FORCEINLINE int GetHPoseCount() const { return HPoseCount; }
	FORCEINLINE int GetSPoseCount() const { return SPoseCount; }

public:
	FHierarchyPoseGroup();
	FHierarchyPoseGroup(FHierarchy NewHier, int NumPoses);
	~FHierarchyPoseGroup();
};

USTRUCT(BlueprintType)
struct ULAB_API FHierarchyState
{
	GENERATED_BODY()

protected:
	FHierarchy Hierarchy;
	FHierarchyPose SamplePose;
	FHierarchyPose LocalSpacePose;
	FHierarchyPose ObjectSpacePose;

public:
	FORCEINLINE FHierarchy GetHierarchy() { return Hierarchy; }
	FORCEINLINE FHierarchyPose GetSample() { return SamplePose; }
	FORCEINLINE FHierarchyPose GetLocal() { return LocalSpacePose; }
	FORCEINLINE FHierarchyPose GetObject() { return ObjectSpacePose; }

public:
	FHierarchyState();
	~FHierarchyState();
};