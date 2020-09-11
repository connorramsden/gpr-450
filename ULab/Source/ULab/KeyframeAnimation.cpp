// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimation.h"
#include <Math/UnrealMath.h>

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
	// Arbitrary duration between 1 and 10 ticks
	keyframeDuration = FMath::RandRange(1.0f, 10.0f);
	// Calculate duration inverse
	keyframeDurationInv = 1.0f / keyframeDuration;
	// Randomly select 'Data' (Will be more concrete in future update)
	keyframeData = FMath::Rand();
}

// Initialize a keyframe
FKeyframe::FKeyframe(const float duration, const int value_x)
{
	// Set duration
	keyframeDuration = duration;
	// Calculate duration inverse
	keyframeDurationInv = 1.0f / duration;
	// Set Data value (Will not be integer in future update)
	keyframeData = value_x;

	return;
}

// Default Deconstructor
FKeyframe::~FKeyframe()
{
	// Do I need anything here? No pointers.
}

///////////// KEYFRAME END /////////////

///////////// KEYFRAME POOL  START /////////////

// Default KPool Constructor
FKeyframePool::FKeyframePool()
{
	// Default initialization to 20
	for (int i = 0; i < 20; ++i)
	{
		// Increment keyframe pool count
		keyframePoolCount++;

		// Assign a temporary keyframe a duration between 1 and 10, and a random piece of 'data'
		FKeyframe tempFrame = FKeyframe(FMath::RandRange(1.0f, 10.0f), FMath::Rand());
		// Set the temporary keyframe's index to the current keyframe count
		tempFrame.keyframeIndex = keyframePoolCount;

		// Add the temporary keyframe to the pool
		keyframePool.Add(tempFrame);

		// Do I need to clean up temp frame? It is not a pointer...
	}

	return;
}

// Allocate Keyframe Pool
FKeyframePool::FKeyframePool(const int count)
{	
	// Allocate array of keyframes (not sure if this function works. Might have to initialize manually)
	for (int i = 0; i < count; ++i)
	{
		// Increment keyframe pool count
		keyframePoolCount++;

		// Assign a temporary keyframe a duration between 1 and 10, and a random piece of 'data'
		FKeyframe tempFrame = FKeyframe(FMath::RandRange(1.0f, 10.0f), FMath::Rand());
		// Set the temporary keyframe's index to the current keyframe count
		tempFrame.keyframeIndex = keyframePoolCount;

		// Add the temporary keyframe to the pool
		keyframePool.Add(tempFrame);

		// Do I need to clean up temp frame? It is not a pointer...
	}

	return;
}

// Release keyframe pool
FKeyframePool::~FKeyframePool()
{
	// Do I have anything to deconstruct? Might need to free pool memory?
}

///////////// KEYFRAME POOL END /////////////

///////////// CLIP START /////////////

// Default Clip Constructor
FClip::FClip()
{
	// Set default clip name
	clipName = "New Clip";

	// Initialize default keyframe pool (NOTE: Might not work the way I want it to!)
	keyframePool = FKeyframePool();

	// NOTE: Might need to fix these default values, we'll see
	// Set first keyframe index to 0
	firstKeyframe = 0;
	// Last index should be 19 (since we have 20 keyframes in a default init)
	lastKeyframe = 19;

	return;
}

// Specialized Clip Constructor
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
	// Do I need to deallocate anything from the Clip?
}

// Calculate clip duration as sum of keyframes' durations
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

// Uniformly set duration and inverse across entire pool
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

// Default Clip Pool Constructor
FClipPool::FClipPool()
{
}

// Specialized Clip Pool Constructor
FClipPool::FClipPool(const int count)
{
	for (int i = 0; i < count; ++i)
	{
		// Increment clip count
		clipCount++;

		// Create a default / blank Clip
		FClip tempClip = FClip();
		// Set the clip index to the current count
		tempClip.clipIndex = clipCount;

		// Add the temp clip to the pool
		clipPool.Add(tempClip);
	}

	return;
}

// Clip Pool Deconstructor
FClipPool::~FClipPool()
{
	// Do I need to deallocate anything from the pool?
}

int FClipPool::GetClipIndexInPool(FString clipName)
{
	int tempIndex = -1;

	for (int i = 0; i < clipCount; ++i)
	{
		// If the names match, set temp index
		if (clipPool[i].clipName.Compare(clipName))
		{
			tempIndex = clipPool[i].clipIndex;
			break;
		}
	}

	return tempIndex;
}

///////////// CLIP POOL END /////////////
