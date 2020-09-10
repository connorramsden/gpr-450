// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimationController.h"

// Sets default values
AKeyframeAnimationController::AKeyframeAnimationController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Set starting clip, keyframe and state
AKeyframeAnimationController::AKeyframeAnimationController(FString ctrlName, FClipPool newPool, uint32 clipPoolIndex)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set controller name
	name = ctrlName;
	// Set clip pool
	clipPool = newPool;
	// Set default clip index
	clipIndex = clipPoolIndex;
}

// Called when the game starts or when spawned
void AKeyframeAnimationController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame (Basically Unity Update)
void AKeyframeAnimationController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

