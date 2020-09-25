// Copyright 2020 Connor Ramsden

#include "Kinematics.h"

void KinematicsSolveForward(FHierarchyState State)
{
	// Do partial but at root
	KinematicsSolveForwardPartial(State, 0, State.GetHierarchy().GetNumNodes());

	return;
}

void KinematicsSolveForwardPartial(FHierarchyState State, int FirstIndex, int NodeCount)
{
	if (FirstIndex < State.GetHierarchy().GetNumNodes() && NodeCount > 0)
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
			int ParentIndex = State.GetHierarchy().GetNodeAtIndex(i).GetParIndex();

			// Check if node has parent node
			if (ParentIndex >= 0)
			{
				// Acquire parent object matrix
				FTransform ParentObjectMatrix = State.GetObject().GetPosePool()[ParentIndex].GetTransform();
				// Aqcuire local matrix
				FTransform LocalMatrix = State.GetLocal().GetPosePool()[i].GetTransform();

				// Set object matrix to POM * LM
				State.GetObject().GetPosePool()[i].SetTransform(ParentObjectMatrix * LocalMatrix);
			}
			else
			{
				// Get local matrix
				FSpatialPose LocalPose = State.GetLocal().GetPosePool()[i];
				// Spatial pose copy contructor
				State.GetObject().GetPosePool()[i] = LocalPose;
			}
		}
	}

	return;
}

void KinematicsSolveInverse(FHierarchyState * State)
{}

void KinematicsSolveInversePartial(FHierarchyState * State, int FirstIndex, int NodeCount)
{}
