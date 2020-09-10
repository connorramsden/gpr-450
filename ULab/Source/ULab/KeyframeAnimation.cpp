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
Keyframe::Keyframe()
{
}

// Initialize a keyframe
Keyframe::Keyframe(const float duration, const uint32 value_x)
{
	// Set duration
	kfDuration = duration;
	// Set duration inverse
	kfDurationInv = 1 / duration;
	// Set value
	kfData = value_x;

	return;
}

// Default Deconstructor
Keyframe::~Keyframe()
{
}

///////////// KEYFRAME END /////////////

///////////// KEYFRAME POOL  START /////////////

// Default KPool Constructor
KeyframePool::KeyframePool()
{
}

// Allocate Keyframe Pool
KeyframePool::KeyframePool(const uint32 count)
{
	// Allocate array of keyframes
	kpPool.SetNumUninitialized(count);
	// Set keyframe count
	kpCount = count;

	return;
}

// Release keyframe pool
KeyframePool::~KeyframePool()
{
	for (uint32 i = 0; i < kpCount; ++i) {
		// NOTE: Might break, depending on how RemoveAt works. Does it resize array?
		kpPool.RemoveAt(i);
	}

	return;
}

///////////// KEYFRAME POOL END /////////////

///////////// CLIP START /////////////

Clip::Clip()
{
}

Clip::Clip(const FString clipName, const KeyframePool* keyframePool, const uint32 firstKeyframeIndex, const uint32 finalKeyframeIndex)
{
	kName = clipName;

}

Clip::~Clip()
{
}

float Clip::CalculateDuration()
{
	return 0.0f;
}

float Clip::DistributeDuration(const float newClipDuration)
{
	return 0.0f;
}

///////////// CLIP END /////////////


///////////// CLIP POOL START /////////////

ClipPool::ClipPool()
{
}

ClipPool::ClipPool(const uint32 count)
{
}

ClipPool::~ClipPool()
{
}

uint32 ClipPool::GetClipIndexInPool(FString clipName)
{
	return uint32();
}

///////////// CLIP POOL END /////////////
