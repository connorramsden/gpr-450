// Copyright 2020 Connor Ramsden


#include "CJR_HierarchyState.h"
#include "CJR_HelperFunctions.h"
typedef FCJR_HelperFunctions FHF;

UHierarchyPose::UHierarchyPose()
{
	Pose = TArray<USpatialPose*>();
	bIsInitialized = false;

	return;
}

UHierarchyPose::~UHierarchyPose()
{
	/*
	for (int i = 0; i < Pose.Num(); ++i)
	{
		if (Pose[i])
			Pose[i]->ConditionalBeginDestroy();
	}*/
}

void UHierarchyPose::Init(const int NumPoses)
{
	for (int i = 0; i < NumPoses; ++i)
	{
		// Create temporary pose
		USpatialPose* TempPose = NewObject<USpatialPose>();

		// Add temporary pose to Pose array
		Pose.Add(TempPose);

		// Do I need to clean up TempPose here?
	}

	bIsInitialized = true;
}

void UHierarchyPose::PoseReset(const int NodeCount)
{	
	if(Pose.Num() <= 0 || NodeCount <= 0)
	{
		FHF::LogStringErr("Hierarchy Pose Count is 0 or Less.");
		return;
	}
	
	// Iterate through Pose[0] --> Pose[NodeCount]
	for (int i = 0; i < NodeCount; ++i)
	{
		// Reset Pose[i]
		Pose[i]->ResetPose();
	}
}

void UHierarchyPose::PoseConvert(const int NodeCount, ESpatialPoseChannel Channel, ESpatialPoseEulerOrder Order)
{
	// Iterate through Pose[0] --> Pose[NodeCount]
	for (int i = 0; i < NodeCount; ++i)
	{
		// Convert Pose[i]
		Pose[i]->PoseConvert(Channel, Order);
	}
}

void UHierarchyPose::PoseRestore(const int NodeCount, ESpatialPoseChannel Channel, ESpatialPoseEulerOrder Order)
{
	for (int i = 0; i < NodeCount; ++i)
	{
		Pose[i]->PoseRestore(Channel, Order);
	}
}

void UHierarchyPose::PoseCopy(UHierarchyPose* PoseIn, const int NodeCount)
{
	for (int i = 0; i < NodeCount; ++i)
	{
		Pose[i] = PoseIn->GetPoses()[i];
	}
}

void UHierarchyPose::PoseConcat(UHierarchyPose* Other, const int NodeCount)
{
	for (int i = 0; i < NodeCount; ++i)
	{
		Pose[i]->PoseConcat(Other->GetPoses()[i]);
	}
}

void UHierarchyPose::PoseLerp(UHierarchyPose* Other, const int NodeCount, const float U)
{
	for (int i = 0; i < NodeCount; ++i)
	{
		Pose[i]->PoseLerp(Other->GetPoses()[i], U);
	}
}

UHierarchyPoseGroup::UHierarchyPoseGroup()
{
	Hierarchy = NewObject<UHierarchy>();

	HPose = TArray<UHierarchyPose*>();

	Pose = TArray<USpatialPose*>();

	Channel = TArray<ESpatialPoseChannel>();

	Order = ESpatialPoseEulerOrder::PoseEulerOrder_xyz;

	PoseCount = -1;

	bIsInitialized = false;

	return;
}

UHierarchyPoseGroup::~UHierarchyPoseGroup()
{
	/*if (Hierarchy)
		Hierarchy->ConditionalBeginDestroy();
	for (int i = 0; i < HPose.Num(); ++i)
	{
		if (HPose[i])
			HPose[i]->ConditionalBeginDestroy();
	}

	for (int i = 0; i < Pose.Num(); ++i)
	{
		if (Pose[i])
			Pose[i]->ConditionalBeginDestroy();
	}*/
}

void UHierarchyPoseGroup::Init(UHierarchy* NewHier, const int NewCount, const ESpatialPoseEulerOrder NewOrder)
{
	// Redundant error handling for passed Hierarchy.
	if (NewHier == nullptr || NewHier->bIsInitialized == false)
	{
		FHF::LogStringErr("PoseGroup->Init() received a nullptr or uninitialized Hierarchy.");
		return;
	}

	// Error handling for passed pose count
	if(NewCount <= 0)
	{
		FHF::LogStringErr("Cannot Init() a PoseGroup with 0 or Negative PoseCount.");
		return;
	}

	// Init Hierarchy
	Hierarchy = NewHier;

	// Init pose counts
	HPoseCount = NewCount;
	PoseCount = HPoseCount * Hierarchy->GetNumNodes();

	// Init Spatial Pose Order
	Order = NewOrder;

	// Should also initialize Channel here.

	bIsInitialized = true;
}

UHierarchyState::UHierarchyState()
{
	// Instantiate Hierarchy
	Hierarchy = NewObject<UHierarchy>();

	// Instantiate all Poses
	LocalSpace = NewObject<UHierarchyPose>();
	ObjectSpace = NewObject<UHierarchyPose>();
	ObjectSpaceInverse = NewObject<UHierarchyPose>();
	ObjectSpaceBindToCurrent = NewObject<UHierarchyPose>();

	return;
}

UHierarchyState::~UHierarchyState()
{
}

void UHierarchyState::Init(UHierarchy* Hier)
{
	// Hierarchy error handling
	if (Hier == nullptr || Hier->bIsInitialized == false)
	{
		FHF::LogStringErr("HierarchyState->Init() received a nullptr or uninitialized Hierarchy.");
		return;
	}

	const int NodeCount = Hier->GetNumNodes();
	const int HPoseCount = 4;
	const int SPoseCount = HPoseCount * NodeCount;

	Hierarchy = Hier;

	// Init other poses from this hierarchy
	ObjectSpace->SetPose(LocalSpace->GetPoses());
	ObjectSpaceInverse->SetPose(ObjectSpace->GetPoses());
	ObjectSpaceBindToCurrent->SetPose(ObjectSpaceInverse->GetPoses());


	FHF::LogStringErr("Reached previous error point from HierarchyState->Init()");

	/*for (int i = 0; i < HPoseCount; ++i)
	{
		for (int j = 0; ; j += NodeCount)
		{
			LocalSpace->GetPoses()[i] = LocalSpace->GetPoses()[j];
		}
	}*/

	LocalSpace->PoseReset(SPoseCount);
}

void UHierarchyState::UpdateObjectInverse()
{
	if (Hierarchy == nullptr || Hierarchy->bIsInitialized == false)
	{
		FHF::LogStringErr("Hierarchy is null or uninitialized in HierarchyState->UpdateObjectInverse()");
		return;
	}

	for (int i = 0; i < Hierarchy->GetNumNodes(); ++i)
	{
		ObjectSpaceInverse->GetPoses()[i]->SetTransform(
			ObjectSpace->GetPoses()[i]->GetTransform().Inverse());
	}
}

void UHierarchyState::UpdateObjectBindToCurrent()
{
	FHF::NotImplemented();
}
