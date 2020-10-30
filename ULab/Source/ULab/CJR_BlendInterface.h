// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "CJR_SpatialPose.h"
#include "CJR_HierarchyState.h"
#include "CJR_BlendInterface.generated.h"

typedef FSpatialPose FSPose;
typedef FHierarchyPose FHPose;

// No idea if this works in UE4C++ LOL
// Execution template
typedef void (*FSpatialPoseOpExec)(struct FBlendNode const BlendNode);

// Operation template for (almost) any Spatial Pose Operation
typedef FSpatialPose (*FSpatialPoseOp)(FSpatialPose PoseOut, ...);

USTRUCT()
struct ULAB_API FBlendNode
{
	GENERATED_BODY()
	// Execution Invocation
	FSpatialPoseOpExec Execution;

	// The operation itself
	FSpatialPoseOp Operation;

	// Output pose
	FSpatialPose PoseOut; // exactly one external pose referenced

	// Control poses
	TArray<FSpatialPose> PoseControl;

	// Parameters
	float const* U[8]; // up to 8 pointers, externally sourced

	// How many of the above do we have? (optional)
	int ControlCount, ParamCount;
};

USTRUCT()
struct ULAB_API FBlendTree
{
	GENERATED_BODY()
	// Tells us NumNodes and the Parent of each node
	FHierarchy BlendTreeDescriptor;

	// All blend nodes that are in this tree
	TArray<FBlendNode> Nodes;

	// We could also keep track of child indices if we wanted to
};

/// Execution Operations (Project 03) ///
// 0 Control Params, 0 Inputs
void SpatialPoseOpExec0C0I(FBlendNode BlendNode);
// 1 Control, 1 Input (ex: Scale)
void SpatialPoseOpExec1C1I(FBlendNode BlendNode);
// 2 Control, 0 Input (ex: ADD)
void SpatialPoseOpExec2C0I(FBlendNode BlendNode);
// 2 Control Params, 1 Input (ex: LERP)
void SpatialPoseOpExec2C1I(FBlendNode BlendNode);

/// FUNDAMENTAL SPATIAL OPERATIONS (Lab 03) ///
static FSpatialPose SPoseOpIdentity();
static FSpatialPose SPoseOpConstruct(FSPose Pose, FVector T, FVector R, FVector S);
static FSpatialPose SPoseOpCopy(FSPose PoseOut, FSPose PoseIn);
static FSpatialPose SPoseOpInvert(FSPose Pose);
static FSpatialPose SPoseOpConcat(FSPose Lhs, FSPose Rhs);
static FSpatialPose SPoseOpNearest(FSPose Pose0, FSPose Pose1, const float U);
static FSpatialPose SPoseOpLerp(FSPose Pose0, FSPose Pose1, const float U);
static FSpatialPose SPoseOpCubic(FSPose Pose0, FSPose Pose1, FSPose Pose2, FSPose Pose3, const float U);

/// FUNDAMENTAL HIERARCHICAL OPERATIONS (Lab 03)  ///
static FHierarchyPose HPoseOpIdentity(FHPose OutPose, const int NumPoses);
static FHierarchyPose HPoseOpConstruct(FHPose Pose, FVector T, FVector R, FVector S, const int NumPoses,
                                       const int FirstIndex = 0);
static FHierarchyPose HPoseOpCopy(FHPose PoseOut, FHPose PoseIn, const int NumPoses, const int FirstIndex = 0);
static FHierarchyPose HPoseOpInvert(FHPose Pose, const int NumPoses, const int FirstIndex = 0);
static FHierarchyPose HPoseOpConcat(FHPose Lhs, FHPose Rhs, const int NumPoses, const int FirstIndex = 0);
static FHierarchyPose HPoseOpNearest(FHPose OutPose, FHPose Pose0, FHPose Pose1, const float U,
                                     const int NumPoses, const int FirstIndex = 0);
static FHierarchyPose HPoseOpLerp(FHPose OutPose, FHPose Pose0, FHPose Pose1, const float U,
                                  const int NumPoses, const int FirstIndex = 0);
static FHierarchyPose HPoseOpCubic(FHPose OutPose, FHPose Pose0, FHPose Pose1, FHPose Pose2, FHPose Pose3,
                                   const float U, const int NumPoses, const int FirstIndex = 0);

