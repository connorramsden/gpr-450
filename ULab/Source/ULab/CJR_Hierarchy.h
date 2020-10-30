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
class ULAB_API AHNode : public AActor
{
	GENERATED_BODY()

public:
	/// PROPERTIES ///

	// The node's name / identifier
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FString Name;

	// Index within the Hierarchical tree
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	int Index;

	// Index of parent within the tree (-1 if root)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	int ParentIndex;

	// The node's visual representation in Space
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	UStaticMeshComponent* Mesh;

	/// METHODS ///
	AHNode();
};

/**
 * Effectively a Node pool
 * Nodes are sorted Tree-style, via Depth
 */

USTRUCT(BlueprintType)
struct ULAB_API FHierarchy
{
	GENERATED_BODY()

	/// PROPERTIES ///
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	TArray<AHNode*> Nodes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	int NumNodes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	bool bIsInitialized;

	/// Ctor & Dtor ///
	FHierarchy();
	~FHierarchy();

	/// ACCESSORS ///
	FORCEINLINE AHNode* GetNode(const int Index) { return Nodes[Index]; }

	/// METHODS ///
	void Init(int NodesToCreate);
	void Init(int NodesToCreate, TArray<FString> Names);
	void SetNode(int Index, int NewPIndex, FString NewName);
};
