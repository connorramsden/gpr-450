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

	float timeMult;

public:
	// Sets default values for this actor's properties
	ATestingInterface();

	// The testing interface's Keyframe Pool (20+ keyframes!)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components")
		FKeyframePool keyframePool;
	// The testing interface's Clip Pool! (5+ clips!)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components")
		FClipPool clipPool;
	// The testing interface's ClipController Pool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components")
		TArray<FKeyframeAnimationController> clipControllerPool;

	// The current controller the user is editing
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components")
		FKeyframeAnimationController currentController;

	// The current clip the user is controlling
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components")
		FClip currentClip;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Select current clip controller to edit
	UFUNCTION(BlueprintCallable)
		void SetCurrentController(int newIndex);

	// Change Direction of Controller Playback
	UFUNCTION(BlueprintCallable)
		void SetControllerPlayback(int newPlaybackState);

	// Toggle Play / Pause State
	UFUNCTION(BlueprintCallable)
		void TogglePlayPause();

	// Select current clip to control
	UFUNCTION(BlueprintCallable)
		void SetCurrentClip(FString newClip);

	// Allows for Slow Motion
	UFUNCTION(BlueprintCallable)
		void SetTimeMultiplier(float newMultiplier);
};
