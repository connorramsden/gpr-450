// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"

#include "ULabGameModeBase.generated.h"

/**
 * UMG Tutorial courtesy of: https://docs.unrealengine.com/en-US/Programming/Tutorials/UMG/index.html
 */
UCLASS()
class ULAB_API AULabGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Functions")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Functions")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** THe widget instance that we are using as our menu. */
	UPROPERTY()
		UUserWidget* CurrentWidget;
};
