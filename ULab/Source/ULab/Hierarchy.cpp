// Copyright 2020 Connor Ramsden

#include "Hierarchy.h"

UHNode::UHNode()
{
	Name = "Node";
	Index = 0;
	ParentIndex = Index - 1;

	return;
}

UHierarchy::UHierarchy()
{
	Nodes = TArray<UHNode *>();
	NumNodes = 0;

	return;
}

UHierarchy::~UHierarchy()
{
	Nodes.Empty();

	return;
}

void UHierarchy::Init(int NumNodesToCreate)
{
	TArray<FString> Names;

	for (int i = 0; i < NumNodesToCreate; ++i)
	{
		Names.Add("Node " + FString::FromInt(i));
	}

	Init(NumNodesToCreate, Names);

	return;
}

void UHierarchy::Init(int NumNodesToCreate, TArray<FString> Names)
{
	// Create NumNodes nodes & append them to Nodes pool
	for (int i = 0; i < NumNodesToCreate; ++i)
	{
		// Create a temporary node
		UHNode * TempNode = NewObject<UHNode>();
		// Assign its name, index, and parent index
		TempNode->SetName(Names[i]);
		TempNode->SetIndex(i);
		TempNode->SetPIndex(i - 1);

		// Add the node to the pool
		Nodes.Add(TempNode);
		// Free memory
		TempNode->ConditionalBeginDestroy();
	}

	return;
}
