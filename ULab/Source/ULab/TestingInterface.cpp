// Fill out your copyright notice in the Description page of Project Settings.


#include "TestingInterface.h"

// Sets default values
ATestingInterface::ATestingInterface()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize a new pool of keyframes. Count should pull from UI elements.
	keyframePool = FKeyframePool(NUM_KFPOOL);

	// Initialize a new pool of clips. Count should pull from UI elements.
	clipPool = FClipPool(NUM_CLIPPOOL);

	// Initialize clip controllers
	for (int i = 0; i < NUM_CONTROLLERS; ++i)
	{
		FString tempName = "Clip Controller " + FString::FromInt(i);
		clipControllerPool.Add(FKeyframeAnimationController(tempName, clipPool, 0));
	}

	// Set default controller to first controller
	SetCurrentController(0);
}

// Called when the game starts or when spawned
void ATestingInterface::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestingInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Create a custom DeltaTime utilizing time multiplier
	float customDeltaTime = timeMult * DeltaTime;

	// Update all Clip Controllers in parallel
	for (int i = 0; i < NUM_CONTROLLERS; ++i)
	{
		clipControllerPool[i].ClipControllerUpdate(customDeltaTime);
	}
}

// Select current clip controller to edit
void ATestingInterface::SetCurrentController(int newIndex)
{
	// NOTE: Needs out of bounds error handling
	currentController = clipControllerPool[newIndex];

	// Acquire current controller's current clip
	int tempClipIndex = currentController.clipIndex;

	// Update current clip to current controller's current clip
	currentClip = currentController.clipPool.pool[tempClipIndex];
}

// Play / Pause / Change Direction of Controller Playback
void ATestingInterface::SetControllerPlayback(int newPlaybackState)
{
	// Error handling for new playback state
	if (newPlaybackState < -1 || newPlaybackState > 1)
	{
		return;
	}

	// Set previous direction to current direction
	currentController.prevPlaybackDir = currentController.currPlaybackDir;

	// Set current direction to new direction
	currentController.currPlaybackDir = newPlaybackState;
}

// Toggle Play/Pause State of Current Controller
void ATestingInterface::TogglePlayPause()
{
	// If the playback state is NOT paused
	if (currentController.currPlaybackDir != 0)
	{
		// Set playback state to paused. Updates prev & curr dir.
		SetControllerPlayback(0);
	}
	// If playback state IS paused
	else
	{
		// Set playback dir to previous direction (forward / backwards, etc.)
		SetControllerPlayback(currentController.prevPlaybackDir);
	}
}

// Select current clip to control
void ATestingInterface::SetCurrentClip(FString newClip)
{
	// Acquire index of the new controlled clip
	int newClipIndex = currentController.clipPool.GetClipIndexInPool(newClip);

	// Set current clip to the acquired index in current controller's pool
	currentClip = currentController.clipPool.pool[newClipIndex];
}

// Set time multiplier for Slow Motion
void ATestingInterface::SetTimeMultiplier(float newMult)
{
	// Error handling for time multiplier
	if (newMult > 0.0f && newMult <= 2.0f)
	{
		timeMult = newMult;
	}
}