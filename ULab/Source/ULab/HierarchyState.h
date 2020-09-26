// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "Hierarchy.h"
#include "SpatialPose.h"

#include "HierarchyState.generated.h"

// A simpe wrapper for a generic array of spatial poses
USTRUCT(BlueprintType)
struct ULAB_API FHierarchyPose
{
	GENERATED_BODY()

protected:
	TArray<FSpatialPose> Pool;

public:
	FORCEINLINE TArray<FSpatialPose> GetPosePool() { return Pool; }
public:
	FHierarchyPose();
	FHierarchyPose(TArray<FSpatialPose> NewPool);
	~FHierarchyPose();
};

USTRUCT(BlueprintType)
struct ULAB_API FHierarchyPoseGroup
{
	GENERATED_BODY()

protected:
	// The hierarchy associated with this spatial data (organization of poses)
	// The pool itself describes the spatial properties of this hierarchy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pose Group Components")
		FHierarchy Hierarchy;

	// Actual array of individual node poses
	// Similar to a keyframe pol for all poses for this hierarhy & nodes
	// TLDR: Set of all poses for all nodes
	TArray<FSpatialPose> SpatialPosePool;

	// An array of hierarchical poses (referencing ^ spatial poses)
	// Similar to a keyframe pool for the whole hierarchy. 
	// Organizes individual node poses.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pose Group Components")
		TArray<FHierarchyPose> HierarchicalPoses;

	// Array of transforamtion channels for each node in the hierarchy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pose Group Components")
		TArray<SpatialPoseChannel> Channels;

	// Global flag for the pool that describes the concatenation order
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pose Group Components")
		SpatialPoseEulerOrder EulerOrder;

	// # of Hierarchical Poses
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pose Group Components")
		int HPoseCount;

	// Total # of Spatial Poses
	// HPoseCount * HNumNodes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pose Group Components")
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
	FHierarchyState(FHierarchy NewHier, TArray<FHierarchyPose> Poses);
	~FHierarchyState();
};