// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hierarchy.h"
#include "HierarchyState.h"
#include "SpatialPose.h"
#include "Kinematics.h"
#include "KinematicsInterface.generated.h"

const int NUM_POSES = 4;

UCLASS(BlueprintType)
class ULAB_API AKinematicsInterface : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CRAnimation")
		FHierarchy Skeleton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CRAnimation")
		FHierarchyPoseGroup PosePool;
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimDebug")
		int NumSkeletonNodes;

public:
	// Sets default values for this actor's properties
	AKinematicsInterface();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
