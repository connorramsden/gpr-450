// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyframeAnimation.h"

// Must be last include
#include "KeyframeAnimationController.generated.h"

UCLASS()
class ULAB_API AKeyframeAnimationController : public AActor
{
	GENERATED_BODY()

public:
	// Identifies controller by name. NOT the name of the clip
	UPROPERTY(EditAnywhere, Category = "Clip Controller Components")
		FString name;

	// Index of clip to control in referenced pool
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		uint32 clipIndex;

	// Current time relative to start of clip. Between 0 and current clip's duration
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		float clipTime;

	// Normalized keyframe time. Should always be between 0 and 1
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		float clipParameter;

	// Index of current keyframe in referenced keyframe pool (clip references pool)
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		uint32 keyframeIndex;

	// Current time relative to current keyframe; always between 0 and current keyframe duration
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		float keyframeTime;

	// Normalized keyframe time. Always between 0 and 1
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		float keyframeParameter;

	// Active behavior of playback (-1 reverse, 0 pause, +1 forward)
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		uint32 playbackDirection;

	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		FClipPool clipPool;

	// Sets default values for this actor's properties
	AKeyframeAnimationController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
