// Copyright 2020 Connor Ramsden

#include "CJR_Kinematics.h"

void KinematicsSolveForward(FHierarchyState HierarchyState)
{
	if (HierarchyState.GetHierarchy().bIsInitialized)
	{
		// Solve for entire tree
		KinematicsSolveForwardPartial(HierarchyState, 0, HierarchyState.GetHierarchy().NumNodes);
	}
}
 
void KinematicsSolveForwardPartial(FHierarchyState HierarchyState, const int FirstIndex, const int NodeCount)
{
	const int NumNodes = HierarchyState.GetHierarchy().NumNodes;

	if (FirstIndex < NumNodes && NodeCount > 0)
	{
		/**
		* For all nodes starting at FirstIndex
		* 	-> if node is not root (has parent)
		* 		-> object matrix = parent object matrix * local matrix
		* 	-> else
		* 		-> copy local matrix to object matrix
		*/

		for (int i = FirstIndex; i < NumNodes; ++i)
		{
			// Get the node at current index
			const AHNode* Node = HierarchyState.GetHierarchy().GetNode(i);

			// Ensure we have a non-root node
			if (Node->ParentIndex >= 0)
			{
				// Get Parent Object Matrix
				FTransform ParentObjectMatrix = HierarchyState.GetObject().GetPose(Node->ParentIndex).GetTransform();

				// Get Local Matrix
				FTransform LocalMat = HierarchyState.GetLocal().GetPose(Node->Index).GetTransform();

				// Set the new Object Matrix (POM * LM)
				HierarchyState.GetObject().GetPose(Node->Index).SetTransform(ParentObjectMatrix * LocalMat);
			}
			else
			{
				// Copy Local Matrix to Object Matrix
				HierarchyState.GetObject().SetPose(Node->Index, HierarchyState.GetLocal().GetPose(Node->Index));
			}
		}
	}
}

void KinematicsSolveInverse(const FHierarchyState HierarchyState)
{
}

void KinematicsSolveInversePartial(const FHierarchyState HierarchyState, const int FirstIndex, const int NodeCount)
{
}
