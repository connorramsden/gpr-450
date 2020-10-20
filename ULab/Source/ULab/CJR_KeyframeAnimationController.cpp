// Fill out your copyright notice in the Description page of Project Settings.


#include "CJR_KeyframeAnimationController.h"

// Sets default values
UFKeyframeAnimationController::UFKeyframeAnimationController()
{
	// UE_LOG(LogTemp, Warning, TEXT("Clip Controller Constructor"));

	// Set default controller name
	Name = "Clip Controller";

	// INIT CLIP DATA BEGIN //

	// Initialize default Clip Pool
	ClipPool = NewObject<UFClipPool>();
	// Set default index to 0
	ClipIndex = 0;
	// Initialize clip time to 0
	ClipTime = 0;

	if (ClipPool->Pool.Num() > 0)
	{
		// Initialize clip parameter (normalized keyframe time)
		ClipParameter = ClipTime / ClipPool->Pool[ClipIndex]->Duration;

		// INIT CLIP DATA END //

		// INIT KEYFRAME DATA BEGIN //

		// Initialize to first keyframe of current clip pool
		KeyframeIndex = ClipPool->Pool[ClipIndex]->FirstKeyframe;
		KeyframeTime = 0;
		KeyframeParameter = KeyframeTime / ClipPool->Pool[ClipIndex]->KeyframePool->Pool[KeyframeIndex]->Duration;

		// INIT KEYFRAME DATA END //
	}
	// Init Current Playback Direction to Paused
	CurrPlaybackDir = 0;
	// Init Previous Playback Direction to Forward
	PrevPlaybackDir = 1;
}

void UFKeyframeAnimationController::Init(FString CtrlName, UFClipPool* NewPool, int ClipPoolIndex)
{
	// Set controller name
	Name = CtrlName;

	// INIT CLIP DATA BEGIN //

	// Set clip pool
	ClipPool = NewPool;
	// Set default clip index
	ClipIndex = ClipPoolIndex;
	// Initialize clip time to 0
	ClipTime = 0;

	if (ClipPool->Pool.Num() >= 0)
	{
		// Initialize clip parameter (normalized keyframe time)
		ClipParameter = ClipTime / ClipPool->Pool[ClipIndex]->Duration;


		// INIT CLIP DATA END //

		// INIT KEYFRAME DATA BEGIN //

		// Initialize to first keyframe of current clip pool
		KeyframeIndex = ClipPool->Pool[ClipIndex]->FirstKeyframe;
		KeyframeTime = 0;
		KeyframeParameter = KeyframeTime / ClipPool->Pool[ClipIndex]->KeyframePool->Pool[KeyframeIndex]->Duration;
	}
	// INIT KEYFRAME DATA END //

	// Init Current Playback Direction to Paused
	CurrPlaybackDir = 0;
	// Init Previous Playback Direction to Forward
	PrevPlaybackDir = 1;
}

// Called every frame (Basically Unity Update)
void UFKeyframeAnimationController::ClipControllerUpdate(float DeltaTime)
{
	// Check our pause case first. Exit if paused.
	if (CurrPlaybackDir == 0)
		return;

	// Adjust time step by playback direction
	DeltaTime *= CurrPlaybackDir;

	/* Step 01: Pre-resolution
	* Apply time step
	* One-time, single line of code, applied twice
	* Increment keyframe time AND clip time by DeltaTime
	* Utilizes numerical integration for time itself
	*/

	KeyframeTime += DeltaTime;
	ClipTime += DeltaTime;

	// Acquire current clip for case evaluations
	UFClip* CurrClip = GetCurrentClip();
	UFKeyframe* CurrKeyframe = GetCurrentKeyframe();

	/* Step 02: Resolve time
	* While unresolved, continue to use playback behaviour to determine the NEW keyframe time & clip time
	* Update behaviour should be looping such that when the clip reaches either end,
		it starts playing again from the opposite end in the same direction
	* There are 7 cases to check for resolution. At least one will terminate the algorithm
	* Case 01: Reverse Terminus (Playhead passes clip start)
	* Case 02: Reverse Skip (Playhead enters previous keyframe)
	* Case 03: Reverse (playhead rewinds towards previous [t += -dt])
	* Case 04: Paused (playhead stays put [t += 0])
	* Case 05: Forward (playhead advances towards next keyframe [t += +dt])
	* Case 06: Forward Skip (playhead enters next keyframe)
	* Case 07: Forward Terminus (playhead passes clip end)
	*/

	// Check play direction
	switch (CurrPlaybackDir)
	{
		// Evaluate Reverse (Three Cases)
	case(-1):
		{
			// Reverse Skip
			if (KeyframeTime < 0)
			{
				// Decrement the keyframe index (return to previous keyframe)
				KeyframeIndex--;

				// Check if KFIndex has gone below current clip's set of keyframes
				if (KeyframeIndex < CurrClip->FirstKeyframe)
				{
					// Set current keyframe to last keyframe
					KeyframeIndex = CurrClip->LastKeyframe;
					// Set clip time to duration + parameter
					ClipTime = CurrClip->Duration + KeyframeParameter;
				}

				// Set keyframe time to the top of the pool
				KeyframeTime = CurrKeyframe->Duration + KeyframeParameter;
			}

			break;
		}
		// Evaluate Forward (Three Cases)
	case(1):
		{
			// Check if keyframe time exceeds keyframe duration
			if (KeyframeTime > CurrClip->Duration)
			{
				// Increment the keyframe index (move to next keyframe)
				KeyframeIndex++;

				// Flip keyframe time over to the next keyframe
				KeyframeTime -= CurrClip->Duration;

				// Forward Terminus (keyframe index exceeds last clip
				if (KeyframeIndex > CurrClip->LastKeyframe)
				{
					// Move back to the first clip
					KeyframeIndex = CurrClip->FirstKeyframe;
					// reset clip time to start of keyframe time
					ClipTime = KeyframeTime;
				}
			}

			break;
		}
	}

	// Establish parameters without clamping. Similar to calculating inverse / normals
	ClipParameter = ClipTime / CurrClip->Duration;
	KeyframeParameter = KeyframeTime / CurrKeyframe->Duration;
}
