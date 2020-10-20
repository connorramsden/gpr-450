// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "CJR_SpatialPose.h"
#include "CJR_HierarchyState.h"
#include "UObject/NoExportTypes.h"
#include "CJR_BlendInterface.generated.h"

typedef USpatialPose USPose;
typedef UHierarchyPose UHPose;

/**
 * 
 */
UCLASS()
class ULAB_API UCJR_BlendInterface final : public UObject
{
	GENERATED_BODY()

	// Fundamental Spatial Operations
	static USPose* SPoseOpIdentity();
	static USpatialPose& SPoseOpConstruct(USPose& Pose, FVector Rotation, FVector Scale, FVector Translation);
	static USpatialPose& SPoseOpCopy(USPose& PoseOut, USPose* PoseIn);
	static USpatialPose& SPoseOpInvert(USPose& Pose);
	static USpatialPose& SPoseOpConcat(USPose& Lhs, USPose& Rhs);
	static USpatialPose& SPoseOpNearest(USPose& Pose0, USPose& Pose1, const float U);
	static USpatialPose& SPoseOpLerp(USPose& Pose0, USPose& Pose1, const float U);
	static USpatialPose& SPoseOpCubic(USPose& Pose0, USPose& Pose1, USPose& Pose2,
	                                  USPose& Pose3, const float U);


	// Fundamental Hierarchical Operations
	static UHierarchyPose* HPoseOpIdentity(const int NumPoses);
	static UHierarchyPose& HPoseOpConstruct(UHPose& Pose, FVector Rotation, FVector Scale, FVector Translation,
	                                        const int NumPoses);
	static UHierarchyPose& HPoseOpCopy(UHPose& PoseOut, UHPose* PoseIn, const int NumPoses);
	static UHierarchyPose& HPoseOpInvert(UHPose& Pose, const int NumPoses);
	static UHierarchyPose& HPoseOpConcat(UHPose& Lhs, UHPose& Rhs, const int NumPoses);
	static UHierarchyPose* HPoseOpNearest(UHPose& Pose0, UHPose& Pose1, const float U, const int NumPoses);
	static UHierarchyPose& HPoseOpLerp(UHPose& Pose0, UHPose& Pose1, const float U, const int NumPoses);
	static UHierarchyPose* HPoseOpCubic(UHPose& Pose0, UHPose& Pose1, UHPose& Pose2,
	                                    UHPose& Pose3, const float U, const int NumPoses);

	// Derivative Spatial Operations
	static USpatialPose& SPoseOpDeconcat(USPose& Lhs, USPose& Rhs);
	static USpatialPose& SPoseOpScale(USPose& Pose, const float U);
	static USpatialPose& SPoseOpTri(USPose& Pose0, USPose& Pose1, USPose& Pose2, const float U1,
	                                const float U2);
	static USpatialPose& SPoseOpBinearest(USPose& Pose0, USPose& Pose1, USPose& Pose2, USPose& Pose3,
	                                      const float U0, const float U1, const float U);
	static USpatialPose& SPoseOpBilerp(USPose& Pose0, USPose& Pose1, USPose& Pose2, USPose& Pose3, const float U0,
	                                   const float U1, const float U);
	static USpatialPose& SPoseOpBicubic(USPose& PoseP0, USPose& PoseP1, USPose& PoseP2, USPose& PoseP3,
	                                    USPose& PoseN0, USPose& PoseN1, USPose& PoseN2, USPose& PoseN3,
	                                    USPose& Pose00, USPose& Pose01, USPose& Pose02, USPose& Pose03,
	                                    USPose& Pose10, USPose& Pose11, USPose& Pose12, USPose& Pose13,
	                                    const float U0, const float U1, const float U2, const float U3, const float U);


	// Derivative Hierarchical Poses
	static UHierarchyPose* HPoseOpDeconcat(UHPose& Lhs, UHPose& Rhs, const int NumPoses);
	static UHierarchyPose* HPoseOpScale(UHPose& Pose, const float U, const int NumPoses);
	static UHierarchyPose* HPoseOpTri(UHPose& Pose0, UHPose& Pose1, UHPose& Pose2, const float U1,
	                                  const float U2, const int NumPoses);
	static UHierarchyPose* HPoseOpBinearest(UHPose& Pose0, UHPose& Pose1, UHPose& Pose2, UHPose& Pose3,
	                                        const float U0, const float U1, const float U, const int NumPoses);
	static UHierarchyPose* HPoseOpBilerp(UHPose& Pose0, UHPose& Pose1, UHPose& Pose2, UHPose& Pose3, const float U0,
	                                     const float U1, const float U, const int NumPoses);
	static UHierarchyPose* HPoseOpBicubic(UHPose& PoseP0, UHPose& PoseP1, UHPose& PoseP2, UHPose& PoseP3,
	                                      UHPose& PoseN0, UHPose& PoseN1, UHPose& PoseN2, UHPose& PoseN3,
	                                      UHPose& Pose00, UHPose& Pose01, UHPose& Pose02, UHPose& Pose03,
	                                      UHPose& Pose10, UHPose& Pose11, UHPose& Pose12, UHPose& Pose13,
	                                      const float U0, const float U1, const float U2, const float U3,
	                                      const float U, const int NumPoses);
};
