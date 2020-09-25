// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hierarchy.h"
#include "HierarchyState.h"
#include "SpatialPose.h"
#include "Kinematics.h"
#include "KinematicsInterface.generated.h"

UCLASS(BlueprintType)
class ULAB_API AKinematicsInterface : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CRAnimation")
		UHierarchy * Skeleton;

public:
	// Sets default values for this actor's properties
	AKinematicsInterface();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
