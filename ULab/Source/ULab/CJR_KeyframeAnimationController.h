// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CJR_KeyframeAnimation.h"

// Must be last include
#include "CJR_KeyframeAnimationController.generated.h"

UCLASS(BlueprintType)
class ULAB_API UFKeyframeAnimationController final : public UObject
{
	GENERATED_BODY()

public:
	// Identifies controller by name. NOT the name of the clip
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components", meta = (AllowPrivateAccess =
		"true"))
	FString Name;

	// CLIP DATA BEGIN//

	// Index of clip to control in referenced pool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
	int ClipIndex;

	// Current time relative to start of clip. Between [0, current clip's duration)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
	float ClipTime;

	// Normalized keyframe time. Should always be between [0, 1)
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
	float ClipParameter;

	// CLIP DATA END //

	// KEYFRAME DATA BEGIN //

	// Index of current keyframe in referenced keyframe pool (clip references pool)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
	int KeyframeIndex;

	// Current time relative to current keyframe; always between [0, current keyframe duration)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
	float KeyframeTime;

	// Normalized keyframe time. Always between [0, 1)
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
	float KeyframeParameter;

	// KEYFRAME DATA END //

	// Active behavior of playback (-1 reverse, 0 pause, +1 forward)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
	int CurrPlaybackDir;

	// Previous behavior of playback. Defaults to 1 (Forward Play)
	UPROPERTY(VisibleAnywhere, Category = "Clip Controller Components")
	int PrevPlaybackDir;

	// The pool of clips that this Controller controls
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clip Controller Components")
	UFClipPool* ClipPool;
protected:
	bool bIsResolved = false;

private:
	// Return the current clip from the clip pool
	FORCEINLINE UFClip* GetCurrentClip() const { return ClipPool->Pool[ClipIndex]; }
	// Return the current Keyframe referenced by the current Clip
	FORCEINLINE UFKeyframe* GetCurrentKeyframe() const { return GetCurrentClip()->KeyframePool->Pool[KeyframeIndex]; }
	// Return the current keyframe's duration
	FORCEINLINE float GetKeyframeDuration() const { return GetCurrentKeyframe()->Duration; }

public:
	// Sets default values for this actor's properties
	UFKeyframeAnimationController();

	void Init(FString CtrlName, UFClipPool* NewPool, int ClipPoolIndex);

	void ClipControllerUpdate(float DeltaTime);
};
