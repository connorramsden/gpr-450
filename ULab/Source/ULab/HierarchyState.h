// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Hierarchy.h"
#include "SpatialPose.h"
#include <Math/DualQuat.h>

#include "HierarchyState.generated.h"

typedef TArray<USpatialPose *> SPosePool;
typedef TArray<UHierarchicalPose *> HPosePool;

/**
 * A neat wrapper for a collection of poses
 * Decoupled context for a Hierarchy
 * Represents teh spatial description of a hierarchy at some point in time
 */
UCLASS()
class ULAB_API UHierarchicalPose : public UObject
{
	GENERATED_BODY()

protected:
	TArray<USpatialPose *> Poses;

public:
	UHierarchicalPose();
	~UHierarchicalPose();

public:
	FORCEINLINE SPosePool GetPoses() { return Poses; }
	FORCEINLINE USpatialPose * GetPose(int Index) { return Poses[Index]; }

public:
	// Init given a number of poses
	void Init(int NumPoses);
	// Init given an array of poses
	void Init(TArray<USpatialPose *> InitPoses);
	// Update the pose at the passed index
	void SetPose(USpatialPose * Pose, int Index);
	// Add a new pose to the end of the pool
	void AddPose(USpatialPose * Pose);
	// Reset all poses in the pool
	void ResetPoses();
	void ConvertPoses(int NodeCount, PoseChannel Channel, PoseOrder Order);
};

/**
 * A pool or group of hierarchical poses & their individual node poses
 */
UCLASS()
class ULAB_API UHierarchyPosePool : public UObject
{
	GENERATED_BODY()

protected:
	// The hierarchy associated with this spatial data. 
	// The whole pool describes the spatial properties of the hierarchy.
	// Thie hierarchy describes the organization of poses.
	UHierarchy * Hierarchy;

	// The actual array of individual node poses.
	// The set of all poses for all nodes.
	TArray<USpatialPose *> SpatialPoses;

	// An array of hierarchical poses. References SpatialPoses.
	// This organizes the individual node poses.
	TArray<UHierarchicalPose *> HierarchicalPoses;

	// An array of transformation channels for each node in the Hierarchy
	// Describes individual pose transformation components
	// Ex: Rotation X, Translation XYZ, etc.)
	TArray<PoseChannel> Channels;

	// Some global flag for the pool
	// Describes the concatenation order of orientation channel
	PoseOrder EulerOrder;

public:
	UHierarchyPosePool();
	~UHierarchyPosePool();

public:
	FORCEINLINE UHierarchy * GetHierarchy() { return Hierarchy; }
	FORCEINLINE SPosePool GetSpatial() { return SpatialPoses; }
	FORCEINLINE USpatialPose * GetSPose(int Index) { return SpatialPoses[Index]; }
	FORCEINLINE HPosePool GetHierarchical() { return HierarchicalPoses; }
	FORCEINLINE UHierarchicalPose * GetHPose(int Index) { return HierarchicalPoses[Index]; }
	FORCEINLINE TArray<PoseChannel> GetChannels() { return Channels; }
	FORCEINLINE PoseChannel GetChannel(int Index) { return Channels[Index]; }
	FORCEINLINE PoseOrder GetOrder() { return EulerOrder; }
};

/**
 * A
 */
UCLASS()
class ULAB_API UHierarchyState : public UObject
{
	GENERATED_BODY()

protected:
	UHierarchy * Hierarchy;

	UHierarchicalPose * SamplePose;
	UHierarchicalPose * LocalSpacePose;
	UHierarchicalPose * ObjectSpacePose;

public:
	UHierarchyState();
	~UHierarchyState();

public:
	FORCEINLINE UHierarchy * GetHierarchy() { return Hierarchy; }
	FORCEINLINE UHierarchicalPose * GetSample() { return SamplePose; }
	FORCEINLINE UHierarchicalPose * GetLocal() { return LocalSpacePose; }
	FORCEINLINE UHierarchicalPose * GetObject() { return ObjectSpacePose; }
	FORCEINLINE void SetHierarchy(UHierarchy * NewHier) { Hierarchy = NewHier; }
	FORCEINLINE void SetSample(UHierarchicalPose * NewPose) { SamplePose = NewPose; }
	FORCEINLINE void SetLocal(UHierarchicalPose * NewPose) { LocalSpacePose = NewPose; }
	FORCEINLINE void SetObject(UHierarchicalPose * NewPose) { ObjectSpacePose = NewPose; }

public:
	// Iniitalize the state given the passed hierarchy
	void Init(UHierarchy * NewHier);
	// Update inverse object-space matrices
	void UpdateObjectInverse();
};
