#include "CJR_SkeletalInterface.h"


ASkeletalInterface::ASkeletalInterface()
{
	PrimaryActorTick.bCanEverTick = true;
}

ASkeletalInterface::~ASkeletalInterface()
{
}


void ASkeletalInterface::BeginPlay()
{
	Super::BeginPlay();
}

void ASkeletalInterface::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
