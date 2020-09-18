// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DataHandler.generated.h"

// Data structure to hold incoming file data / instructions

USTRUCT()
struct ULAB_API FClipInstruction
{
	GENERATED_BODY();

public:
	// Name of clip from file
	UPROPERTY(VisibleAnywhere, Category = "Instructions", meta = (AllowPrivateAccess = "true"))
	FString clipName;

	// Duration of clip from file
	float clipDuration;
	// Frame lengths from file
	int firstFrame;
	int lastFrame;

	// Transition instructions
	FString revTransition;
	FString fwdTransition;

	// Comments (reading them so nothing messes up, will be ignored)
	FString comments;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ULAB_API UDataHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDataHandler();
	~UDataHandler();

	// An array of Clip Instructions read from file
	UPROPERTY(VisibleAnywhere, Category = "Data Components", meta = (AllowPrivateAccess = "true"))
	TArray<FClipInstruction> instructions;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FString clipPoolFile;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	// Reads data from fileName
	UFUNCTION(BlueprintCallable)
		FString ReadFile(FString fileName);
};
