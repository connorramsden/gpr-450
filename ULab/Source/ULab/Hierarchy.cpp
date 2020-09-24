// Copyright 2020 Connor Ramsden

#include "Hierarchy.h"

/// <summary>
///  Hierarchy Node: A single link in a hierarchy tree
/// </summary>

FHNode::FHNode()
{
	// Default name
	Name = "Node";
	// Assume this is root
	Index = 0;
	// Assume no parent
	ParentIndex = -1;
}

FHNode::FHNode(FString NewName, int NewIndex, int NewPIndex)
{
	Name = NewName;
	Index = NewIndex;
	ParentIndex = NewPIndex;
}

FHNode::~FHNode()
{}

/// <summary>
/// Hierarchy: Node container, a depth-sorted tree
/// </summary>

FHierarchy::FHierarchy()
{
	// Initialize empty node tree
	Nodes = TArray<FHNode>();
	// Set initial count to 0
	NumNodes = 0;
}

FHierarchy::FHierarchy(int NewCount)
{
	// Ensure positive count
	if (NewCount <= 0)
		return;

	Nodes = TArray<FHNode>();

	for (int i = 0; i < NewCount; ++i)
	{
		// Temporary node name
		FString TempName = "Node " + FString::FromInt(i);
		// Initialize a temporary node with
		//	-> Temp Name
		//	-> Index 'i'
		//	-> ParentIndex 'i-1'
		FHNode TempNode = FHNode(TempName, i, i-1);

		// Insert the temporary node into the pool
		Nodes.Add(TempNode);
	}

	NumNodes = NewCount;
}

FHierarchy::~FHierarchy()
{
	// Empty this array
	Nodes.Empty();
}
