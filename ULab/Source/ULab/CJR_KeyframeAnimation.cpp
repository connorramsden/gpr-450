// Fill out your copyright notice in the Description page of Project Settings.


#include "CJR_KeyframeAnimation.h"

///////////// KEYFRAME START /////////////

// Default Constructor
UFKeyframe::UFKeyframe()
{
	// index initialized in the Keyframe Pool
	Index = -1;
	// Arbitrary duration between 1 and 10 ticks
	Duration = FMath::RandRange(1.0f, 10.0f);
	// Calculate duration inverse
	DurationInv = 1.0f / Duration;
	// Randomly select 'Data' (Will be more concrete in future update)
	Data = FMath::Rand();
}

// Default Deconstructor
UFKeyframe::~UFKeyframe()
{
}

void UFKeyframe::Init(const float NewDuration, const int Value_X)
{
	// index initialized in Keyframe Pool
	Index = -1;
	// Set duration
	Duration = NewDuration;
	// Calculate duration inverse
	DurationInv = 1.0f / Duration;
	// Set Data value (Will not be integer in future update)
	Data = Value_X;

	return;
}

///////////// KEYFRAME END /////////////

///////////// KEYFRAME POOL  START /////////////

// Default KPool Constructor
UFKeyframePool::UFKeyframePool()
{
	// Default initialization to 20 Keyframes
	for (int i = 0; i < 20; ++i)
	{
		// Increment keyframe pool count
		PoolCount++;

		// Assign a temporary keyframe a duration between 1 and 10, and a random piece of 'data'
		UFKeyframe* TempFrame = NewObject<UFKeyframe>();

		TempFrame->Init(
			FMath::RandRange(1.0f, 10.0f), FMath::Rand());

		// Set the temporary keyframe's index to the current keyframe count
		TempFrame->Index = PoolCount;

		// Add the temporary keyframe to the pool
		Pool.Add(TempFrame);
	}

	return;
}

// Release keyframe pool
UFKeyframePool::~UFKeyframePool()
{
	// Need to de-allocate array
}

void UFKeyframePool::Init(const int Count)
{
	// Allocate array of keyframes (not sure if this function works. Might have to initialize manually)
	for (int i = 0; i < Count; ++i)
	{
		// Increment keyframe pool count
		PoolCount++;

		// Assign a temporary keyframe a duration between 1 and 10, and a random piece of 'data'
		UFKeyframe* TempFrame = NewObject<UFKeyframe>();
		TempFrame->Init(
			FMath::RandRange(1.0f, 10.0f), FMath::Rand());

		// Set the temporary keyframe's index to the current keyframe count
		TempFrame->Index = PoolCount;

		// Add the temporary keyframe to the pool
		Pool.Add(TempFrame);
	}
}


///////////// KEYFRAME POOL END /////////////

///////////// CLIP START /////////////

// Default Clip Constructor
UFClip::UFClip()
{
	// Set default clip name
	Name = "New Clip";

	// Initialize default keyframe pool (NOTE: Might not work the way I want it to!)
	KeyframePool = NewObject<UFKeyframePool>();

	// Set count
	Count = KeyframePool->PoolCount;

	// NOTE: Might need to fix these default values, we'll see
	// Set first keyframe index to 0
	FirstKeyframe = 0;
	// Last index should be 19 (since we have 20 keyframes in a default init)
	LastKeyframe = 19;

	// Init duration to 0
	Duration = 0;

	// Calculate Duration based on keyframePool
	CalculateDuration();

	return;
}

UFClip::~UFClip()
{
}

void UFClip::Init(const FString NewClipName, UFKeyframePool* NewPool, const int FirstKeyframeIndex,
                  const int FinalKeyframeIndex)
{
	// Set name
	Name = NewClipName;
	// Set referenced keyframe pool
	KeyframePool = NewPool;
	// Set count
	Count = KeyframePool->PoolCount;
	// Set first KF index
	FirstKeyframe = FirstKeyframeIndex;
	// Set last KF index
	LastKeyframe = FinalKeyframeIndex;

	// Init duration to 0
	Duration = 0;

	// Calculate Duration based on keyframePool
	CalculateDuration();

	return;
}

// Calculate clip duration as sum of keyframes' durations
void UFClip::CalculateDuration()
{
	// Sum the duration of all keyframes to calculate clip duration
	for (int i = 0; i < KeyframePool->PoolCount; ++i)
	{
		Duration += KeyframePool->Pool[i]->Duration;
	}

	// Calculate clip duration inverse
	DurationInv = 1.0f / Duration;

	return;
}

// Uniformly set duration and inverse across entire pool
void UFClip::DistributeDuration(const float NewClipDuration)
{
	// Set duration directly
	Duration = NewClipDuration;
	// Set inverse directly
	DurationInv = 1.0f / NewClipDuration;

	// Distribute uniform duration across all keyframes
	for (int i = 0; i < KeyframePool->PoolCount; ++i)
	{
		KeyframePool->Pool[i]->Duration = Duration;
		KeyframePool->Pool[i]->DurationInv = DurationInv;
	}

	return;
}

///////////// CLIP END /////////////


///////////// CLIP POOL START /////////////

// Default Clip Pool Constructor
UFClipPool::UFClipPool()
{
	// Assumes default initialization size is 5 clips
	for (int i = 0; i < 5; ++i)
	{
		Count++;

		UFClip* TempClip = NewObject<UFClip>();
		TempClip->Index = Count;
		TempClip->Name = TempClip->Name + FString(" ") + FString::FromInt(TempClip->Index);

		Pool.Add(TempClip);
	}

	return;
}

// Clip Pool Deconstructor
UFClipPool::~UFClipPool()
{
	// Do I need to deallocate anything from the pool?
}

void UFClipPool::Init(const int NewCount)
{
	for (int i = 0; i < NewCount; ++i)
	{
		// Increment clip count
		Count++;

		// Create a default / blank Clip
		UFClip* TempClip = NewObject<UFClip>();
		// Set the clip index to the current count
		TempClip->Index = Count;
		// Adjust clip name based on index
		TempClip->Name = TempClip->Name + FString(" ") + FString::FromInt(TempClip->Index);

		// Add the temp clip to the pool
		Pool.Add(TempClip);
	}

	return;
}

int UFClipPool::GetClipIndexInPool(const FString ClipName)
{
	int TempIndex = -1;

	for (int i = 0; i < Count; ++i)
	{
		// If the names match, set temp index
		if (Pool[i]->Name.Compare(ClipName))
		{
			TempIndex = Pool[i]->Index;
			break;
		}
	}

	return TempIndex;
}

///////////// CLIP POOL END /////////////
