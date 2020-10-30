// Copyright 2020 Connor Ramsden

#include "CJR_SpatialPose.h"
#include "CJR_HelperFunctions.h"
typedef FCJR_HelperFunctions FHF;

FSpatialPose::FSpatialPose()
{
	// Performs the same ops we'd want in a default pose anyways.
	ResetPose();
}

void FSpatialPose::Init(FTransform TMat, FVector TVec, FVector R, FVector S)
{
	Transform = TMat;

	Translation = TVec;
	Rotation = R;
	Scale = S;
}

void FSpatialPose::ResetPose()
{
	// Transform is Identity
	Transform = FTransform::Identity;

	// Orientation is V4 Identity
	Orientation = FVector4(0.0f, 0.0f, 0.0f, 1.0f);

	// (0, 0, 0)
	Translation = FVector::ZeroVector;
	// (0, 0, 0)
	Rotation = FVector::ZeroVector;
	// (1, 1, 1)
	Scale = FVector::OneVector;
}

void FSpatialPose::PoseConvert(EPoseChannel Channel, EPoseOrder Order)
{
	FHF::NotImplemented();
}

void FSpatialPose::PoseRestore(EPoseChannel Channel, EPoseOrder Order)
{
	FHF::NotImplemented();
}

void FSpatialPose::PoseCopy(const FSpatialPose Other)
{
	Transform = Other.Transform;
	Orientation = Other.Orientation;

	Translation = Other.Translation;
	Rotation = Other.Rotation;
	Scale = Other.Scale;
}

void FSpatialPose::PoseConcat(const FSpatialPose Other)
{
	Translation += Other.Translation;
	Rotation += Other.Rotation;
	Scale *= Other.Scale;
}

void FSpatialPose::PoseLerp(const FSpatialPose Other, const float U, const EInterpMode Mode)
{
	switch (Mode)
	{
	case EInterpMode::Mode_Err:
		FHF::LogStringErr("PoseLerp() Mode passed incorrectly.");
		break;
	case EInterpMode::Mode_Step:
		break;
	case EInterpMode::Mode_Nearest:
		break;
	case EInterpMode::Mode_Linear:
		Translation = FMath::Lerp(Translation, Other.Translation, U);
		Rotation = FMath::Lerp(Rotation, Other.Rotation, U);
		Scale = FMath::Lerp(Scale, Other.Scale, U);
		break;
	case EInterpMode::Mode_Smooth:
		break;
	}
}
