// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CJR_Hierarchy.h"
#include "CJR_SpatialPose.h"
#include "CJR_HierarchyState.h"
#include "CJR_Kinematics.h"
#include "CJR_BlendInterface.h"

#include "CJR_SkeletalInterface.generated.h"

UCLASS()
class ULAB_API ASkeletalInterface : public AActor {
	GENERATED_BODY()

	protected:
	UPROPERTY()
	struct FHierarchy Hierarchy;

	UPROPERTY()

	struct FHierarchyState BasePose;

	virtual void BeginPlay() override;

	public:
	ASkeletalInterface();
	~ASkeletalInterface();

	virtual void Tick(float DeltaSeconds) override;
};