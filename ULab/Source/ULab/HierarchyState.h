// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "Hierarchy.h"
#include "SpatialPose.h"

#include "HierarchyState.generated.h"

// A simpe wrapper for a generic array of spatial poses
USTRUCT()
struct ULAB_API FHierarchyPose
{
	GENERATED_BODY()

protected:
	TArray<FSpatialPose> SpatialPose;

public:
	FHierarchyPose();
	~FHierarchyPose();
};

USTRUCT()
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
	TArray<FSpatialPose> SpatialPosePool;

	// An array of hierarchical poses (referencing ^ spatial poses)
	// Similar to a keyframe pool for the whole hierarchy. 
	// Organizes individual node poses.
	TArray<FHierarchyPose> HierarchicalPoses;

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
	FHierarchyPoseGroup();
	~FHierarchyPoseGroup();
};

USTRUCT()
struct ULAB_API FHierarchyState
{
	GENERATED_BODY()

protected:
	FHierarchy * Hierarchy;
	FHierarchyPose * SamplePose;
	FHierarchyPose * LocalSpacePose;
	FHierarchyPose * ObjectSpacePose;

public:
	FORCEINLINE FHierarchy * GetHierarchy() const { return Hierarchy; }

public:
	FHierarchyState();
	~FHierarchyState();
};