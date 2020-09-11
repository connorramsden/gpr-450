// Fill out your copyright notice in the Description page of Project Settings.


#include "ULabPlayerController.h"

void AULabPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
}