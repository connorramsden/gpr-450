// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "Math/DualQuat.h"
#include "UObject/NoExportTypes.h"
#include "CJR_SpatialPose.generated.h"

/**
 * List of Euler angle product orders
 */
UENUM()
enum class ESpatialPoseEulerOrder
{
	PoseEulerOrder_xyz,
	PoseEulerOrder_yzx,
	PoseEulerOrder_zxy,
	PoseEulerOrder_yxz,
	PoseEulerOrder_xzy,
	PoseEulerOrder_zyx,
};

/**
 * Flags to describe transformation components in use
 * Useful for constraining motion and kinematics
 */
UENUM()
enum class ESpatialPoseChannel
{
	// identity (no channels)
	PoseChannel_None,

	// orientation
	PoseChannel_Orient_X = 0x0001,
	PoseChannel_Orient_Y = 0x0002,
	PoseChannel_Orient_Z = 0x0004,
	PoseChannel_Orient_XY = PoseChannel_Orient_X | PoseChannel_Orient_Y,
	PoseChannel_Orient_YZ = PoseChannel_Orient_Y | PoseChannel_Orient_Z,
	PoseChannel_Orient_ZX = PoseChannel_Orient_Z | PoseChannel_Orient_X,
	PoseChannel_Orient_XYZ = PoseChannel_Orient_XY | PoseChannel_Orient_Z,

	// scale
	PoseChannel_Scale_X = 0x0010,
	PoseChannel_Scale_Y = 0x0020,
	PoseChannel_Scale_Z = 0x0040,
	PoseChannel_Scale_XY = PoseChannel_Scale_X | PoseChannel_Scale_Y,
	PoseChannel_Scale_YZ = PoseChannel_Scale_Y | PoseChannel_Scale_Z,
	PoseChannel_Scale_ZX = PoseChannel_Scale_Z | PoseChannel_Scale_X,
	PoseChannel_Scale_XYZ = PoseChannel_Scale_XY | PoseChannel_Scale_Z,

	// translation
	PoseChannel_Translate_X = 0x0100,
	PoseChannel_Translate_Y = 0x0200,
	PoseChannel_Translate_Z = 0x0400,
	PoseChannel_Translate_XY = PoseChannel_Translate_X | PoseChannel_Translate_Y,
	PoseChannel_Translate_YZ = PoseChannel_Translate_Y | PoseChannel_Translate_Z,
	PoseChannel_Translate_ZX = PoseChannel_Translate_Z | PoseChannel_Translate_X,
	PoseChannel_Translate_XYZ = PoseChannel_Translate_XY | PoseChannel_Translate_Z,
};

/**
 * A description of a transformation (pose) in space
 * Provides spatial / temporal context for a UHNode
 * Spatial description of a UHNode at a given time
 */
UCLASS()
class ULAB_API USpatialPose final : public UObject
{
	GENERATED_BODY()

protected: // Member Variables
	// 4x4 matrix described by a pose, relative to parent space
	// Derived from TRS, and matrices don't blend well
	FTransform Transform;

	// Final DQ - can be derived from all below or TR - they do animate
	// dq = dual number, with real and dual part, each a quaternion
	// default dq = "1": real = (0, 0, 0, 1), dual = (0, 0, 0, 0)
	// encodes angle/axis rotation, uniform scale (squared magnitude))
	// FDualQuat Dq; 

	// quaternion - derived from Euler angles or angle/axis
	// default quat = "1": (0, 0, 0, 1)
	FVector4 Orientation;
	
	// 3 Element Vectors
	// R -> Elements describing Euler angle orientation, relative to parent space
	// S -> Elements describing scale, relative to parent space
	// T -> Elements describing the translation, relative to parent space
	FVector Rotation, Scale, Translation;

public: // CTor
	USpatialPose();

public: // Getters & Setters
	FORCEINLINE FTransform GetTransform() const { return Transform; }
	FORCEINLINE FVector4 GetOrientation() const { return Orientation; }
	FORCEINLINE FVector GetRotation() const { return Rotation; }
	FORCEINLINE FVector GetScale() const { return Scale; }
	FORCEINLINE FVector GetTranslation() const { return Translation; }
	FORCEINLINE void SetTransform(const FTransform NewT) { Transform = NewT; }
	FORCEINLINE void SetOrientation(const FVector4 NewO) { Orientation = NewO; }
	FORCEINLINE void SetRotation(const FVector NewR) { Rotation = NewR; }
	FORCEINLINE void SetScale(const FVector NewS) { Scale = NewS; }
	FORCEINLINE void SetTranslation(const FVector NewT) { Translation = NewT; }

public:
	void Init(FTransform TMat, FVector O, FVector S, FVector TVec);
	void ResetPose();
};

typedef ESpatialPoseChannel EPoseChannel;
typedef ESpatialPoseEulerOrder EPoseOrder;

USpatialPose * PoseCopy(USpatialPose & OtherPose);
void PoseConvert(USpatialPose & PoseIn, EPoseChannel Channel, EPoseOrder Order);
USpatialPose * PoseConcat(USpatialPose & Lhs, USpatialPose & RHS);
USpatialPose * PoseLerp(USpatialPose & Pose0, USpatialPose & Pose1, float U);
