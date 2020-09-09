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
	int kIndex;
	// Interval of time for which this keyframe is active. Cannot be zero
	float kDuration;
	// Reciprocal of kDuration
	float kDurationInv;
	// Value of the sample described by a keyframe. Just an integer for example purposes
	int kData;

	Keyframe();
	~Keyframe();
};

class ULAB_API KeyframePool
{
public:
	// Array of all keyframes in the pool
	Keyframe* kpKeyframe;

	// Number of keyframes in the pool
	int kpCount;
};