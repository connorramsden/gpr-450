// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

/**
 * Simple helper functions
 */
class ULAB_API FCJR_HelperFunctions
{
	public:
	// Called when a function is not implemented, logs an error
	static void NotImplemented();
	// Log the passed string to Output Window, logs as an error
	static void LogStringErr(const FString Msg);
	// Log the passed string to Output Window
	static void LogString(const FString Msg);
	// Log the passed float (and opt. message) to Output Window
	static void LogFloat(const float F, const FString Msg = "");
};
