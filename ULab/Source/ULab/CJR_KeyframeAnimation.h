// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CJR_KeyframeAnimation.generated.h"

UCLASS(BlueprintType)
class ULAB_API UFKeyframe final : public UObject
{
	GENERATED_BODY()
public:
	// Index in pool of keyframes
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
	int Index;
	// Interval of time for which this keyframe is active. Cannot be zero
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Keyframe Components")
	float Duration;
	// Reciprocal of kDuration
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
	float DurationInv;
	// Value of the sample described by a keyframe. Just an integer for example purposes
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Components")
	int Data;
	
	// Default Constructor
	UFKeyframe();
	// Release a keyframe
	~UFKeyframe();

	// Init a Keyframe
	void Init(const float NewDuration, const int Value_X);
};

UCLASS(BlueprintType)
class ULAB_API UFKeyframePool final : public UObject
{
	GENERATED_BODY()
public:
	// Array of all keyframes in the pool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Keyframe Pool Components")
	TArray<UFKeyframe*> Pool;

	// Number of keyframes in the pool
	UPROPERTY(VisibleAnywhere, Category = "Keyframe Pool Components")
	int PoolCount = -1;
	
	// Default KPool Constructor
	UFKeyframePool();
	// Release keyframe pool
	~UFKeyframePool();
	
	void Init(const int Count);
};

UCLASS(BlueprintType)
class ULAB_API UFClip final : public UObject
{
	GENERATED_BODY()

public:
	// Identifies the clip
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Components", meta = (AllowPrivateAccess = "true"))
	FString Name;
	// Index in clip pool
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
	int Index;
	// Duration of the clip; can be calculated as sum of all referenced keyframes or set first & distribute. Cannot be 0
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
	float Duration;
	// Inverse of clipDuration
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
	float DurationInv;
	// Number of keyframes referenced by clip
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
	int Count;
	// index of first keyframe in pool ref'd by clip
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
	int FirstKeyframe;
	// index of final keyframe in pool ref'd by clip
	UPROPERTY(VisibleAnywhere, Category = "Clip Components")
	int LastKeyframe;
	// The pool of keyframes containing those included in this set.
	UPROPERTY()
	UFKeyframePool* KeyframePool;

	// Default Clip Constructor
	UFClip();
	// Release Clip
	~UFClip();

	void Init(FString NewClipName, UFKeyframePool* NewPool, const int FirstKeyframeIndex,
           const int FinalKeyframeIndex);

	// Calculate clip duration as sum of keyframes' durations
	void CalculateDuration();
	// Uniformly set duration and inverse across entire pool
	void DistributeDuration(const float NewClipDuration);
};

UCLASS(BlueprintType)
class ULAB_API UFClipPool final : public UObject
{
	GENERATED_BODY()

public:
	// Array of Clips
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clip Pool Components")
	TArray<UFClip*> Pool;

	// Number of Clips in the Pool
	UPROPERTY(EditAnywhere, Category = "Clip Pool Components")
	int Count = -1;

	// Default ClipPool Constructor
	UFClipPool();
	// Release Clip Pool
	~UFClipPool();

	void Init(const int NewCount);

	// Get Clip Index from Pool
	int GetClipIndexInPool(FString ClipName);
};
