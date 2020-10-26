// Copyright 2020 Connor Ramsden

#include "CJR_Hierarchy.h"
#include "CJR_HelperFunctions.h"

typedef FCJR_HelperFunctions FHF;

AHNode::AHNode()
{
    Name = "Node";
    Index = 0;
    ParentIndex = Index - 1;

    return;
}

UHierarchy::UHierarchy()
{
    Nodes = TArray<AHNode*>();
    NumNodes = 0;
    bIsInitialized = false;

    return;
}

UHierarchy::~UHierarchy()
{
    if (Nodes.Num() > 0)
        Nodes.Empty();
}

void UHierarchy::Init(int NumNodesToCreate)
{
    FHF::LogString("Entering Hierarchy.Init()");

    TArray<FString> Names = TArray<FString>();

    for (int i = 0; i < NumNodesToCreate; ++i)
    {
        Names.Add("Node " + FString::FromInt(i));
    }

    if (NumNodes <= 0)
        NumNodes = NumNodesToCreate;

    if (Names.Num() > 0)
        Init(NumNodesToCreate, Names);
    else
        FHF::LogStringErr("Names Array is causing an error.");

    if (Nodes.Num() > 0 && bIsInitialized == false)
        bIsInitialized = true;
}

void UHierarchy::Init(int NumNodesToCreate, TArray<FString> Names)
{
    FHF::LogString("Entering Hierarchy.Init() with Names");

    // Create NumNodes nodes & append them to Nodes pool
    for (int i = 0; i < NumNodesToCreate; ++i)
    {
        // Create a temporary node
        AHNode* TempNode = NewObject<AHNode>();

        // Assign its name, index, and parent index
        TempNode->SetName(Names[i]);
        TempNode->SetIndex(i);
        TempNode->SetPIndex(i - 1);

        // Add the node to the pool
        Nodes.Add(TempNode);
        // Free memory
        TempNode->ConditionalBeginDestroy();
    }

    if (NumNodes <= 0)
        NumNodes = NumNodesToCreate;

    if (Nodes.Num() > 0 && bIsInitialized == false)
        bIsInitialized = true;
}

void UHierarchy::SetNode(int Index, int NewPIndex, FString NewName)
{
    Nodes[Index]->SetPIndex(NewPIndex);
    Nodes[Index]->SetName(NewName);
}
