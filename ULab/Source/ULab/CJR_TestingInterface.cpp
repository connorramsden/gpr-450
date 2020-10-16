// Fill out your copyright notice in the Description page of Project Settings.

#include "CJR_TestingInterface.h"

// Sets default values
ATestingInterface::ATestingInterface()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KeyframePool = NewObject<UFKeyframePool>();

	KeyframePool->Init(NUM_KFPOOL);

	// Temp clip pool
	ClipPool = NewObject<UFClipPool>();

	ClipPool->Init(NUM_CLIPPOOL);

	// Initialize clip controllers
	for (int i = 0; i < NUM_CONTROLLERS; ++i)
	{
		// Set up clip controller's name with index
		const FString TempName = "Clip Controller " + FString::FromInt(i);

		// Set up the clip to control at random (0 and max clip pool count)
		const int ClipToControl = FMath::RandRange(0, ClipPool->Count - 1);

		// Initialize a temporary Clip Controller
		UFKeyframeAnimationController* TempController = NewObject<UFKeyframeAnimationController>();

		TempController->Init(TempName, ClipPool, ClipToControl);

		// Add the controller to the pool
		ClipControllerPool.Add(TempController);
	}
}

ATestingInterface::~ATestingInterface()
{
}

// Called when the game starts or when spawned
void ATestingInterface::BeginPlay()
{
	Super::BeginPlay();

	// Acquire attached data handler
	DataHandler = this->FindComponentByClass<UDataHandler>();

	TArray<UFClipInstruction*> TempInstructions = DataHandler->Instructions;

	// Iterate through data handlers instructions and initialize clips
	for (int i = 0; i < TempInstructions.Num(); ++i)
	{
		const FString TempName = TempInstructions[i]->ClipName;
		// float TempDuration = TempInstructions[i]->ClipDuration;
		const int TempFrame0 = TempInstructions[i]->FirstFrame;
		const int TempFrame1 = TempInstructions[i]->LastFrame;
		// we'll handle transitions later

		// Initialize a new clip from clip instruction
		UFClip* TempClip = NewObject<UFClip>();

		UFKeyframePool* TempPool = NewObject<UFKeyframePool>();
		TempPool->Init(TempFrame1);

		TempClip->Init(TempName, TempPool, TempFrame0, TempFrame1);

		// Add clip to clip pool
		ClipPool->Pool.Add(TempClip);
	}

	// Set default controller to first controller
	SetCurrentController(0);
}

// Called every frame
void ATestingInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Create a custom DeltaTime utilizing time multiplier
	const float CustomDeltaTime = TimeMult * DeltaTime;

	// Update all Clip Controllers in parallel
	for (int i = 0; i < NUM_CONTROLLERS; ++i)
	{
		ClipControllerPool[i]->ClipControllerUpdate(CustomDeltaTime);
	}
}

// Select current clip controller to edit
void ATestingInterface::SetCurrentController(int NewIndex)
{
	CurrentControllerIndex = NewIndex;

	UFKeyframeAnimationController* CurrCtrl = GetCurrentController();

	const int TempClipIndex = CurrCtrl->ClipIndex;
	CurrentClip = CurrCtrl->ClipPool->Pool[TempClipIndex];
}

// Play / Pause / Change Direction of Controller Playback
void ATestingInterface::SetControllerPlayback(int NewPlaybackState)
{
	UFKeyframeAnimationController* CurrCtrl = GetCurrentController();

	// Error handling for new playback state
	if (NewPlaybackState < -1 || NewPlaybackState > 1)
	{
		return;
	}

	// Set previous direction to current direction
	CurrCtrl->PrevPlaybackDir = CurrCtrl->CurrPlaybackDir;

	// Set current direction to new direction
	CurrCtrl->CurrPlaybackDir = NewPlaybackState;
}

// Toggle Play/Pause State of Current Controller
void ATestingInterface::TogglePlayPause()
{
	UFKeyframeAnimationController* CurrCtrl = GetCurrentController();

	// If the playback state is NOT paused
	if (CurrCtrl->CurrPlaybackDir != 0)
	{
		// Set playback state to paused. Updates prev & curr dir.
		SetControllerPlayback(0);
	}
		// If playback state IS paused
	else
	{
		// Set playback dir to previous direction (forward / backwards, etc.)
		SetControllerPlayback(CurrCtrl->PrevPlaybackDir);
	}
}

// Select current clip to control
void ATestingInterface::SetCurrentClip(const FString NewClip)
{
	UFKeyframeAnimationController* CurrCtrl = GetCurrentController();

	// Acquire index of the new controlled clip
	const int NewClipIndex = CurrCtrl->ClipPool->GetClipIndexInPool(NewClip);

	// Set current clip to the acquired index in current controller's pool
	CurrentClip = CurrCtrl->ClipPool->Pool[NewClipIndex];
}

// Set time multiplier for Slow Motion
void ATestingInterface::SetTimeMultiplier(const float NewMult)
{
	// Error handling for time multiplier
	if (NewMult > 0.0f && NewMult <= 2.0f)
	{
		TimeMult = NewMult;
	}
}
