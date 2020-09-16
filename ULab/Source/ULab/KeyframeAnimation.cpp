// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimation.h"
#include <Math/UnrealMath.h>

KeyframeAnimation::KeyframeAnimation()
{}

KeyframeAnimation::~KeyframeAnimation()
{}

///////////// KEYFRAME START /////////////

// Default Constructor
FKeyframe::FKeyframe()
{
	// index initialized in the Keyframe Pool

	// Arbitrary duration between 1 and 10 ticks
	duration = FMath::RandRange(1.0f, 10.0f);
	// Calculate duration inverse
	durationInv = 1.0f / duration;
	// Randomly select 'Data' (Will be more concrete in future update)
	data = FMath::Rand();
}

// Initialize a keyframe
FKeyframe::FKeyframe(const float newDuration, const int value_x)
{
	// Set duration
	duration = newDuration;
	// Calculate duration inverse
	durationInv = 1.0f / duration;
	// Set Data value (Will not be integer in future update)
	data = value_x;

	return;
}

// Default Deconstructor
FKeyframe::~FKeyframe()
{}

///////////// KEYFRAME END /////////////

///////////// KEYFRAME POOL  START /////////////

// Default KPool Constructor
FKeyframePool::FKeyframePool()
{
	// Default initialization to 20 Keyframes
	for (int i = 0; i < 20; ++i)
	{
		// Increment keyframe pool count
		poolCount++;

		// Assign a temporary keyframe a duration between 1 and 10, and a random piece of 'data'
		FKeyframe tempFrame = FKeyframe(FMath::RandRange(1.0f, 10.0f), FMath::Rand());
		// Set the temporary keyframe's index to the current keyframe count
		tempFrame.index = poolCount;

		// Add the temporary keyframe to the pool
		pool.Add(tempFrame);
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
		poolCount++;

		// Assign a temporary keyframe a duration between 1 and 10, and a random piece of 'data'
		FKeyframe tempFrame = FKeyframe(FMath::RandRange(1.0f, 10.0f), FMath::Rand());
		// Set the temporary keyframe's index to the current keyframe count
		tempFrame.index = poolCount;

		// Add the temporary keyframe to the pool
		pool.Add(tempFrame);
	}

	return;
}

// Release keyframe pool
FKeyframePool::~FKeyframePool()
{
	// Need to de-allocate array
}

///////////// KEYFRAME POOL END /////////////

///////////// CLIP START /////////////

// Default Clip Constructor
FClip::FClip()
{
	// Set default clip name
	name = "New Clip";

	// Initialize default keyframe pool (NOTE: Might not work the way I want it to!)
	keyframePool = FKeyframePool();

	// Set count
	count = keyframePool.poolCount;

	// NOTE: Might need to fix these default values, we'll see
	// Set first keyframe index to 0
	firstKeyframe = 0;
	// Last index should be 19 (since we have 20 keyframes in a default init)
	lastKeyframe = 19;

	// Calculate Duration based on keyframePool
	CalculateDuration();

	return;
}

// Specialized Clip Constructor
FClip::FClip(FString newClipName, const FKeyframePool newPool, const int firstKeyframeIndex, const int finalKeyframeIndex)
{
	// Set name
	name = newClipName;
	// Set referenced keyframe pool
	keyframePool = newPool;
	// Set count
	count = keyframePool.poolCount;
	// Set first KF index
	firstKeyframe = firstKeyframeIndex;
	// Set last KF index
	lastKeyframe = finalKeyframeIndex;

	// Calculate Duration based on keyframePool
	CalculateDuration();

	return;
}

FClip::~FClip()
{}

// Calculate clip duration as sum of keyframes' durations
void FClip::CalculateDuration()
{
	// Sum the duration of all keyframes to calculate clip duration
	for (int i = 0; i < keyframePool.poolCount; ++i)
	{
		duration += keyframePool.pool[i].duration;
	}

	// Calculate clip duration inverse
	durationInv = 1.0f / duration;

	return;
}

// Uniformly set duration and inverse across entire pool
void FClip::DistributeDuration(const float newClipDuration)
{
	// Set duration directly
	duration = newClipDuration;
	// Set inverse directly
	durationInv = 1.0f / newClipDuration;

	// Distribute uniform duration across all keyframes
	for (int i = 0; i < keyframePool.poolCount; ++i)
	{
		keyframePool.pool[i].duration = duration;
		keyframePool.pool[i].durationInv = durationInv;
	}

	return;
}

///////////// CLIP END /////////////


///////////// CLIP POOL START /////////////

// Default Clip Pool Constructor
FClipPool::FClipPool()
{}

// Specialized Clip Pool Constructor
FClipPool::FClipPool(const int newCount)
{
	for (int i = 0; i < newCount; ++i)
	{
		// Increment clip count
		count++;

		// Create a default / blank Clip
		FClip tempClip = FClip();
		// Set the clip index to the current count
		tempClip.index = count;
		// Adjust clip name based on index
		tempClip.name = tempClip.name + FString(" ") + FString::FromInt(tempClip.index);

		// Add the temp clip to the pool
		pool.Add(tempClip);
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

	for (int i = 0; i < count; ++i)
	{
		// If the names match, set temp index
		if (pool[i].name.Compare(clipName))
		{
			tempIndex = pool[i].index;
			break;
		}
	}

	return tempIndex;
}

///////////// CLIP POOL END /////////////
