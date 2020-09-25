// Copyright 2020 Connor Ramsden

#include "Kinematics.h"

void KinematicsSolveForward(UHierarchyState * State)
{
	// Do partial but at root
	KinematicsSolveForwardPartial(State, 0, State->GetHierarchy()->GetNumNodes());

	return;
}

void KinematicsSolveForwardPartial(UHierarchyState * State, int FirstIndex, int NodeCount)
{
	if (State->GetHierarchy() &&
		FirstIndex < State->GetHierarchy()->GetNumNodes() && NodeCount)
	{
		// Implement FK algorithm
		//	-> For all nodes starting at first index
		//		-> if node is not root (has parent node)
		//			-> object matrix = parent object matrix * local matrix
		//		-> else
		//			-> copy local matrix to object matrix

		// Start at first index, iterate all nodes
		for (int i = FirstIndex; i < NodeCount; ++i)
		{
			int ParentIndex = State->GetHierarchy()->GetNodeAtIndex(i)->GetParIndex();

			// Check if node has parent node
			if (ParentIndex >= 0)
			{
				// Acquire parent object matrix
				FMatrix ParentObjectMatrix = State->GetObject()->GetPosePool()[ParentIndex]->GetTransform();
				// Aqcuire local matrix
				FMatrix LocalMatrix = State->GetLocal()->GetPosePool()[i]->GetTransform();

				// Set object matrix to POM * LM
				State->GetObject()->GetPosePool()[i]->SetTransform(ParentObjectMatrix * LocalMatrix);
			}
			else
			{
				// Get local matrix
				USpatialPose * LocalPose = State->GetLocal()->GetPosePool()[i];
				// Spatial pose copy contructor
				State->GetObject()->GetPosePool()[i] = LocalPose;
			}
		}
	}

	return;
}

void KinematicsSolveInverse(UHierarchyState * State)
{}

void KinematicsSolveInversePartial(UHierarchyState * State, int FirstIndex, int NodeCount)
{}
