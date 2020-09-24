// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"

#include "Hierarchy.h"
#include "SpatialPose.h"

#include "HierarchyState.generated.h"

// A simpe wrapper for a generic array of spatial poses
USTRUCT()
struct ULAB_API FHierarchyPose
{
	GENERATED_BODY()

public:
	TArray<FSpatialPose> SpatialPose;
	FHierarchyPose();
	~FHierarchyPose();
};