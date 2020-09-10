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
FKeyframe::FKeyframe(const float duration, const int value_x)
{
	// Set duration
	keyframeDuration = duration;
	// Set duration inverse
	keyframeDurationInv = 1.0f / duration;
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
FKeyframePool::FKeyframePool(const int count)
{
	// Allocate array of keyframes (not sure if this function works. Might have to initialize manually)
	keyframePool.SetNumUninitialized(count);
	// Set keyframe count
	keyframePoolCount = count;

	return;
}

// Release keyframe pool
FKeyframePool::~FKeyframePool()
{
}

///////////// KEYFRAME POOL END /////////////

///////////// CLIP START /////////////

FClip::FClip()
{
}

FClip::FClip(FString newClipName, const FKeyframePool newPool, const int firstKeyframeIndex, const int finalKeyframeIndex)
{
	// Set name
	clipName = newClipName;
	// Set referenced keyframe pool
	keyframePool = newPool;
	// Set first KF index
	firstKeyframe = firstKeyframeIndex;
	// Set last KF index
	lastKeyframe = finalKeyframeIndex;

	return;
}

FClip::~FClip()
{
}

void FClip::CalculateDuration()
{
	// Sum the duration of all keyframes to calculate clip duration
	for (int i = 0; i < keyframePool.keyframePoolCount; ++i) {
		clipDuration += keyframePool.keyframePool[i].keyframeDuration;
	}

	// Calculate clip duration inverse
	clipDurationInv = 1.0f / clipDuration;

	return;
}

void FClip::DistributeDuration(const float newClipDuration)
{
	// Set duration directly
	clipDuration = newClipDuration;
	// Set inverse directly
	clipDurationInv = 1.0f / newClipDuration;

	// Distribute uniform duration across all keyframes
	for (int i = 0; i < keyframePool.keyframePoolCount; ++i) {
		keyframePool.keyframePool[i].keyframeDuration = clipDuration;
		keyframePool.keyframePool[i].keyframeDurationInv = clipDurationInv;
	}

	return;
}

///////////// CLIP END /////////////


///////////// CLIP POOL START /////////////

FClipPool::FClipPool()
{
}

FClipPool::FClipPool(const int count)
{
	// IDK how this function works! Hopefully it just does!
	clipPool.SetNumUninitialized(count);

	// Set clip count
	clipCount = count;

	return;
}

FClipPool::~FClipPool()
{
}

int FClipPool::GetClipIndexInPool(FString clipName)
{
	int tempIndex = -1;

	for (int i = 0; i < clipCount; ++i)
	{
		if (clipPool[i].clipName == clipName)
		{
			tempIndex = clipPool[i].clipIndex;
		}
	}

	return tempIndex;
}

///////////// CLIP POOL END /////////////
