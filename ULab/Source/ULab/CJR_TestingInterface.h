// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CJR_KeyframeAnimation.h"
#include "CJR_KeyframeAnimationController.h"
#include "CJR_DataHandler.h"

#include "CJR_TestingInterface.generated.h"

UCLASS(BlueprintType)
class ULAB_API ATestingInterface final : public AActor
{
	GENERATED_BODY()
protected:
	const int NUM_KFPOOL = 20;
	const int NUM_CLIPPOOL = 5;
	const int NUM_CONTROLLERS = 3;

	// Init timeMult to default value
	float TimeMult = 1.0f;

public:
	// Sets default values for this actor's properties
	ATestingInterface();
	~ATestingInterface();

	// The testing interface's Keyframe Pool (20+ keyframes!)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components", meta = (AllowPrivateAccess
		= "true"))
	UFKeyframePool* KeyframePool;
	// The testing interface's Clip Pool! (5+ clips!)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components", meta = (AllowPrivateAccess
		= "true"))
	UFClipPool* ClipPool;
	// The testing interface's ClipController Pool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components", meta = (AllowPrivateAccess
		= "true"))
	TArray<UFKeyframeAnimationController*> ClipControllerPool;

	// The current clip the user is controlling
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Interface Components")
	UFClip* CurrentClip;

	// Data Handler Child Object
	UPROPERTY()
	UDataHandler* DataHandler;

	int CurrentControllerIndex = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// TIME CONTROL BEGIN //

	// Change Direction of Controller Playback
	UFUNCTION(BlueprintCallable)
	void SetControllerPlayback(int NewPlaybackState);

	// Toggle Play / Pause State
	UFUNCTION(BlueprintCallable)
	void TogglePlayPause();

	// Allows for Slow Motion
	UFUNCTION(BlueprintCallable)
	void SetTimeMultiplier(float NewMultiplier);

	// TIME CONTROL END

	// Select current clip controller to edit
	UFUNCTION(BlueprintCallable)
	void SetCurrentController(int NewIndex);

	// Select current clip to control
	UFUNCTION(BlueprintCallable)
	void SetCurrentClip(FString NewClip);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetNumControllers() const { return NUM_CONTROLLERS; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetTimeMult() const { return TimeMult; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UFKeyframeAnimationController* GetCurrentController()
	{
		return ClipControllerPool[CurrentControllerIndex];
	}
};
