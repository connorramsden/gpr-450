// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "CJR_HierarchyState.h"

// Solve forward for entire tree
void KinematicsSolveForward(FHierarchyState HierarchyState);

// Solve forward for given indices
void KinematicsSolveForwardPartial(FHierarchyState HierarchyState, const int FirstIndex, const int NodeCount);

// Solve inverse for entire tree
void KinematicsSolveInverse(FHierarchyState HierarchyState);

// Solve inverse for given indices
void KinematicsSolveInversePartial(FHierarchyState HierarchyState, const int FirstIndex, const int NodeCount);
