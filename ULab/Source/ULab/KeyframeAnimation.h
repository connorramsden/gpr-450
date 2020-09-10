// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */

class ULAB_API KeyframeAnimation
{
public:
	KeyframeAnimation();
	~KeyframeAnimation();
};

class ULAB_API Keyframe
{
public:
	// Index in pool of keyframes
	uint32 kfIndex;
	// Interval of time for which this keyframe is active. Cannot be zero
	float kfDuration;
	// Reciprocal of kDuration
	float kfDurationInv;
	// Value of the sample described by a keyframe. Just an integer for example purposes
	uint32 kfData;

	// Default Contructor
	Keyframe();
	// Initialize a keyframe
	Keyframe(const float duration, const uint32 value_x);
	// Release a keyframe
	~Keyframe();
};

class ULAB_API KeyframePool
{
public:
	// Array of all keyframes in the pool
	TArray<Keyframe*> kpPool;

	// Number of keyframes in the pool
	uint32 kpCount;
	
	// Default KPool Constructor
	KeyframePool();
	// Allocate Keyframe Pool
	KeyframePool(const uint32 count);
	// Release keyframe pool
	~KeyframePool();
};

class ULAB_API Clip
{
public:
	// Identifies the clip
	FString kName;
	// Index in clip pool
	uint32 kClipIndex;
	// Duration of the clip; can be calculated as sum of all referenced keyframes or set first & distribute. Cannot be 0
	float kClipDuration;

	// Default Clip Constructor
	Clip();
	// Initialize Clip with First and Last indices
	Clip(const FString clipName, const KeyframePool* keyframePool, const uint32 firstKeyframeIndex, const uint32 finalKeyframeIndex);
	// Release Clip
	~Clip();

	// Calculate clip duration as sum of keyframes' durations
	float CalculateDuration();
	float DistributeDuration(const float newClipDuration);
};

class ULAB_API ClipPool
{
public:
	// Array of Clips
	TArray<Clip*> kClipPool;
	// Number of Clips
	uint32 kClipCount;

	// Default ClipPool Constructor
	ClipPool();
	// Allocate Clip Pool
	ClipPool(const uint32 count);
	// Release Clip Pool
	~ClipPool();

	// Get Clip Index from Pool
	uint32 GetClipIndexInPool(FString clipName);
};