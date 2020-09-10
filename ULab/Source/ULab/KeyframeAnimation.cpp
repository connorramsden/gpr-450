// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimation.h"

KeyframeAnimation::KeyframeAnimation()
{
}

KeyframeAnimation::~KeyframeAnimation()
{
}

///////////// KEYFRAME START /////////////

// Default Constructor
FKeyframe::FKeyframe()
{
}

// Initialize a keyframe
FKeyframe::FKeyframe(const float duration, const uint32 value_x)
{
	// Set duration
	keyframeDuration = duration;
	// Set duration inverse
	keyframeDurationInv = 1 / duration;
	// Set value
	keyframeData = value_x;

	return;
}

// Default Deconstructor
FKeyframe::~FKeyframe()
{
}

///////////// KEYFRAME END /////////////

///////////// KEYFRAME POOL  START /////////////

// Default KPool Constructor
FKeyframePool::FKeyframePool()
{
}

// Allocate Keyframe Pool
FKeyframePool::FKeyframePool(const uint32 count)
{
	// Allocate array of keyframes
	keyframePool.SetNumUninitialized(count);
	// Set keyframe count
	keyframePoolCount = count;

	return;
}

// Release keyframe pool
FKeyframePool::~FKeyframePool()
{
	for (uint32 i = 0; i < keyframePoolCount; ++i) {
		// NOTE: Might break, depending on how RemoveAt works. Does it resize array?
		keyframePool.RemoveAt(i);
	}

	return;
}

///////////// KEYFRAME POOL END /////////////

///////////// CLIP START /////////////

FClip::FClip()
{
}

FClip::FClip(FString newClipName, const FKeyframePool* keyframePool, const uint32 firstKeyframeIndex, const uint32 finalKeyframeIndex)
{
	clipName = newClipName;
}

FClip::~FClip()
{
}

float FClip::CalculateDuration()
{
	return 0.0f;
}

float FClip::DistributeDuration(const float newClipDuration)
{
	return 0.0f;
}

///////////// CLIP END /////////////


///////////// CLIP POOL START /////////////

FClipPool::FClipPool()
{
}

FClipPool::FClipPool(const uint32 count)
{
}

FClipPool::~FClipPool()
{
}

uint32 FClipPool::GetClipIndexInPool(FString clipName)
{
	return uint32();
}

///////////// CLIP POOL END /////////////
