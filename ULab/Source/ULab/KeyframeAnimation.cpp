// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimation.h"

KeyframeAnimation::KeyframeAnimation()
{
}

KeyframeAnimation::~KeyframeAnimation()
{
}

// Default Constructor
Keyframe::Keyframe()
{
}

// Initialize a keyframe
Keyframe::Keyframe(const float duration, const uint32 value_x)
{
	kDuration = duration;
	kDurationInv = 1 / duration;
	kData = value_x;
	return;
}

// Default Deconstructor
Keyframe::~Keyframe()
{
}

// Default KPool Constructor
KeyframePool::KeyframePool()
{
}

// Allocate Keyframe Pool
KeyframePool::KeyframePool(const uint32 count)
{
	kPool.SetNumUninitialized(count);
	kCount = count;
	return;
}

// Release keyframe pool
KeyframePool::~KeyframePool()
{
	for (uint32 i = 0; i < kCount; ++i) {
		kPool.RemoveAt(i);
	}
}
