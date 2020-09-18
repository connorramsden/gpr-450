// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimationController.h"

// Sets default values
FKeyframeAnimationController::FKeyframeAnimationController()
{
	// UE_LOG(LogTemp, Warning, TEXT("Clip Controller Constructor"));

	// Set default controller name
	name = "Clip Controller";

	// INIT CLIP DATA BEGIN //

	// Initialize default Clip Pool
	clipPool = FClipPool();
	// Set default index to 0
	clipIndex = 0;
	// Initialize clip time to 0
	clipTime = 0;

	if (clipPool.pool.Num() > 0)
	{
		// Initialize clip parameter (normalized keyframe time)
		clipParameter = clipTime / clipPool.pool[clipIndex].duration;

		// INIT CLIP DATA END //

		// INIT KEYFRAME DATA BEGIN //

		// Initialize to first keyframe of current clip pool
		keyframeIndex = clipPool.pool[clipIndex].firstKeyframe;
		keyframeTime = 0;
		keyframeParameter = keyframeTime / clipPool.pool[clipIndex].keyframePool.pool[keyframeIndex].duration;

		// INIT KEYFRAME DATA END //
	}
	// Init Current Playback Direction to Paused
	currPlaybackDir = 0;
	// Init Previous Playback Direction to Forward
	prevPlaybackDir = 1;
}

// Set starting clip, keyframe and state
FKeyframeAnimationController::FKeyframeAnimationController(FString ctrlName, FClipPool newPool, int clipPoolIndex)
{
	// Set controller name
	name = ctrlName;

	// INIT CLIP DATA BEGIN //

	// Set clip pool
	clipPool = newPool;
	// Set default clip index
	clipIndex = clipPoolIndex;
	// Initialize clip time to 0
	clipTime = 0;

	if (clipPool.pool.Num() >= 0)
	{
		// Initialize clip parameter (normalized keyframe time)
		clipParameter = clipTime / clipPool.pool[clipIndex].duration;


		// INIT CLIP DATA END //

		// INIT KEYFRAME DATA BEGIN //

		// Initialize to first keyframe of current clip pool
		keyframeIndex = clipPool.pool[clipIndex].firstKeyframe;
		keyframeTime = 0;
		keyframeParameter = keyframeTime / clipPool.pool[clipIndex].keyframePool.pool[keyframeIndex].duration;
	}
	// INIT KEYFRAME DATA END //

	// Init Current Playback Direction to Paused
	currPlaybackDir = 0;
	// Init Previous Playback Direction to Forward
	prevPlaybackDir = 1;
}

// Called every frame (Basically Unity Update)
void FKeyframeAnimationController::ClipControllerUpdate(float DeltaTime)
{
	// Check our pause case first. Exit if paused.
	if (currPlaybackDir == 0)
		return;

	// Adjust time step by playback direction
	DeltaTime *= currPlaybackDir;

	/* Step 01: Pre-resolution
	* Apply time step
	* One-time, single line of code, applied twice
	* Increment keyframe time AND clip time by DeltaTime
	* Utilizes numerical integration for time itself
	*/

	keyframeTime += DeltaTime;
	clipTime += DeltaTime;

	// Acquire current clip for case evaluations
	FClip currClip = GetCurrentClip();
	FKeyframe currKeyframe = GetCurrentKeyframe();

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
	switch (currPlaybackDir)
	{
		// Evaluate Reverse (Three Cases)
		case(-1):
		{
			// Reverse Skip
			if (keyframeTime < 0)
			{
				// Decrement the keyframe index (return to previous keyframe)
				keyframeIndex--;

				// Check if KFIndex has gone below current clip's set of keyframes
				if (keyframeIndex < currClip.firstKeyframe)
				{
					// Set current keyframe to last keyframe
					keyframeIndex = currClip.lastKeyframe;
					// Set clip time to duration + parameter
					clipTime = currClip.duration + keyframeParameter;
				}

				// Set keyframe time to the top of the pool
				keyframeTime = currKeyframe.duration + keyframeParameter;
			}

			break;
		}
		// Evaluate Forward (Three Cases)
		case(1):
		{
			// Check if keyframe time exceeds keyframe duration
			if (keyframeTime > currClip.duration)
			{
				// Increment the keyframe index (move to next keyframe)
				keyframeIndex++;

				// Flip keyframe time over to the next keyframe
				keyframeTime -= currClip.duration;

				// Forward Terminus (keyframe index exceeds last clip
				if (keyframeIndex > currClip.lastKeyframe)
				{
					// Move back to the first clip
					keyframeIndex = currClip.firstKeyframe;
					// reset clip time to start of keyframe time
					clipTime = keyframeTime;
				}
			}

			break;
		}
	}

	// Establish parameters without clamping. Similar to calculating inverse / normals
	clipParameter = clipTime / currClip.duration;
	keyframeParameter = keyframeTime / currKeyframe.duration;
}

