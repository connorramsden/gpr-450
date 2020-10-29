// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "CJR_SpatialPose.h"
#include "CJR_HierarchyState.h"
#include "CJR_BlendInterface.generated.h"

typedef FSpatialPose FSPose;
typedef FHierarchyPose FHPose;

/***
 * 
 */

USTRUCT()
struct ULAB_API FBlendInterface
{
	GENERATED_BODY()

	/// FUNDAMENTAL SPATIAL OPERATIONS ///
	static FSpatialPose SPoseOpIdentity();
	static FSpatialPose SPoseOpConstruct(FSPose& Pose, FVector T, FVector R, FVector S);
	static FSpatialPose SPoseOpCopy(FSPose& PoseOut, FSPose PoseIn);
	static FSpatialPose SPoseOpInvert(FSPose& Pose);
	static FSpatialPose SPoseOpConcat(FSPose& Lhs, FSPose& Rhs);
	static FSpatialPose SPoseOpNearest(FSPose& Pose0, FSPose& Pose1, const float U);
	static FSpatialPose SPoseOpLerp(FSPose& Pose0, FSPose& Pose1, const float U);
	static FSpatialPose SPoseOpCubic(FSPose& Pose0, FSPose& Pose1, FSPose& Pose2, FSPose& Pose3, const float U);

	/// FUNDAMENTAL HIERARCHICAL OPERATIONS ///
	static FHierarchyPose HPoseOpIdentity(const int NumPoses);
	static FHierarchyPose HPoseOpConstruct(FHPose& Pose, FVector T, FVector R, FVector S, const int NumPoses,
	                                       const int FirstIndex = 0);
	static FHierarchyPose HPoseOpCopy(FHPose& PoseOut, FHPose PoseIn, const int NumPoses, const int FirstIndex = 0);
	static FHierarchyPose HPoseOpInvert(FHPose& Pose, const int NumPoses, const int FirstIndex = 0);
	static FHierarchyPose HPoseOpConcat(FHPose& Lhs, FHPose& Rhs, const int NumPoses, const int FirstIndex = 0);
	static FHierarchyPose HPoseOpNearest(FHPose& Pose0, FHPose& Pose1, const float U, const int NumPoses,
	                                     const int FirstIndex = 0);
	static FHierarchyPose HPoseOpLerp(FHPose& Pose0, FHPose& Pose1, const float U, const int NumPoses,
	                                  const int FirstIndex = 0);
	static FHierarchyPose HPoseOpCubic(FHPose& Pose0, FHPose& Pose1, FHPose& Pose2, FHPose& Pose3, const float U,
	                                   const int NumPoses, const int FirstIndex = 0);

	/// DERIVATIVE SPATIAL OPERATIONS ///
	static FSpatialPose SPoseOpDeconcat(FSPose& Lhs, FSPose& Rhs);
	static FSpatialPose SPoseOpScale(FSPose& Pose, const float U);
	static FSpatialPose SPoseOpTri(FSPose& Pose0, FSPose& Pose1, FSPose& Pose2, const float U0, const float U1);
	static FSpatialPose SPoseOpBinearest(FSPose& Pose0, FSPose& Pose1, FSPose& Pose2, FSPose& Pose3, const float U0,
	                                     const float U1, const float U);
	static FSpatialPose SPoseOpBilerp(FSPose& Pose0, FSPose& Pose1, FSPose& Pose2, FSPose& Pose3, const float U0,
	                                  const float U1, const float U);
	static FSpatialPose SPoseOpBicubic(FSPose& PoseP0, FSPose& PoseP1, FSPose& PoseP2, FSPose& PoseP3,
	                                   FSPose& PoseN0, FSPose& PoseN1, FSPose& PoseN2, FSPose& PoseN3,
	                                   FSPose& Pose00, FSPose& Pose01, FSPose& Pose02, FSPose& Pose03,
	                                   FSPose& Pose10, FSPose& Pose11, FSPose& Pose12, FSPose& Pose13,
	                                   const float U0, const float U1, const float U2, const float U3, const float U);

	/// DERIVATIVE HIERARCHICAL OPERATIONS ///
	static FHierarchyPose HPoseOpDeconcat(FHPose& Lhs, FHPose& Rhs, const int NumPoses, const int FirstIndex = 0);
	static FHierarchyPose HPoseOpScale(FHPose& Pose, const float U, const int NumPoses, const int FirstIndex = 0);
	static FHierarchyPose HPoseOpTri(FHPose& Pose0, FHPose& Pose1, FHPose& Pose2, const float U0, const float U1,
	                                 const int NumPoses, const int FirstIndex = 0);
	static FHierarchyPose HPoseOpBinearest(FHPose& Pose0, FHPose& Pose1, FHPose& Pose2, FHPose& Pose3, const float U0,
	                                       const float U1, const float U, const int NumPoses, const int FirstIndex = 0);
	static FHierarchyPose HPoseOpBilerp(FHPose& Pose0, FHPose& Pose1, FHPose& Pose2, FHPose& Pose3, const float U0,
	                                    const float U1, const float U, const int NumPoses, const int FirstIndex = 0);
	static FHierarchyPose HPoseOpBicubic(FHPose& PoseP0, FHPose& PoseP1, FHPose& PoseP2, FHPose& PoseP3,
	                                     FHPose& PoseN0, FHPose& PoseN1, FHPose& PoseN2, FHPose& PoseN3,
	                                     FHPose& Pose00, FHPose& Pose01, FHPose& Pose02, FHPose& Pose03,
	                                     FHPose& Pose10, FHPose& Pose11, FHPose& Pose12, FHPose& Pose13,
	                                     const float U0, const float U1, const float U2, const float U3, const float U,
	                                     const int NumPoses, const int FirstIndex = 0);
};
