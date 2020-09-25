// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "Hierarchy.generated.h"

UCLASS()
class ULAB_API UHNode : public UObject
{
	GENERATED_BODY()

protected:
	// A string identifying this node
	UPROPERTY(VisibleAnywhere, Category = "Node Components")
		FString Name;

	// Index in Node Hierarchy
	UPROPERTY(VisibleAnywhere, Category = "Node Components")
		int Index;

	// Index of parent node in hierarchy; should always be less than Index
	UPROPERTY(VisibleAnywhere, Category = "Node Components")
		int ParentIndex;

public:
	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE int GetIndex() const { return Index; }
	FORCEINLINE int GetParIndex() const { return ParentIndex; }
	FORCEINLINE void SetName(FString NewName) { Name = NewName; }
	FORCEINLINE void SetParentIndex(const int NewParent) { ParentIndex = NewParent; }
public:
	// Default Constructor
	UHNode();
	// Specialized Constructor
	UHNode(FString NewName, int NewIndex, int NewPIndex);
	// Default Deconstructor
	~UHNode();
};

UCLASS()
class ULAB_API UHierarchy : public UObject
{
	GENERATED_BODY()

protected:
	// Member nodes: array of nodes (empty / null if unused)
	UPROPERTY(VisibleAnywhere, Category = "Hierarchy Components")
		TArray<UHNode*> Nodes;
	// Maximum number of nodes in Hierarchy (zero if unused)
	UPROPERTY(VisibleAnywhere, Category = "Hierarchy Components")
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
	FORCEINLINE UHNode * GetNodeAtIndex(int x) { return Nodes[x]; }
	FORCEINLINE int GetNumNodes() const { return NumNodes; }
public:
	// Default Constructor
	UHierarchy();
	// Specialized Constructor
	UHierarchy(int NewCount);
	// Default Deconstructor
	~UHierarchy();
};

