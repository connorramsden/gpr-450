// Copyright 2020 Connor Ramsden


#include "SpatialPose.h"

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

	// Set Orientation to (0, 0, 0)
	Orientation = FVector::ZeroVector;
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

FMatrix PoseConvert(USpatialPose & PoseIn, PoseChannel Channel, PoseOrder Order)
{
	return FMatrix();
}

USpatialPose * PoseConcat(USpatialPose & lhs, USpatialPose & rhs)
{
	// Create the Pose to be returned
	USpatialPose * OutPose = NewObject<USpatialPose>();

	// Calculate & Set Concat'd values for O, S, & T
	OutPose->SetOrientation(lhs.GetOrientation() + rhs.GetOrientation());
	OutPose->SetScale(lhs.GetScale() * rhs.GetScale());
	OutPose->SetTranslation(lhs.GetTranslation() + rhs.GetTranslation());

	// Done, return the Pose
	return OutPose;
}

USpatialPose * PoseLerp(USpatialPose & Pose0, USpatialPose & Pose1, float u)
{
	// Create the Pose to be returned
	USpatialPose * OutPose = NewObject<USpatialPose>();

	// Calculate LERP'd values for O, S, & T
	FVector OutOrientation = FMath::Lerp(Pose0.GetOrientation(), Pose1.GetOrientation(), u);
	FVector OutScale = FMath::Lerp(Pose0.GetScale(), Pose1.GetScale(), u);
	FVector OutTrans = FMath::Lerp(Pose0.GetTranslation(), Pose1.GetTranslation(), u);

	// Set calculated values for return'd pose
	OutPose->SetOrientation(OutOrientation);
	OutPose->SetScale(OutScale);
	OutPose->SetTranslation(OutTrans);

	// Done, return the Pose
	return OutPose;
}
