// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyframeAnimation.generated.h"

/**
 *
 */

class ULAB_API KeyframeAnimation
{
public:
	KeyframeAnimation();
	~KeyframeAnimation();
};

USTRUCT()
struct ULAB_API FKeyframe
{
	GENERATED_BODY()
public:
	// Index in pool of keyframes
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
		uint32 keyframeIndex;
	// Interval of time for which this keyframe is active. Cannot be zero
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
		float keyframeDuration;
	// Reciprocal of kDuration
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
		float keyframeDurationInv;
	// Value of the sample described by a keyframe. Just an integer for example purposes
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
		uint32 keyframeData;

	// Default Contructor
	FKeyframe();
	// Initialize a keyframe
	FKeyframe(const float duration, const uint32 value_x);
	// Release a keyframe
	~FKeyframe();
};

USTRUCT()
struct ULAB_API FKeyframePool
{
	GENERATED_BODY()
public:
	// Array of all keyframes in the pool
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Pool Components")
		TArray<FKeyframe> keyframePool;

	// Number of keyframes in the pool
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Pool Components")
		uint32 keyframePoolCount;

	// Default KPool Constructor
	FKeyframePool();
	// Allocate Keyframe Pool
	FKeyframePool(const uint32 count);
	// Release keyframe pool
	~FKeyframePool();
};

USTRUCT()
struct ULAB_API FClip
{
	GENERATED_BODY()

public:
	// Identifies the clip
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		FString clipName;
	// Index in clip pool
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		uint32 clipIndex;
	// Duration of the clip; can be calculated as sum of all referenced keyframes or set first & distribute. Cannot be 0
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		float clipDuration;

	// Default Clip Constructor
	FClip();
	// Initialize Clip with First and Last indices
	FClip(FString newClipName, const FKeyframePool* keyframePool, const uint32 firstKeyframeIndex, const uint32 finalKeyframeIndex);
	// Release Clip
	~FClip();

	// Calculate clip duration as sum of keyframes' durations
	float CalculateDuration();
	float DistributeDuration(const float newClipDuration);
};

USTRUCT()
struct ULAB_API FClipPool
{
	GENERATED_BODY()

public:
	// Array of Clips
	UPROPERTY(VisibleAnywhere, Category = "Clip Pool Components")
		TArray<FClip> clipPool;

	// Number of Clips
	UPROPERTY(VisibleAnywhere, Category = "Clip Pool Components")
		uint32 clipCount;

	// Default ClipPool Constructor
	FClipPool();
	// Allocate Clip Pool
	FClipPool(const uint32 count);
	// Release Clip Pool
	~FClipPool();

	// Get Clip Index from Pool
	uint32 GetClipIndexInPool(FString clipName);
};