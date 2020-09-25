// Copyright 2020 Connor Ramsden

#include "Hierarchy.h"

/// <summary>
///  Hierarchy Node: A single link in a hierarchy tree
/// </summary>

UHNode::UHNode()
{
	// Default name
	Name = "Node";
	// Assume this is root
	Index = 0;
	// Assume no parent
	ParentIndex = -1;
}

UHNode::UHNode(FString NewName, int NewIndex, int NewPIndex)
{
	Name = NewName;
	Index = NewIndex;
	ParentIndex = NewPIndex;
}

UHNode::~UHNode()
{}

/// <summary>
/// Hierarchy: Node container, a depth-sorted tree
/// </summary>

void UHierarchy::SetNode(const int Index, const int NewPIndex, FString NewName)
{
	Nodes[Index]->SetName(NewName);
	Nodes[Index]->SetParentIndex(NewPIndex);

	return;
}

TArray<FString> UHierarchy::GetNodeNames()
{
	TArray<FString> OutNames;

	for (int i = 0; i < NumNodes; ++i)
	{
		OutNames.Add(Nodes[i]->GetName());
	}

	return OutNames;
}

bool UHierarchy::IsParentNode(const int PIndex, const int OIndex)
{
	return Nodes[OIndex]->GetParIndex() == PIndex ? true : false;
}

bool UHierarchy::IsChildNode(const int CIndex, const int OIndex)
{
	return Nodes[CIndex]->GetParIndex() == OIndex ? true : false;
}

UHierarchy::UHierarchy()
{
	// Initialize empty node tree
	Nodes = TArray<UHNode*>();
	// Set initial count to 0
	NumNodes = 0;
}

UHierarchy::UHierarchy(int NewCount)
{
	// Ensure positive count
	if (NewCount <= 0)
		return;

	Nodes = TArray<UHNode*>();

	for (int i = 0; i < NewCount; ++i)
	{
		// Temporary node name
		FString TempName = "Node " + FString::FromInt(i);
		// Initialize a temporary node with
		//	-> Temp Name
		//	-> Index 'i'
		//	-> ParentIndex 'i-1'
		
			// UHNode(TempName, i, i - 1);

		UHNode * TempNode = NewObject<UHNode>(this);

		// Insert the temporary node into the pool
		Nodes.Add(TempNode);
	}

	NumNodes = NewCount;
}

UHierarchy::~UHierarchy()
{
	// Empty this array
	Nodes.Empty();
}
