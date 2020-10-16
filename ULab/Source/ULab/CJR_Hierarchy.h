// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CJR_Hierarchy.generated.h"

/**
 * Core of all hierarchical data
 * Contains no spatial or temporal information
 */
UCLASS()
class ULAB_API UHNode : public UObject
{
	GENERATED_BODY()

protected:
	// The node's Name
	FString Name;

	// Index within the Tree
	int Index;
	// Parent's index within the tree
	int ParentIndex;

public:
	UHNode();

public:
	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE int GetIndex() const { return Index; }
	FORCEINLINE int GetPIndex() const { return ParentIndex; }
	FORCEINLINE void SetName(const FString NewName) { Name = NewName; }
	FORCEINLINE void SetIndex(const int NewIndex) { Index = NewIndex; }
	FORCEINLINE void SetPIndex(const int NewPIndex) { ParentIndex = NewPIndex; }
};

/**
 * Effectively a Node pool
 * Nodes are sorted Tree-style, via depth
 */

UCLASS()
class ULAB_API UHierarchy : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<UHNode *> Nodes;
	int NumNodes;
public:
	UHierarchy();
	~UHierarchy();

public:
	FORCEINLINE TArray<UHNode *> GetNodes() const { return Nodes; }			// get the entire array of nodes
	FORCEINLINE UHNode * GetNode(const int Index) { return Nodes[Index]; }	// get a specific node by index
	FORCEINLINE int GetNumNodes() const { return NumNodes; }					// return the number of nodes in the pool

public:
	// Initialize Nodes with a number of nodes
	void Init(int NodesToCreate);
	// Initialize Nodes with a number of nodes and pre-set names
	void Init(int NodesToCreate, TArray<FString> Names);
	// Change the values of a Node at the given index
	void SetNode(int Index, int NewPIndex, FString NewName);
};
