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
	
}

// Called every frame
void ATestingInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestingInterface::ButtonLogTest()
{
	UE_LOG(LogTemp, Warning, TEXT("UI BUTTON CLICKED!"));
}

