// Copyright 2020 Connor Ramsden

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CJR_Hierarchy.generated.h"

/**
 * Core of all Hierarchical data
 * Contains no spatial or temporal information
 */
UCLASS(BlueprintType)
class ULAB_API AHNode final : public AActor
{
	GENERATED_BODY()

public:
	/// PROPERTIES ///

	// The node's name / identifier
	UPROPERTY()
	FString Name;

	// Index within the Hierarchical tree
	UPROPERTY()
	int Index;

	// Index of parent within the tree (-1 if root)
	UPROPERTY()
	int ParentIndex;

	// The node's visual representation in Space
	UPROPERTY()
	UStaticMeshComponent* Mesh;

	/// METHODS ///
	AHNode();
};

/**
 * Effectively a Node pool
 * Nodes are sorted Tree-style, via Depth
 */

USTRUCT()
struct ULAB_API FHierarchy
{
	GENERATED_BODY()

public:
	/// PROPERTIES ///
	UPROPERTY()
	TArray<AHNode *> Nodes;
	UPROPERTY()
	int NumNodes;
	UPROPERTY()
	bool bIsInitialized;

	/// Ctor & Dtor ///
	FHierarchy();
	~FHierarchy();

	/// ACCESSORS ///
	FORCEINLINE AHNode * GetNode(const int Index) {return Nodes[Index];}
	
	/// METHODS ///
	void Init(int NodesToCreate);
	void Init(int NodesToCreate, TArray<FString> Names);
	void SetNode(int Index, int NewPIndex, FString NewName);
};
