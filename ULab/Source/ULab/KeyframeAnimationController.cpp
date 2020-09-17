// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimationController.h"

// Sets default values
FKeyframeAnimationController::FKeyframeAnimationController()
{
	// Set default controller name
	name = "Clip Controller";

	// INIT CLIP DATA BEGIN //

	// Initialize default Clip Pool
	clipPool = FClipPool();
	// Set default index to 0
	clipIndex = 0;
	// Initialize clip time to 0
	clipTime = 0;

	// Initialize clip parameter (normalized keyframe time)
	clipParameter = clipTime / clipPool.pool[clipIndex].duration;

	// INIT CLIP DATA END //

	// INIT KEYFRAME DATA BEGIN //

	// Initialize to first keyframe of current clip pool
	keyframeIndex = clipPool.pool[clipIndex].firstKeyframe;
	keyframeTime = 0;
	keyframeParameter = keyframeTime / clipPool.pool[clipIndex].keyframePool.pool[keyframeIndex].duration;

	// INIT KEYFRAME DATA END //

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
	// Initialize clip parameter (normalized keyframe time)
	clipParameter = clipTime / clipPool.pool[clipIndex].duration;

	// INIT CLIP DATA END //

	// INIT KEYFRAME DATA BEGIN //

	// Initialize to first keyframe of current clip pool
	keyframeIndex = clipPool.pool[clipIndex].firstKeyframe;
	keyframeTime = 0;
	keyframeParameter = keyframeTime / clipPool.pool[clipIndex].keyframePool.pool[keyframeIndex].duration;

	// INIT KEYFRAME DATA END //

	// Init Current Playback Direction to Paused
	currPlaybackDir = 0;
	// Init Previous Playback Direction to Forward
	prevPlaybackDir = 1;
}

// Called every frame (Basically Unity Update)
void FKeyframeAnimationController::ClipControllerUpdate(float DeltaTime)
{
	/* Step 01: Pre-resolution
	* Apply time step
	* One-time, single line of code, applied twice
	* Increment keyframe time AND clip time by DeltaTime
	* Utilizes numerical integration for time itself
	*/

	keyframeTime += DeltaTime;
	clipTime += DeltaTime;

	// Reset is resolved to false
	bIsResolved = false;

	/* Step 02: Resolve time
	* While unresolved, continue to use playback behaviour to determine the NEW keyframe time & clip time
	* Update behaviour should be looping such that when the clip reaches either end,
		it starts playing again from the opposite end in the same direction
	* There are 7 cases to check for resolution. At least one will terminate the algorithm
	* Case 01: Reverse Terminus (Playhead passes clip start)
	* Case 02: Reverse Skip (Playhead enters previous keyframe
	* Case 03: Reverse (playhead rewinds towards previous [t += -dt])
	* Case 04: Paused (playhead stays put [t += 0])
	* Case 05: Forward (playhead advances towards next keyframe [t += +dt])
	* Case 06: Forward Skip (playhead enters next keyframe)
	* Case 07: Forward Terminus (playhead passes clip end)
	*/

	// Dan's notes from grading:
	// WHILE is important. Need a resolution loop (& resolution variable?)
	// 1. Check play direction: forward (3 sub-cases), reverse (3 sub-cases), paused (1)
	// 2. Check possible cases for each play dir. 
	//		-> fwdrev: same interval in [0,  d);
	//		-> surpassed interval in either (-inf, 0), or [d, inf); terminus

	// Loop while unresolved
	while (bIsResolved == false)
	{
		// Evaluate playback direction
		switch (currPlaybackDir)
		{
			// Evaluate Reverse
			case(-1):
			{
				UE_LOG(LogTemp, Warning, TEXT("Playback is REVERSE for %s"), *name);
				break;

			}
			// Evaulate Paused
			case(0):
			{
				UE_LOG(LogTemp, Warning, TEXT("Playback is PAUSED for %s"), *name);
				break;
			}
			// Evaluate Forward
			case(1):
			{
				UE_LOG(LogTemp, Warning, TEXT("Playback is FORWARD for %s"), *name);
				break;
			}
		}

		// TEMP, MARK AS RESOLVED
		bIsResolved = true;
	}
}

