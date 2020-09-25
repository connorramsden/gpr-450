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

FHNode::~FHNode()
{}

/// <summary>
/// Hierarchy: Node container, a depth-sorted tree
/// </summary>

void FHierarchy::SetNode(const int Index, const int NewPIndex, FString NewName)
{
	if (Nodes[Index].GetIndex() <= 0)
		return;

	Nodes[Index].SetName(NewName);
	Nodes[Index].SetParentIndex(NewPIndex);

	return;
}

TArray<FString> FHierarchy::GetNodeNames()
{
	TArray<FString> OutNames;

	for (int i = 0; i < NumNodes; ++i)
	{
		OutNames.Add(Nodes[i].GetName());
	}

	return OutNames;
}

bool FHierarchy::IsParentNode(const int PIndex, const int OIndex)
{
	return Nodes[OIndex].GetParIndex() == PIndex ? true : false;
}

bool FHierarchy::IsChildNode(const int CIndex, const int OIndex)
{
	return Nodes[CIndex].GetParIndex() == OIndex ? true : false;
}

FHierarchy::FHierarchy()
{
	// Initialize empty node tree
	Nodes = TArray<FHNode>();
	// Set initial count to 0
	NumNodes = 0;

	return;
}

FHierarchy::FHierarchy(int NewCount)
{
	Nodes = TArray<FHNode>();

	for (int i = 0; i < NewCount; ++i)
	{
		FHNode TempNode = FHNode();
		TempNode.SetName("Node " + FString::FromInt(i));
		TempNode.SetIndex(i);
		TempNode.SetParentIndex(i - 1);

		Nodes.Add(TempNode);
	}

	NumNodes = NewCount;

	return;
}

FHierarchy::~FHierarchy()
{
	// Empty this array
	Nodes.Empty();

	return;
}
