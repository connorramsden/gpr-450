// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "CJR_HierarchyState.h"

// Solve forward for entire tree
void KinematicsSolveForward(const UHierarchyState& HierarchyState);

// Solve forward for given indices
void KinematicsSolveForwardPartial(const UHierarchyState& HierarchyState, const int FirstIndex, const int NodeCount);

// Solve inverse for entire tree
void KinematicsSolveInverse(const UHierarchyState& HierarchyState);

// Solve inverse for given indices
void KinematicsSolveInversePartial(const UHierarchyState& HierarchyState, const int FirstIndex, const int NodeCount);
