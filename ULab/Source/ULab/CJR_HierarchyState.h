// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "CJR_Hierarchy.h"
#include "CJR_SpatialPose.h"

#include "CJR_Hierarchy.generated.h"

/**
 * A set of poses for a collection of nodes.
 * Makes algorithms easier to keep this separate.
 */

USTRUCT()
struct ULAB_API FHierarchyPose
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<FSpatialPose> Pose;

public:
	bool bIsInitialized;

	/// Ctor & Dtor ///
	FHierarchyPose();
	~FHierarchyPose();

	/// GETTERS & SETTERS ///
	FORCEINLINE FSpatialPose GetPose(const int Index) {return Pose[Index];}
	FORCEINLINE TArray<FSpatialPose> GetPoses() {return Pose;}
	FORCEINLINE int GetNumPoses() {return Pose.Num();}
	
	/// METHODS ///
	
	void Init(const int NumPoses);

	void PoseReset(const int NodeCount, const int FirstIndex = 0);
	void PoseConvert(EPoseChannel Channel, EPoseOrder Order, const int NodeCount, const int FirstIndex = 0);
	void PoseRestore(EPoseChannel Channel, EPoseOrder Order, const int NodeCount, const int FirstIndex = 0);
	void PoseCopy(FHierarchyPose Other, const int NodeCount, const int FirstIndex = 0);
	void PoseConcat(FHierarchyPose Other, const int NodeCount, const int FirstIndex = 0);
	void PoseLerp(FHierarchyPose Other, const float U, const int NodeCount, const int FirstIndex = 0);
};

typedef TArray<FSpatialPose> FSPosePool;
typedef TArray<FHierarchyPose> FHPosePool;

/**
 * Pose Group
 */

USTRUCT()
struct ULAB_API FHierarchyPoseGroup
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FHierarchy Hierarchy;
	UPROPERTY()
	TArray<FHierarchyPose> HPose;
	UPROPERTY()
	TArray<FSpatialPose> Pose;

	UPROPERTY()
	TArray<ESpatialPoseChannel> Channel;

	UPROPERTY()
	ESpatialPoseEulerOrder Order;

	UPROPERTY()
	int HPoseCount;

	UPROPERTY()
	int PoseCount;
public:
	bool bIsInitialized;

	FHierarchyPoseGroup();
	~FHierarchyPoseGroup();

	void Init(FHierarchy NewH, const int NewC, const EPoseOrder NewO);
};

USTRUCT()
struct ULAB_API FHierarchyState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FHierarchy Hierarchy;
	UPROPERTY()
	FHierarchyPose LocalSpace;
	UPROPERTY()
	FHierarchyPose ObjectSpace;
	UPROPERTY()
	FHierarchyPose ObjectSpaceInv;
	UPROPERTY()
	FHierarchyPose ObjectSpaceBindToCurrent;

public:
	FHierarchyState();
	~FHierarchyState();

	void Init(FHierarchy NewH);
	void UpdateObjectInverse();
	void UpdateObjectBindToCurrent();
};
