// Fill out your copyright notice in the Description page of Project Settings.


#include "TestingInterface.h"

// Sets default values
ATestingInterface::ATestingInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestingInterface::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize a new pool of keyframes. Count should pull from UI elements.
	keyframePool = FKeyframePool(20);

	// Initialize a new pool of clips. Count should pull from UI elements.
	clipPool = FClipPool(5);
}

// Called every frame
void ATestingInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

