#include "CJR_Hierarchy.h"
#include "CJR_HelperFunctions.h"

typedef FCJR_HelperFunctions FHF;

AHNode::AHNode()
{
	Name = "Node 0";
	Index = 0;
	ParentIndex = Index - 1;
}

FHierarchy::FHierarchy()
{
	Nodes = TArray<AHNode*>();
	NumNodes = 0;
	bIsInitialized = false;
}

FHierarchy::~FHierarchy()
{
	if (Nodes.Num() > 0)
	{
		Nodes.Empty();
	}
}

void FHierarchy::Init(int NodesToCreate)
{
	TArray<FString> Names = TArray<FString>();

	for(int i = 0; i < NodesToCreate; ++i)
	{
		Names.Add("Node " + FString::FromInt(i));
	}

	if(NumNodes <= 0)
	{
		NumNodes = NodesToCreate;
	}

	if(Names.Num() > 0)
		Init(NodesToCreate, Names);
	else
		FHF::LogStringErr("Names Array causing an error.");

	if(Nodes.Num() > 0 && bIsInitialized == false)
		bIsInitialized = true;
}

void FHierarchy::Init(int NodesToCreate, TArray<FString> Names)
{
	for(int i = 0; i < NodesToCreate; ++i)
	{
		AHNode * TempNode = NewObject<AHNode>();

		TempNode->Name = Names[i];
		TempNode->Index = i;
		TempNode->ParentIndex = i - 1;

		Nodes.Add(TempNode);
	}

	if(NumNodes <= 0)
		NumNodes = NodesToCreate;
	if(Nodes.Num() > 0 && bIsInitialized == false)
		bIsInitialized = true;
}

void FHierarchy::SetNode(int Index, int NewPIndex, FString NewName)
{
	Nodes[Index]->ParentIndex = NewPIndex;
	Nodes[Index]->Name = NewName;
}
