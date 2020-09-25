// Copyright 2020 Connor Ramsden

#include "SpatialPose.h"

USpatialPose::USpatialPose()
{
	// This function achieves the same thing as a default constructor would
	ResetPose();

	return;
}

USpatialPose::USpatialPose(FVector NewRot, FVector NewScale, FVector NewTranslation)
{
	Transform = FMatrix::Identity;
	Orientation = NewRot;
	Scale = NewScale;
	Translation = NewTranslation;

	return;
}

USpatialPose::~USpatialPose()
{
	return;
}

void USpatialPose::SetRotation(float rx_degrees, float ry_degrees, float rz_degrees)
{
	Orientation = FVector(rx_degrees, ry_degrees, rz_degrees);

	return;
}

void USpatialPose::SetScale(float sx, float sy, float sz)
{
	Scale = FVector(sx, sy, sz);

	return;
}

void USpatialPose::SetTranslation(float tx, float ty, float tz)
{
	Translation = FVector(tx, ty, tz);

	return;
}

void USpatialPose::ResetPose()
{
	// Set transform to identity matrix
	Transform = FMatrix::Identity;
	// Set orientation to (0, 0, 0)
	Orientation = FVector::ZeroVector;
	// Set scale to (1, 1, 1)
	Scale = FVector::OneVector;
	// Set translation to (0, 0, 0)
	Translation = FVector::ZeroVector;

	return;
}

FMatrix PoseConvert(USpatialPose * PoseIn, SpatialPoseChannel Channel, SpatialPoseEulerOrder Order)
{
	// COME BACK TO THIS!

	return FMatrix();
}

USpatialPose * PoseConcat(USpatialPose * lhs, USpatialPose * rhs)
{
	// Calculate new values
	FVector ConcatRot = lhs->GetOrientation() + rhs->GetOrientation();
	FVector ConcatScale = FVector::CrossProduct(lhs->GetScale(), rhs->GetScale());
	FVector ConcatTranslation = lhs->GetTranslation() + rhs->GetTranslation();

	USpatialPose * OutPose = NewObject<USpatialPose>();
	OutPose->SetRotation(ConcatRot.X, ConcatRot.Y, ConcatRot.Z);
	OutPose->SetScale(ConcatScale.X, ConcatScale.Y, ConcatScale.Z);
	OutPose->SetTranslation(ConcatTranslation.X, ConcatTranslation.Y, ConcatTranslation.Z);

	// Return the newly created spatial pose
	return OutPose;
}

USpatialPose * PoseLerp(USpatialPose* PoseZero, USpatialPose *PoseOne, float u)
{
	// Calculate lerp'd values
	FVector LerpRot = FMath::Lerp(PoseZero->GetOrientation(), PoseOne->GetOrientation(), u);
	FVector LerpScale = FMath::Lerp(PoseZero->GetScale(), PoseOne->GetScale(), u);
	FVector LerpTranslation = FMath::Lerp(PoseZero->GetTranslation(), PoseOne->GetTranslation(), u);

	USpatialPose * OutPose = NewObject<USpatialPose>();
	OutPose->SetRotation(LerpRot.X, LerpRot.Y, LerpRot.Z);
	OutPose->SetScale(LerpScale.X, LerpScale.Y, LerpScale.Z);
	OutPose->SetTranslation(LerpTranslation.X, LerpTranslation.Y, LerpTranslation.Z);

	// Return the newly created spatial pose
	return OutPose;
}
