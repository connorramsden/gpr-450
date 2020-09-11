// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimationController.h"

// Sets default values
AKeyframeAnimationController::AKeyframeAnimationController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Set starting clip, keyframe and state
AKeyframeAnimationController::AKeyframeAnimationController(FString ctrlName, FClipPool newPool, uint32 clipPoolIndex)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set controller name
	name = ctrlName;
	// Set clip pool
	clipPool = newPool;
	// Set default clip index
	clipIndex = clipPoolIndex;
}

// Called when the game starts or when spawned
void AKeyframeAnimationController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame (Basically Unity Update)
void AKeyframeAnimationController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Step 01: Pre-resolution
	* Apply time step
	* One-time, single line of code, applied twice
	* Increment keyframe time AND clip time by DeltaTime
	* Utilizes numerical integration for time itself
	*/

	keyframeTime += DeltaTime;
	clipTime += DeltaTime;

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
	
	// Case 01
	if (clipTime < 0) {
		UE_LOG(LogTemp, Warning, TEXT("REVERSE TERMINUS"));
	}
	// Case 02

	// Case 03
	if (playbackDirection == -1) {
		UE_LOG(LogTemp, Warning, TEXT("Playback is in reverse!"))
	}
	
	// Case 04
	if (playbackDirection == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Playback is paused!"));
	}
	
	// Case 05
	if (playbackDirection == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Playback is forward!"));
	}

	// Case 06


	// Case 07
	// if (clipTime >= clipPool.clipPool[clipIndex].clipDuration) {
	// 	UE_LOG(LogTemp, Warning, TEXT("Forward Terminus Reached!"))
	// }
}

