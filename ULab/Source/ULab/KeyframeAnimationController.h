// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyframeAnimation.h"

// Must be last include
#include "KeyframeAnimationController.generated.h"

USTRUCT(BlueprintType)
struct ULAB_API FKeyframeAnimationController
{
	GENERATED_BODY()

public:
	// Identifies controller by name. NOT the name of the clip
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components", meta = (AllowPrivateAccess = "true"))
		FString name;

	// CLIP DATA BEGIN//
	
	// Index of clip to control in referenced pool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
		int clipIndex;

	// Current time relative to start of clip. Between 0 and current clip's duration
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
		float clipTime;

	// Normalized keyframe time. Should always be between 0 and 1
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		float clipParameter;

	// CLIP DATA END //

	// KEYFRAME DATA BEGIN //

	// Index of current keyframe in referenced keyframe pool (clip references pool)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
		int keyframeIndex;

	// Current time relative to current keyframe; always between 0 and current keyframe duration
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
		float keyframeTime;

	// Normalized keyframe time. Always between 0 and 1
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
		float keyframeParameter;

	// KEYFRAME DATA END //

	// Active behavior of playback (-1 reverse, 0 pause, +1 forward)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
		int currPlaybackDir = 0;

	// Previous behavior of playback. Defaults to 1 (Forward Play)
	int prevPlaybackDir = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
		FClipPool clipPool;

protected:
	bool bIsResolved = false;

public:
	// Sets default values for this actor's properties
	FKeyframeAnimationController();

	// set starting clip, keyframe and state
	FKeyframeAnimationController(FString ctrlName, FClipPool newPool, int clipPoolIndex);

	void ClipControllerUpdate(float DeltaTime);
};
