// Copyright 2020 Connor Ramsden

#include "Kinematics.h"

void KinematicsSolveForward(FHierarchyState & State)
{
	// Do partial but at root
	KinematicsSolveForwardPartial(State, 0, State.GetHierarchy()->GetNumNodes());

	return;
}

void KinematicsSolveForwardPartial(FHierarchyState & State, int FirstIndex, int NodeCount)
{
	if (State.GetHierarchy() && 
		FirstIndex < State.GetHierarchy()->GetNumNodes() && NodeCount)
	{
		// Implement FK algorithm
		//	-> For all nodes starting at first index
		//		-> if node is not root (has parent node)
		//			-> object matrix = parent object matrix * local matrix
		//		-> else
		//			-> copy local matrix to object matrix
		

	}

	return;
}

void KinematicsSolveInverse(FHierarchyState & State)
{}

void KinematicsSolveInversePartial(FHierarchyState & State, int FirstIndex, int NodeCount)
{}
