// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/ActorComponent.h"

#include "CJR_DataHandler.generated.h"

USTRUCT()
struct ULAB_API FClipInstruction {
    GENERATED_BODY()

    public:
    FClipInstruction();
    ~FClipInstruction();
};

UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class ULAB_API UDataHandler : public UActorComponent {
    GENERATED_BODY()

    public:
    UDataHandler();
    ~UDataHandler();
};