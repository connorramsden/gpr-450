// Copyright 2020 Connor Ramsden

#include "SpatialPose.h"

FSpatialPose::FSpatialPose()
{
	// This function achieves the same thing as a default constructor would
	ResetPose();

	return;
}

FSpatialPose::FSpatialPose(FVector NewRot, FVector NewScale, FVector NewTrans)
{
	Transform = FTransform::Identity;

	Orientation = NewRot;
	Scale = NewScale;
	Translation = NewTrans;

	return;
}

FSpatialPose::~FSpatialPose()
{
	return;
}

void FSpatialPose::SetRotation(float rx_degrees, float ry_degrees, float rz_degrees)
{
	Orientation = FVector(rx_degrees, ry_degrees, rz_degrees);

	return;
}

void FSpatialPose::SetScale(float sx, float sy, float sz)
{
	Scale = FVector(sx, sy, sz);

	return;
}

void FSpatialPose::SetTranslation(float tx, float ty, float tz)
{
	Translation = FVector(tx, ty, tz);

	return;
}

void FSpatialPose::ResetPose()
{
	// Set transform to identity matrix
	Transform = FTransform::Identity;
	// Set orientation to (0, 0, 0)
	Orientation = FVector::ZeroVector;
	// Set scale to (1, 1, 1)
	Scale = FVector::OneVector;
	// Set translation to (0, 0, 0)
	Translation = FVector::ZeroVector;

	return;
}

FMatrix PoseConvert(FSpatialPose PoseIn, SpatialPoseChannel Channel, SpatialPoseEulerOrder Order)
{
	// COME BACK TO THIS!

	return FMatrix();
}

FSpatialPose PoseConcat(FSpatialPose lhs, FSpatialPose rhs)
{
	// Calculate new values
	FVector ConcatRot = lhs.GetOrientation() + rhs.GetOrientation();
	FVector ConcatScale = FVector::CrossProduct(lhs.GetScale(), rhs.GetScale());
	FVector ConcatTranslation = lhs.GetTranslation() + rhs.GetTranslation();

	// Create pose to be returned
	FSpatialPose OutPose = FSpatialPose(ConcatRot, ConcatScale, ConcatTranslation);

	// Return the newly created spatial pose
	return OutPose;
}

FSpatialPose PoseLerp(FSpatialPose PoseZero, FSpatialPose PoseOne, float u)
{
	// Calculate lerp'd values
	FVector LerpRot = FMath::Lerp(PoseZero.GetOrientation(), PoseOne.GetOrientation(), u);
	FVector LerpScale = FMath::Lerp(PoseZero.GetScale(), PoseOne.GetScale(), u);
	FVector LerpTranslation = FMath::Lerp(PoseZero.GetTranslation(), PoseOne.GetTranslation(), u);

	// Create pose to be returned
	FSpatialPose OutPose = FSpatialPose(LerpRot, LerpScale, LerpTranslation);

	// Return the newly created spatial pose
	return OutPose;
}
