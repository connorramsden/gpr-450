// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/ActorComponent.h"

#include "CJR_DataHandler.generated.h"

// Data structure to hold incoming file data / instructions

UCLASS()
class ULAB_API UFClipInstruction final : public UObject
{
	GENERATED_BODY()

public:
	// Name of clip from file
	UPROPERTY(VisibleAnywhere, Category = "Instructions", meta = (AllowPrivateAccess = "true"))
	FString ClipName;

	// Duration of clip from file
	float ClipDuration;
	// Frame lengths from file
	int FirstFrame;
	int LastFrame;

	// Transition instructions
	FString RevTransition;
	FString FwdTransition;

	// Comments (reading them so nothing messes up, will be ignored)
	FString Comments;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ULAB_API UDataHandler final : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDataHandler();
	~UDataHandler();

	// An array of Clip Instructions read from file
	UPROPERTY(VisibleAnywhere, Category = "Data Components", meta = (AllowPrivateAccess = "true"))
	TArray<UFClipInstruction*> Instructions;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FString ClipPoolFile;

public:
	// Reads data from fileName
	UFUNCTION(BlueprintCallable)
	FString ReadFile(FString FileName) const;
};
