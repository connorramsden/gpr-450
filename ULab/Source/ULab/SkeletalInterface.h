// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CJR_Hierarchy.h"
#include "CJR_SpatialPose.h"
#include "CJR_HierarchyState.h"
#include "CJR_Kinematics.h"
#include "CJR_BlendInterface.h"
#include "SkeletalInterface.generated.h"

UCLASS()
class ULAB_API ASkeletalInterface : public AActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UHierarchy* Hierarchy;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface | States")
    class UHierarchyState* BasePose;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Sets default values for this actor's properties
    ASkeletalInterface();
    ~ASkeletalInterface();
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
