// Copyright 2020 Connor Ramsden
// Euler order and PoseChannel credit to Dan Buckstein https://github.com/dbucksteincc

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpatialPose.generated.h"

UENUM()
// List of euler angle product orders
enum SpatialPoseEulerOrder
{
	PoseEulerOrder_xyz,
	PoseEulerOrder_yzx,
	PoseEulerOrder_zxy,
	PoseEulerOrder_yxz,
	PoseEulerOrder_xzy,
	PoseEulerOrder_zyx
};

UENUM()
enum SpatialPoseChannel
{
	// Identity channel
	PoseChannel_none,

	// Orientation
	PoseChannel_orient_x = 0x0001,
	PoseChannel_orient_y = 0x0002,
	PoseChannel_orient_z = 0x0004,
	PoseChannel_orient_xy = PoseChannel_orient_x | PoseChannel_orient_y,
	PoseChannel_orient_yz = PoseChannel_orient_y | PoseChannel_orient_z,
	PoseChannel_orient_zx = PoseChannel_orient_z | PoseChannel_orient_x,
	PoseChannel_orient_xyz = PoseChannel_orient_xy | PoseChannel_orient_z,

	// Scale
	PoseChannel_scale_x = 0x0010,
	PoseChannel_scale_y = 0x0020,
	PoseChannel_scale_z = 0x0040,
	PoseChannel_scale_xy = PoseChannel_scale_x | PoseChannel_scale_y,
	PoseChannel_scale_yz = PoseChannel_scale_y | PoseChannel_scale_z,
	PoseChannel_scale_zx = PoseChannel_scale_z | PoseChannel_scale_x,
	PoseChannel_scale_xyz = PoseChannel_scale_xy | PoseChannel_scale_z,

	// Translation
	PoseChannel_translate_x = 0x0100,
	PoseChannel_translate_y = 0x0200,
	PoseChannel_translate_z = 0x0400,
	PoseChannel_translate_xy = PoseChannel_translate_x | PoseChannel_translate_y,
	PoseChannel_translate_yz = PoseChannel_translate_y | PoseChannel_translate_z,
	PoseChannel_translate_zx = PoseChannel_translate_z | PoseChannel_translate_x,
	PoseChannel_translate_xyz = PoseChannel_translate_xy | PoseChannel_translate_z,
};

UCLASS()
// Single pose for a single node
class ULAB_API USpatialPose : public UObject
{
	GENERATED_BODY()

protected:
	// 4x4 Matrix described by the pose, relative to parent space
	FTransform Transform;
	// Orientation: Three elements describing Euler angle orientation relative to parent space
	// Scale:		Three elements describing scale relative to parent space
	// Translation: Three elems describing the translation relative to parent space
	FVector Orientation, Scale, Translation;

	// CTor/DTor
public:
	// Default SPose Constructor
	USpatialPose();
	// Specialized SPose Constructor
	USpatialPose(FVector NewRot, FVector NewScale, FVector NewTranslation);
	// Default Spose Deconstructor
	~USpatialPose();

	// Getters & Setters
public:
	FORCEINLINE FTransform GetTransform() const { return Transform; }
	FORCEINLINE FVector GetOrientation() const { return Orientation; }
	FORCEINLINE FVector GetScale() const { return Scale; }	
	FORCEINLINE FVector GetTranslation() const { return Translation; }
	FORCEINLINE void SetTransform(FTransform NewTransform) { Transform = NewTransform; }

public:
	// Set rotation values for a single node pose
	void SetRotation(float rx_degrees, float ry_degrees, float rz_degrees);

	// Set scale values for a single node pose
	void SetScale(float sx, float sy, float sz);

	// Set translation values for a single node pose
	void SetTranslation(float tx, float ty, float tz);

	// Reset single node pose to default values
	void ResetPose();
};

// Convert single node pose to matrix
FMatrix PoseConvert(USpatialPose * PoseIn, SpatialPoseChannel Channel, SpatialPoseEulerOrder Order);

// Concat operation for single node pose
USpatialPose * PoseConcat(USpatialPose * lhs, USpatialPose * rhs);

// Lerp operation for single node pose (lerp by u value)
USpatialPose * PoseLerp(USpatialPose * PoseZero, USpatialPose * PoseOne, float u);
