// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpatialPose.generated.h"

/**
 * List of Euler angle product orders
 */
UENUM()
enum class SpatialPoseEulerOrder
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
enum class SpatialPoseChannel
{
	// identity (no channels)
	PoseChannel_none,

	// orientation
	PoseChannel_orient_x = 0x0001,
	PoseChannel_orient_y = 0x0002,
	PoseChannel_orient_z = 0x0004,
	PoseChannel_orient_xy = PoseChannel_orient_x | PoseChannel_orient_y,
	PoseChannel_orient_yz = PoseChannel_orient_y | PoseChannel_orient_z,
	PoseChannel_orient_zx = PoseChannel_orient_z | PoseChannel_orient_x,
	PoseChannel_orient_xyz = PoseChannel_orient_xy | PoseChannel_orient_z,

	// scale
	PoseChannel_scale_x = 0x0010,
	PoseChannel_scale_y = 0x0020,
	PoseChannel_scale_z = 0x0040,
	PoseChannel_scale_xy = PoseChannel_scale_x | PoseChannel_scale_y,
	PoseChannel_scale_yz = PoseChannel_scale_y | PoseChannel_scale_z,
	PoseChannel_scale_zx = PoseChannel_scale_z | PoseChannel_scale_x,
	PoseChannel_scale_xyz = PoseChannel_scale_xy | PoseChannel_scale_z,

	// translation
	PoseChannel_translate_x = 0x0100,
	PoseChannel_translate_y = 0x0200,
	PoseChannel_translate_z = 0x0400,
	PoseChannel_translate_xy = PoseChannel_translate_x | PoseChannel_translate_y,
	PoseChannel_translate_yz = PoseChannel_translate_y | PoseChannel_translate_z,
	PoseChannel_translate_zx = PoseChannel_translate_z | PoseChannel_translate_x,
	PoseChannel_translate_xyz = PoseChannel_translate_xy | PoseChannel_translate_z,
};

/**
 * A description of a transformation (pose) in space
 * Provides spatial / temporal context for a UHNode
 * Spatial description of a UHNode at a given time
 */
UCLASS()
class ULAB_API USpatialPose : public UObject
{
	GENERATED_BODY()

protected: // Member Variables
	// 4x4 matrix described by a pose, relative to parent space
	FTransform Transform;
	// 3 Element Vectors
	// O -> Elements describing Euler angle orientation, relative to parent space
	// S -> Elements describing scale, relative to parent space
	// T -> Elements describing the translation, relative to parent space
	FVector Orientation, Scale, Translation;

public: // CTor
	USpatialPose();

public: // Getters & Setters
	FORCEINLINE FTransform GetTransform() { return Transform; }
	FORCEINLINE FVector GetOrientation() { return Orientation; }
	FORCEINLINE FVector GetScale() { return Scale; }
	FORCEINLINE FVector GetTranslation() { return Translation; }
	FORCEINLINE void SetTransform(FTransform NewT) { Transform = NewT; }
	FORCEINLINE void SetOrientation(FVector NewO) { Orientation = NewO; }
	FORCEINLINE void SetScale(FVector NewS) { Scale = NewS; }
	FORCEINLINE void SetTranslation(FVector NewT) { Translation = NewT; }

public:
	void Init(FTransform TMat, FVector O, FVector S, FVector TVec);
	void ResetPose();
};

typedef SpatialPoseChannel PoseChannel;
typedef SpatialPoseEulerOrder PoseOrder;

USpatialPose * PoseCopy(USpatialPose & OtherPose);
FMatrix PoseConvert(USpatialPose & PoseIn, PoseChannel Channel, PoseOrder Order);
USpatialPose * PoseConcat(USpatialPose & lhs, USpatialPose & rhs);
USpatialPose * PoseLerp(USpatialPose & Pose0, USpatialPose & Pose1, float u);
