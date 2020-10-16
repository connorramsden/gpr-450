// Copyright 2020 Connor Ramsden


#include "CJR_SpatialPose.h"

USpatialPose::USpatialPose()
{
	// Reset does the same thing the Constructor should do
	ResetPose();

	return;
}

void USpatialPose::Init(FTransform TMat, FVector O, FVector S, FVector TVec)
{
	SetTransform(TMat);
	SetOrientation(O);
	SetScale(S);
	SetTranslation(TVec);

	return;
}

void USpatialPose::ResetPose()
{
	// Set Transform to Identity matrix
	Transform = FTransform::Identity;

	Orientation = FVector4(0.f, 0.f, 0.f, 1.f);
	
	// Dq = FDualQuat(FQuat(0.f, 0.f, 0.f, 1.f), FQuat(0.f, 0.f, 0.f, 0.f));

	// Set Rotation to (0, 0, 0)
	Rotation = FVector::ZeroVector;
	// Set Scale to (1, 1, 1)
	Scale = FVector::OneVector;
	// Set Translation to (0, 0, 0)
	Translation = FVector::ZeroVector;

	return;
}

USpatialPose * PoseCopy(USpatialPose & OtherPose)
{
	// Create the Pose to be returned
	USpatialPose * OutPose = NewObject<USpatialPose>();

	// Copy OtherPose's values to the OutPose
	OutPose->SetTransform(OtherPose.GetTransform());
	OutPose->SetOrientation(OtherPose.GetOrientation());
	OutPose->SetScale(OtherPose.GetScale());
	OutPose->SetTranslation(OtherPose.GetTranslation());

	// Done, return the Pose
	return OutPose;
}

void PoseConvert(USpatialPose & PoseIn, EPoseChannel Channel, EPoseOrder Order)
{
	// Check fucking slides lol
	FMatrix rx, ry, rz, r;

	switch(Order)
	{
		case ESpatialPoseEulerOrder::PoseEulerOrder_xyz:
			break;
		case ESpatialPoseEulerOrder::PoseEulerOrder_yzx:
			break;
		case ESpatialPoseEulerOrder::PoseEulerOrder_zxy:
			break;
		case ESpatialPoseEulerOrder::PoseEulerOrder_yxz:
			break;
		case ESpatialPoseEulerOrder::PoseEulerOrder_xzy:
			break;
		case ESpatialPoseEulerOrder::PoseEulerOrder_zyx:
			break;
	}

	
}

USpatialPose * PoseConcat(USpatialPose & Lhs, USpatialPose & RHS)
{
	// Create the Pose to be returned
	USpatialPose * OutPose = NewObject<USpatialPose>();

	// Calculate & Set Concat'd values for O, S, & T
	OutPose->SetRotation(Lhs.GetRotation() + RHS.GetRotation());
	OutPose->SetScale(Lhs.GetScale() * RHS.GetScale());
	OutPose->SetTranslation(Lhs.GetTranslation() + RHS.GetTranslation());

	// Done, return the Pose
	return OutPose;
}

USpatialPose * PoseLerp(USpatialPose & Pose0, USpatialPose & Pose1, float U)
{
	// Create the Pose to be returned
	USpatialPose * OutPose = NewObject<USpatialPose>();

	// Calculate LERP'd values for O, S, & T
	const FVector OutRotation = FMath::Lerp(Pose0.GetRotation(), Pose1.GetRotation(), U);
	const FVector OutScale = FMath::Lerp(Pose0.GetScale(), Pose1.GetScale(), U);
	const FVector OutTrans = FMath::Lerp(Pose0.GetTranslation(), Pose1.GetTranslation(), U);

	// Set calculated values for return'd pose
	OutPose->SetRotation(OutRotation);
	OutPose->SetScale(OutScale);
	OutPose->SetTranslation(OutTrans);

	// Done, return the Pose
	return OutPose;
}
