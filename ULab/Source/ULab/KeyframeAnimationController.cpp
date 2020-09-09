// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyframeAnimationController.h"

// Sets default values
AKeyframeAnimationController::AKeyframeAnimationController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKeyframeAnimationController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyframeAnimationController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

