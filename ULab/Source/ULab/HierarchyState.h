// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "Hierarchy.h"
#include "SpatialPose.h"

#include "HierarchyState.generated.h"

typedef TArray<USpatialPose *> SPosePool;

// A simpe wrapper for a generic array of spatial poses
UCLASS()
class ULAB_API UHierarchyPose : public UObject
{
	GENERATED_BODY()

protected:
	SPosePool Pool;

public:
	FORCEINLINE SPosePool GetPosePool() { return Pool; }
public:
	UHierarchyPose();
	~UHierarchyPose();
};

UCLASS()
class ULAB_API UHierarchyPoseGroup : public UObject
{
	GENERATED_BODY()

protected:
	// The hierarchy associated with this spatial data (organization of poses)
	// The pool itself describes the spatial properties of this hierarchy
	UHierarchy * Hierarchy;

	// Actual array of individual node poses
	// Similar to a keyframe pol for all poses for this hierarhy & nodes
	// TLDR: Set of all poses for all nodes
	SPosePool SpatialPosePool;

	// An array of hierarchical poses (referencing ^ spatial poses)
	// Similar to a keyframe pool for the whole hierarchy. 
	// Organizes individual node poses.
	TArray<UHierarchyPose *> HierarchicalPoses;

	// Array of transforamtion channels for each node in the hierarchy
	TArray<SpatialPoseChannel> Channels;

	// Global flag for the pool that describes the concatenation order
	SpatialPoseEulerOrder EulerOrder;

	// # of Hierarchical Poses
	int HPoseCount;

	// Total # of Spatial Poses
	// HPoseCount * HNumNodes
	int SPoseCount;

public:
	UHierarchyPoseGroup();
	~UHierarchyPoseGroup();
};

UCLASS()
class ULAB_API UHierarchyState : public UObject
{
	GENERATED_BODY()

protected:
	UHierarchy * Hierarchy;
	UHierarchyPose * SamplePose;
	UHierarchyPose * LocalSpacePose;
	UHierarchyPose * ObjectSpacePose;

public:
	FORCEINLINE UHierarchy * GetHierarchy() { return Hierarchy; }
	FORCEINLINE UHierarchyPose * GetSample() { return SamplePose; }
	FORCEINLINE UHierarchyPose * GetLocal() { return LocalSpacePose; }
	FORCEINLINE UHierarchyPose * GetObject() { return ObjectSpacePose; }

public:
	UHierarchyState();
	~UHierarchyState();
};