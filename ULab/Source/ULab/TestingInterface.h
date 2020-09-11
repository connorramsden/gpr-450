// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyframeAnimation.h"
#include "KeyframeAnimationController.h"

#include "TestingInterface.generated.h"

UCLASS()
class ULAB_API ATestingInterface : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestingInterface();

	// The testing interface's Keyframe Pool (20+ keyframes!)
	UPROPERTY(VisibleAnywhere, Category = "Testing Interface Components")
		FKeyframePool keyframePool;
	// The testing interface's Clip Pool! (5+ clips!)
	UPROPERTY(VisibleAnywhere, Category = "Testing Interface Components")
		FClipPool clipPool;
	// One of the testing interface's Clip Controllers
	UPROPERTY(VisibleAnywhere, Category = "Testing Interface Components")
		FKeyframeAnimationController clipControllerOne;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
