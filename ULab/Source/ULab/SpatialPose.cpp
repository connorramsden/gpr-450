// Copyright 2020 Connor Ramsden


#include "SpatialPose.h"

USpatialPose::USpatialPose()
{
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
