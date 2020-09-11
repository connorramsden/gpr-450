// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyframeAnimation.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Animation Functions")
	void ButtonLogTest();
};
