// Copyright 2020 Connor Ramsden

#include "KinematicsInterface.h"

// Sets default values
AKinematicsInterface::AKinematicsInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AKinematicsInterface::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKinematicsInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

