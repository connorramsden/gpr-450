// Copyright 2020 Connor Ramsden


#include "CJR_HierarchyState.h"
#include "CJR_HelperFunctions.h"
typedef FCJR_HelperFunctions FHF;

UHierarchyPose::UHierarchyPose()
{
	Pose = TArray<USpatialPose*>();

	return;
}

UHierarchyPose::~UHierarchyPose()
{
	for (int i = 0; i < Pose.Num(); ++i)
	{
		if (Pose[i])
			Pose[i]->ConditionalBeginDestroy();
	}

	return;
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

	return;
}

void UHierarchyPose::PoseReset(const int NodeCount)
{
	// Iterate through Pose[0] --> Pose[NodeCount]
	for (int i = 0; i < NodeCount; ++i)
	{
		// Reset Pose[i]
		Pose[i]->ResetPose();
	}

	return;
}

void UHierarchyPose::PoseConvert(const int NodeCount, ESpatialPoseChannel Channel, ESpatialPoseEulerOrder Order)
{
	// Iterate through Pose[0] --> Pose[NodeCount]
	for (int i = 0; i < NodeCount; ++i)
	{
		// Convert Pose[i]
		Pose[i]->PoseConvert(Channel, Order);
	}

	return;
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

	return;
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

	return;
}

UHierarchyPoseGroup::~UHierarchyPoseGroup()
{
	if (Hierarchy)
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
	}

	return;
}

void UHierarchyPoseGroup::Init(UHierarchy* NewHier, const int NewCount, const ESpatialPoseEulerOrder NewOrder)
{
	if (NewHier != nullptr)
	{
		Hierarchy = NewHier;
	}
}

UHierarchyState::UHierarchyState()
{
	Hierarchy = NewObject<UHierarchy>();

	LocalSpace = NewObject<UHierarchyPose>();
	ObjectSpace = NewObject<UHierarchyPose>();
	ObjectSpaceInverse = NewObject<UHierarchyPose>();
	ObjectSpaceBindToCurrent = NewObject<UHierarchyPose>();

	return;
}

UHierarchyState::~UHierarchyState()
{
	if (Hierarchy)
		Hierarchy->ConditionalBeginDestroy();
	if (LocalSpace)
		LocalSpace->ConditionalBeginDestroy();
	if (ObjectSpace)
		ObjectSpace->ConditionalBeginDestroy();
	if (ObjectSpaceInverse)
		ObjectSpaceInverse->ConditionalBeginDestroy();
	if (ObjectSpaceBindToCurrent)
		ObjectSpaceBindToCurrent->ConditionalBeginDestroy();

	return;
}

void UHierarchyState::Init(UHierarchy* Hier)
{
	if (Hier)
	{
		const int NodeCount = Hier->GetNumNodes();
		const int HPoseCount = 4;
		const int SPoseCount = HPoseCount * NodeCount;

		Hierarchy = Hier;

		// Init other poses from this hierarchy
		ObjectSpace->SetPose(LocalSpace->GetPoses());
		ObjectSpaceInverse->SetPose(ObjectSpace->GetPoses());
		ObjectSpaceBindToCurrent->SetPose(ObjectSpaceInverse->GetPoses());

		for (int i = 0; i < HPoseCount; ++i)
		{
			for (int j = 0; ; j += NodeCount)
			{
				LocalSpace->GetPoses()[i] = LocalSpace->GetPoses()[j];
			}
		}

		LocalSpace->PoseReset(SPoseCount);
	}
}

void UHierarchyState::UpdateObjectInverse()
{
	if (Hierarchy)
	{
		for (int i = 0; i < Hierarchy->GetNumNodes(); ++i)
		{
			ObjectSpaceInverse->GetPoses()[i]->SetTransform(
				ObjectSpace->GetPoses()[i]->GetTransform().Inverse());
		}
	}

	return;
}

void UHierarchyState::UpdateObjectBindToCurrent()
{
	FHF::NotImplemented();
}
