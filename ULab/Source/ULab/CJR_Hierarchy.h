// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "CJR_Hierarchy.generated.h"

/**
 * Core of all hierarchical data
 * Contains no spatial or temporal information
 */
UCLASS(BlueprintType)
class ULAB_API AHNode final : public AActor
{
	GENERATED_BODY()

public:
	// The node's Name
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Name;

	// The Mesh that a Node is visualized by
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * Mesh;

	// Index within the Tree
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Index;
	// Parent's index within the tree
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int ParentIndex;

public:
	AHNode();

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

UCLASS(BlueprintType)
class ULAB_API UHierarchy : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	TArray<AHNode *> Nodes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	int NumNodes;

    bool bIsInitialized;
public:
	UHierarchy();
	~UHierarchy();

public:
	FORCEINLINE TArray<AHNode *> GetNodes() const { return Nodes; }			// get the entire array of nodes
	FORCEINLINE AHNode * GetNode(const int Index) { return Nodes[Index]; }	// get a specific node by index
	FORCEINLINE int GetNumNodes() const { return NumNodes; }					// return the number of nodes in the pool

public:
	// Initialize Nodes with a number of nodes
	void Init(int NodesToCreate);
	// Initialize Nodes with a number of nodes and pre-set names
	void Init(int NodesToCreate, TArray<FString> Names);
	// Change the values of a Node at the given index
	void SetNode(int Index, int NewPIndex, FString NewName);
};
