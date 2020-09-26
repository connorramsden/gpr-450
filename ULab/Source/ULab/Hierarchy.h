// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hierarchy.generated.h"

UCLASS(BlueprintType)
class ULAB_API AHNode : public AActor
{
	GENERATED_BODY()

protected:
	// A string identifying this node
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Components")
		FString Name;

	// Index in Node Hierarchy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Components")
		int Index;

	// Index of parent node in hierarchy; should always be less than Index
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Components")
		int ParentIndex;

public:
	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE int GetIndex() const { return Index; }
	FORCEINLINE int GetParIndex() const { return ParentIndex; }
	FORCEINLINE void SetName(FString NewName) { Name = NewName; }
	FORCEINLINE void SetIndex(const int NewIndex) { Index = NewIndex; }
	FORCEINLINE void SetParentIndex(const int NewParent) { ParentIndex = NewParent; }
public:
	// Default Constructor
	AHNode();
	// Default Deconstructor
	~AHNode();
};

USTRUCT(BlueprintType)
struct ULAB_API FHierarchy
{
	GENERATED_BODY()

protected:
	// Member nodes: array of nodes (empty / null if unused)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hierarchy Components")
		TArray<AHNode*> Nodes;
	// Maximum number of nodes in Hierarchy (zero if unused)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hierarchy Components")
		int NumNodes;

public:
	/** Replace the node at the given index with params */
	void SetNode(const int NewIndex, const int NewPIndex, FString NewName);
	/** Get the names of every node in the hierarchy */
	TArray<FString> GetNodeNames();
	/** Check if node is parent of other */
	bool IsParentNode(const int PIndex, const int OIndex);
	/** Check if node is child of other */
	bool IsChildNode(const int CIndex, const int OIndex);

public:
	FORCEINLINE AHNode * GetNodeAtIndex(int x) { return Nodes[x]; }
	FORCEINLINE int GetNumNodes() const { return NumNodes; }
public:
	// Default Constructor
	FHierarchy();
	FHierarchy(int NewCount);
	// Default Deconstructor
	~FHierarchy();
};

