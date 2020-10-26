// Copyright 2020 Connor Ramsden


#include "SkeletalInterface.h"

// Sets default values
ASkeletalInterface::ASkeletalInterface()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Hierarchy = NewObject<UHierarchy>();

    BasePose = NewObject<UHierarchyState>();
}

ASkeletalInterface::~ASkeletalInterface()
{
}

// Called when the game starts or when spawned
void ASkeletalInterface::BeginPlay()
{
    Super::BeginPlay();

    // Initialize the hierarchy with a given number of nodes.
    // This number should later be pulled from elsewhere.
    Hierarchy->Init(10);

    // Initialize the BasePose from the initialized Hierarchy
    BasePose->Init(Hierarchy);
}

// Called every frame
void ASkeletalInterface::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
