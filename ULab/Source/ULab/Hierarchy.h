// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "Hierarchy.generated.h"

USTRUCT()
struct ULAB_API FHNode
{
	GENERATED_BODY()

protected:
	// A string identifying this node
	FString Name;

	// Index in Node Hierarchy
	int Index;

	// Index of parent node in hierarchy; should always be less than Index
	int ParentIndex;

public:
	// Default Constructor
	FHNode();
	// Specialized Constructor
	FHNode(FString NewName, int NewIndex, int NewPIndex);
	// Default Deconstructor
	~FHNode();
};

USTRUCT()
struct ULAB_API FHierarchy
{
	GENERATED_BODY()

protected:
	// Member nodes: array of nodes (empty / null if unused)
	TArray<FHNode> Nodes;
	// Maximum number of nodes in Hierarchy (zero if unused)
	int NumNodes;

public:
	/** Might need other functions here, will build as necessary */

public:
	// Default Constructor
	FHierarchy();
	// Specialized Constructor
	FHierarchy(int NewCount);
	// Default Deconstructor
	~FHierarchy();
};

