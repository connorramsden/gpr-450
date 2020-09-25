// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "HierarchyState.h"

// Forward Kinematics Algorithm
void KinematicsSolveForward(UHierarchyState* State);

// FK Algorithm starting at a specific joint
void KinematicsSolveForwardPartial(UHierarchyState * State, int FirstIndex, int NodeCount);

// Inverse Kinematics Algorithm
void KinematicsSolveInverse(UHierarchyState * State);

// IK Algorithm starting at a specific joint
void KinematicsSolveInversePartial(UHierarchyState * State, int FirstIndex, int NodeCount);