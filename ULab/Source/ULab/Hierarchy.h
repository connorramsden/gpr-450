// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Hierarchy.generated.h"

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
	FORCEINLINE FString GetName() { return Name; }
	FORCEINLINE int GetIndex() { return Index; }
	FORCEINLINE int GetPIndex() { return ParentIndex; }
	FORCEINLINE void SetName(FString NewName) { Name = NewName; }
	FORCEINLINE void SetIndex(int NewIndex) { Index = NewIndex; }
	FORCEINLINE void SetPIndex(int NewPIndex) { ParentIndex = NewPIndex; }
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
	TArray<UHNode *> Nodes;
	int NumNodes;
public:
	UHierarchy();
	~UHierarchy();

public:
	void Init(int NodesToCreate);
	void Init(int NodesToCreate, TArray<FString> Names);
};