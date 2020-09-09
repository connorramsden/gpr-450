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
	uint32 kIndex;
	// Interval of time for which this keyframe is active. Cannot be zero
	float kDuration;
	// Reciprocal of kDuration
	float kDurationInv;
	// Value of the sample described by a keyframe. Just an integer for example purposes
	uint32 kData;

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
	TArray<Keyframe*> kPool;

	// Number of keyframes in the pool
	uint32 kCount;
	
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
	FString kName;
};