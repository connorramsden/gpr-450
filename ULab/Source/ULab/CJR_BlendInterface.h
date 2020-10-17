// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "CJR_SpatialPose.h"
#include "UObject/NoExportTypes.h"
#include "CJR_BlendInterface.generated.h"

typedef USpatialPose USPose;

/**
 * 
 */
UCLASS

()
class ULAB_API UCJR_BlendInterface final : public UObject
{
	GENERATED_BODY()

	// Fundamental Operations
	static USPose* SPoseOpIdentity();
	static USpatialPose& SPoseOpConstruct(USPose& Pose, FVector Rotation, FVector Scale, FVector Translation);
	static USpatialPose& SPoseOpCopy(USPose& PoseOut, USPose* PoseIn);
	static USpatialPose& SPoseOpInvert(USPose& Pose);
	static USpatialPose& SPoseOpConcat(USPose& Lhs, USPose& Rhs);
	static USpatialPose& SPoseOpNearest(USPose& Pose0, USPose& Pose1, const float U);
	static USpatialPose& SPoseOpLerp(USPose& Pose0, USPose& Pose1, const float U);
	static USpatialPose& SPoseOpCubic(USPose& Pose0, USPose& Pose1, USPose& Pose2,
	                                  USPose& Pose3, const float U);

	// Derivative Operations
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
};
