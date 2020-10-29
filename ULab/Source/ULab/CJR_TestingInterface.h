// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CJR_KeyframeAnimation.h"
#include "CJR_KeyframeAnimationController.h"
#include "CJR_DataHandler.h"

#include "CJR_TestingInterface.generated.h"

UCLASS()
class ULAB_API ATestingInterface : public AActor
{
	GENERATED_BODY()

public:
	ATestingInterface();
	~ATestingInterface();
};
