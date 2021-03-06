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

// Determines which interpolation mode a Pose will utilize
UENUM()
enum class EInterpMode
{
	Mode_Err = -1,
	Mode_Step,
	Mode_Nearest,
	Mode_Linear,
	Mode_Smooth
};

typedef ESpatialPoseChannel EPoseChannel;
typedef ESpatialPoseEulerOrder EPoseOrder;

USTRUCT(BlueprintType)
struct ULAB_API FSpatialPose
{
	GENERATED_BODY()

protected:
	/// PROPERTIES ///
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FTransform Transform;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FVector4 Orientation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FVector Translation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FVector Rotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FVector Scale;

public:
	/// CONSTRUCTOR ///
	FSpatialPose();

	/// ACCESSORS ///
	// Get & Set Transform
	FORCEINLINE FTransform GetTransform() { return Transform; }
	FORCEINLINE void SetTransform(FTransform NewT) { Transform = NewT; }
	// Get & Set Orientation
	FORCEINLINE FVector4 GetOrientation() { return Orientation; }
	FORCEINLINE void SetOrientation(FVector4 NewO) { Orientation = NewO; }
	// Get & Set Translation
	FORCEINLINE FVector GetTranslation() { return Translation; }
	FORCEINLINE void SetTranslation(FVector NewT) { Translation = NewT; }
	// Get & Set Rotation
	FORCEINLINE FVector GetRotation() { return Rotation; }
	FORCEINLINE void SetRotation(FVector NewR) { Rotation = NewR; }
	// Get & Set Scale
	FORCEINLINE FVector GetScale() { return Scale; }
	FORCEINLINE void SetScale(FVector NewS) { Scale = NewS; }

	/// METHODS ///
	// Init a new Spatial Pose
	void Init(FTransform TMat, FVector TVec, FVector R, FVector S);
	// Reset a given Spatial Pose
	void ResetPose();
	// Convert a Spatial Pose
	void PoseConvert(EPoseChannel Channel = ESpatialPoseChannel::PoseChannel_None, EPoseOrder Order = ESpatialPoseEulerOrder::PoseEulerOrder_xyz);
	// Restore a Spatial Pose
	void PoseRestore(EPoseChannel Channe = ESpatialPoseChannel::PoseChannel_None, EPoseOrder Order = ESpatialPoseEulerOrder::PoseEulerOrder_xyz);
	// Copy the passed Pose to this Pose
	void PoseCopy(const FSpatialPose Other);
	// Concat the passed Pose with this Pose
	void PoseConcat(const FSpatialPose Other);
	// Lerp the passed Pose with this Pose via U (defaults to LERP)
	void PoseLerp(const FSpatialPose Other, const float U, const EInterpMode Mode = EInterpMode::Mode_Linear);
};
