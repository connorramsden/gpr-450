// Copyright 2020 Connor Ramsden


#include "CJR_HelperFunctions.h"

void FCJR_HelperFunctions::NotImplemented()
{
	UE_LOG(LogTemp, Error, TEXT("Not Yet Implemented"));
}

void FCJR_HelperFunctions::LogStringErr(const FString Msg)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *Msg);
}

void FCJR_HelperFunctions::LogString(const FString Msg)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
}

void FCJR_HelperFunctions::LogFloat(const float F, const FString Msg)
{
	UE_LOG(LogTemp, Warning, TEXT("%s%f"), F, *Msg);
}
