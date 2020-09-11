// Copyright Epic Games, Inc. All Rights Reserved.


#include "ULabGameModeBase.h"

void AULabGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);
}

void AULabGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	// If a widget exists, remove it and nullify
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();

		CurrentWidget = nullptr;
	}

	// Initialize a new widget, provided one exists
	if (NewWidgetClass != nullptr)
	{
		// Create a new CurrentWidget
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		// Attach CurrentWidget to Viewport
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}