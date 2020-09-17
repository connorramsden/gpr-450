// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyframeAnimation.h"
#include "KeyframeAnimationController.h"

#include "TestingInterface.generated.h"

UCLASS(BlueprintType)
class ULAB_API ATestingInterface : public AActor
{
	GENERATED_BODY()
	protected:
	const int NUM_KFPOOL = 20;
	const int NUM_CLIPPOOL = 5;
	const int NUM_CONTROLLERS = 3;

	// Init timeMult to default value
	float timeMult = 1.0f;

	public:
	// Sets default values for this actor's properties
	ATestingInterface();

	// The testing interface's Keyframe Pool (20+ keyframes!)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components", meta = (AllowPrivateAccess = "true"))
		FKeyframePool keyframePool;
	// The testing interface's Clip Pool! (5+ clips!)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components", meta = (AllowPrivateAccess = "true"))
		FClipPool clipPool;
	// The testing interface's ClipController Pool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components", meta = (AllowPrivateAccess = "true"))
		TArray<FKeyframeAnimationController> clipControllerPool;

	// The current clip the user is controlling
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components")
		FClip currentClip;
	
	int currentControllerIndex = -1;

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// TIME CONTROL BEGIN //

	// Change Direction of Controller Playback
	UFUNCTION(BlueprintCallable)
		void SetControllerPlayback(int newPlaybackState);

	// Toggle Play / Pause State
	UFUNCTION(BlueprintCallable)
		void TogglePlayPause();

	// Allows for Slow Motion
	UFUNCTION(BlueprintCallable)
		void SetTimeMultiplier(float newMultiplier);

	// TIME CONTROL END

	// Select current clip controller to edit
	UFUNCTION(BlueprintCallable)
		void SetCurrentController(int newIndex);

	// Select current clip to control
	UFUNCTION(BlueprintCallable)
		void SetCurrentClip(FString newClip);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int GetNumControllers() const { return NUM_CONTROLLERS; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetTimeMult() const { return timeMult; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE FKeyframeAnimationController & GetCurrentController() { return clipControllerPool[currentControllerIndex]; }
};
