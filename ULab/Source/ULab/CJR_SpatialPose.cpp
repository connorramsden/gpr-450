// Copyright 2020 Connor Ramsden


#include "CJR_SpatialPose.h"
#include "CJR_HelperFunctions.h"
typedef FCJR_HelperFunctions FHF;

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

void USpatialPose::PoseConvert(EPoseChannel Channel, EPoseOrder Order)
{
	// Check fucking slides lol
	FMatrix rx, ry, rz, r;

	switch (Order)
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

	FHF::NotImplemented();
	
	return;
}

void USpatialPose::PoseRestore(ESpatialPoseChannel Channel, ESpatialPoseEulerOrder Order)
{
	FHF::NotImplemented();

	return;
}

void USpatialPose::PoseCopy(USpatialPose& Other)
{
	SetTransform(Other.GetTransform());
	SetOrientation(Other.GetOrientation());
	SetRotation(Other.GetRotation());
	SetScale(Other.GetScale());
	SetTranslation(Other.GetTranslation());

	return;
}

void USpatialPose::PoseConcat(USpatialPose* Other)
{
	// Concat Rotation
	SetRotation(GetRotation() + Other->GetRotation());
	// Concat Scale
	SetScale(GetScale() * Other->GetScale());
	// Concat Translation
	SetTranslation(GetTranslation() + Other->GetTranslation());

	return;
}

void USpatialPose::PoseLerp(USpatialPose* Other, const float U, EInterpMode Mode)
{
	switch (Mode)
	{
	case EInterpMode::Mode_Err:
		FHF::LogStringErr("Error: Mode Passed Incorrectly.");
		break;
	case EInterpMode::Mode_Step:
		{
			break;
		}
	case EInterpMode::Mode_Nearest:
		{
			break;
		}
	case EInterpMode::Mode_Linear:
		{
			// Lerp Rotation
			SetRotation(FMath::Lerp(GetRotation(), Other->GetRotation(), U));
			// Lerp Scale
			SetScale(FMath::Lerp(GetScale(), Other->GetScale(), U));
			// Lerp Translation
			SetTranslation(FMath::Lerp(GetTranslation(), Other->GetTranslation(), U));
			break;
		}
	case EInterpMode::Mode_Smooth:
		{
			break;
		}
	default:
		FHF::LogStringErr("Error: Mode Passed Incorrectly.");
		break;
	}

	return;
}
