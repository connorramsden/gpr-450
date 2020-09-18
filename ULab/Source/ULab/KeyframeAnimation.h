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

USTRUCT(BlueprintType)
struct ULAB_API FKeyframe
{
	GENERATED_BODY()
	public:
	// Index in pool of keyframes
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
		int index;
	// Interval of time for which this keyframe is active. Cannot be zero
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Keyframe Components")
		float duration;
	// Reciprocal of kDuration
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
		float durationInv;
	// Value of the sample described by a keyframe. Just an integer for example purposes
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
		int data;

	// Default Contructor
	FKeyframe();
	// Initialize a keyframe
	FKeyframe(const float newDuration, const int value_x);
	// Release a keyframe
	~FKeyframe();
};

USTRUCT(BlueprintType)
struct ULAB_API FKeyframePool
{
	GENERATED_BODY()
	public:
	// Array of all keyframes in the pool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Keyframe Pool Components")
		TArray<FKeyframe> pool;

	// Number of keyframes in the pool
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Pool Components")
		int poolCount = -1;

	// Default KPool Constructor
	FKeyframePool();
	// Allocate Keyframe Pool
	FKeyframePool(const int count);
	// Release keyframe pool
	~FKeyframePool();
};

USTRUCT(BlueprintType)
struct ULAB_API FClip
{
	GENERATED_BODY()

	public:
	// Identifies the clip
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Components", meta = (AllowPrivateAccess = "true"))
		FString name;
	// Index in clip pool
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		int index;
	// Duration of the clip; can be calculated as sum of all referenced keyframes or set first & distribute. Cannot be 0
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		float duration;
	// Inverse of clipDuration
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		float durationInv;
	// Number of keyframes referenced by clip
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		int count;
	// index of first keyframe in pool ref'd by clip
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		int firstKeyframe;
	// index of final keyframe in pool ref'd by clip
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
		int lastKeyframe;
	// The pool of keyframes containing those included in this set.
	FKeyframePool keyframePool;

	// Default Clip Constructor
	FClip();
	// Initialize Clip with First and Last indices
	FClip(FString newClipName, const FKeyframePool keyframePool, const int firstKeyframeIndex, const int finalKeyframeIndex);
	// Release Clip
	~FClip();

	// Calculate clip duration as sum of keyframes' durations
	void CalculateDuration();
	// Uniformly set duration and inverse across entire pool
	void DistributeDuration(const float newClipDuration);
};

USTRUCT(BlueprintType)
struct ULAB_API FClipPool
{
	GENERATED_BODY()

	public:
	// Array of Clips
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Pool Components")
		TArray<FClip> pool;

	// Number of Clips in the Pool
	UPROPERTY(EditAnywhere, Category = "Clip Pool Components")
		int count = -1;

	// Default ClipPool Constructor
	FClipPool();
	// Allocate Clip Pool
	FClipPool(const int newCount);
	// Release Clip Pool
	~FClipPool();

	// Get Clip Index from Pool
	int GetClipIndexInPool(FString clipName);
};