/// DERIVATIVE SPATIAL OPERATIONS (Lab 03)  ///
static FSpatialPose SPoseOpDeconcat(FSPose Lhs, FSPose Rhs);
static FSpatialPose SPoseOpScale(FSPose Pose, const float U);
static FSpatialPose SPoseOpTri(FSPose Pose0, FSPose Pose1, FSPose Pose2, const float U0, const float U1);
static FSpatialPose SPoseOpBinearest(FSPose Pose0, FSPose Pose1, FSPose Pose2, FSPose Pose3, const float U0,
                                     const float U1, const float U);
static FSpatialPose SPoseOpBilerp(FSPose Pose0, FSPose Pose1, FSPose Pose2, FSPose Pose3, const float U0,
                                  const float U1, const float U);
static FSpatialPose SPoseOpBicubic(FSPose PoseP0, FSPose PoseP1, FSPose PoseP2, FSPose PoseP3,
                                   FSPose PoseN0, FSPose PoseN1, FSPose PoseN2, FSPose PoseN3,
                                   FSPose Pose00, FSPose Pose01, FSPose Pose02, FSPose Pose03,
                                   FSPose Pose10, FSPose Pose11, FSPose Pose12, FSPose Pose13,
                                   const float U0, const float U1, const float U2, const float U3, const float U);

/// DERIVATIVE HIERARCHICAL OPERATIONS (Lab 03)  ///
static FHierarchyPose HPoseOpDeconcat(FHPose OutPose, FHPose Lhs, FHPose Rhs, const int NumPoses,
                                      const int FirstIndex = 0);
static FHierarchyPose HPoseOpScale(FHPose OutPose, FHPose Pose, const float U, const int NumPoses,
                                   const int FirstIndex = 0);
static FHierarchyPose HPoseOpTri(FHPose OutPose, FHPose Pose0, FHPose Pose1, FHPose Pose2, const float U0,
                                 const float U1, const int NumPoses, const int FirstIndex = 0);
static FHierarchyPose HPoseOpBinearest(FHPose OutPose, FHPose Pose0, FHPose Pose1, FHPose Pose2, FHPose Pose3,
                                       const float U0, const float U1, const float U, const int NumPoses,
                                       const int FirstIndex = 0);
static FHierarchyPose HPoseOpBilerp(FHPose OutPose, FHPose Pose0, FHPose Pose1, FHPose Pose2, FHPose Pose3,
                                    const float U0, const float U1, const float U, const int NumPoses,
                                    const int FirstIndex = 0);
static FHierarchyPose HPoseOpBicubic(FHPose OutPose, FHPose PoseP0, FHPose PoseP1, FHPose PoseP2,
                                     FHPose PoseP3, FHPose PoseN0, FHPose PoseN1, FHPose PoseN2,
                                     FHPose PoseN3, FHPose Pose00, FHPose Pose01, FHPose Pose02,
                                     FHPose Pose03, FHPose Pose10, FHPose Pose11, FHPose Pose12,
                                     FHPose Pose13, const float U0, const float U1, const float U2, const float U3,
                                     const float U, const int NumPoses, const int FirstIndex = 0);

/// ADDITIONAL SPATIAL BLEND OPERATIONS (Project 03) ///
static FSpatialPose SPoseOpSmoothstep(FSPose Pose0, FSPose Pose1, const float U);
static FSpatialPose SPoseOpDescale(FSPose Pose, const float U);
static FSpatialPose SPoseOpConvert(FSPose Pose);
static FSpatialPose SPoseOpRestore(FSPose Pose);
static TArray<FTransform> SPoseOpFK(FHierarchyState State);
static TArray<FTransform> SPoseOpIK(FHierarchyState State);

/// ADDITIONAL HIERARCHICAL BLEND OPERATIONS (Project 03) ///
static FHierarchyPose HPoseOpSmoothstep(FHPose PoseOut, FHPose Pose0, FHPose Pose1, const float U, const int NumPoses,
                                        const int FirstIndex = 0);
static FHierarchyPose HPoseOpDescale(FHPose PoseOut, FHPose Pose, const float U, const int NumPoses,
                                     const int FirstIndex = 0);
static FHierarchyPose HPoseOpConvert(FHPose PoseOut, FHPose Pose, const int NumPoses, const int FirstIndex = 0);
static FHierarchyPose HPoseOpRestore(FHPose PoseOut, FHPose Pose, const int NumPoses, const int FirstIndex = 0);
// static TArray<FTransform> HPoseOpFK(TArray<FTransform> PoseOut, FHierarchyState State, const int NumPoses, const int FirstIndex = 0);
// static TArray<FTransform> HPoseOpIK(TArray<FTransform> PoseOut, FHierarchyState State, const int NumPoses, const int FirstIndex = 0);
