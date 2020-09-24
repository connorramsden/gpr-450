// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "HierarchyState.h"

// Forward Kinematics Algorithm
void KinematicsSolveForward(FHierarchyState & State);

// FK Algorithm starting at a specific joint
void KinematicsSolveForwardPartial(FHierarchyState & State, int FirstIndex, int NodeCount);

// Inverse Kinematics Algorithm
void KinematicsSolveInverse(FHierarchyState & State);

// IK Algorithm starting at a specific joint
void KinematicsSolveInversePartial(FHierarchyState & State, int FirstIndex, int NodeCount);