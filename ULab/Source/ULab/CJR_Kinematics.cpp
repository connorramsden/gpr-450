// Copyright 2020 Connor Ramsden

#include "CJR_Kinematics.h"

void KinematicsSolveForward(const UHierarchyState& HierarchyState)
{
	if (HierarchyState.GetHierarchy())
	{
		// Solve for entire tree
		KinematicsSolveForwardPartial(HierarchyState, 0, HierarchyState.GetHierarchy()->GetNumNodes());
	}

	return;
}
 
void KinematicsSolveForwardPartial(const UHierarchyState& HierarchyState, const int FirstIndex, const int NodeCount)
{
	const int NumNodes = HierarchyState.GetHierarchy()->GetNumNodes();

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
			const AHNode* Node = HierarchyState.GetHierarchy()->GetNodes()[i];

			// Ensure we have a non-root node
			if (Node->GetPIndex() >= 0)
			{
				// Get Parent Object Matrix
				FTransform ParentObjectMatrix = HierarchyState.GetObject()->GetPoses()[Node->GetPIndex()]->
					GetTransform();

				// Get Local Matrix
				FTransform LocalMatrix = HierarchyState.GetLocal()->GetPoses()[Node->GetIndex()]->GetTransform();

				// Set the new Object Matrix (POM * LM)
				HierarchyState.GetObject()->GetPoses()[Node->GetIndex()]->SetTransform(ParentObjectMatrix * LocalMatrix);
			}
			else
			{
				// Copy Local Matrix to Object Matrix
				HierarchyState.GetObject()->GetPoses()[Node->GetIndex()] = HierarchyState.GetLocal()->GetPoses()[Node->
					GetIndex()];
			}
		}
	}

	return;
}

void KinematicsSolveInverse(const UHierarchyState& HierarchyState)
{
}

void KinematicsSolveInversePartial(const UHierarchyState& HierarchyState, const int FirstIndex, const int NodeCount)
{
}
