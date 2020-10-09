// Copyright 2020 Connor Ramsden


#include "HierarchyState.h"

UHierarchicalPose::UHierarchicalPose()
{
	// Init a blank array of Poses
	Poses = TArray<USpatialPose *>();
	return;
}

UHierarchicalPose::~UHierarchicalPose()
{
	if (Poses.Num() > 0)
		Poses.Empty();

	return;
}

void UHierarchicalPose::Init(int NumPoses)
{
	for (int i = 0; i < NumPoses; ++i)
	{
		USpatialPose * TempPose = NewObject<USpatialPose>();

		Poses.Add(TempPose);

		TempPose->ConditionalBeginDestroy();
	}

	return;
}

void UHierarchicalPose::Init(TArray<USpatialPose *> InitPoses)
{
	Poses = InitPoses;

	return;
}

void UHierarchicalPose::SetPose(USpatialPose * Pose, int Index)
{
	Poses[Index] = Pose;

	return;
}

void UHierarchicalPose::AddPose(USpatialPose * Pose)
{
	Poses.Add(Pose);

	return;
}

void UHierarchicalPose::ResetPoses()
{
	// For each Pose in pool, call Reset()
	for (int i = 0; i < Poses.Num(); ++i)
	{
		Poses[i]->ResetPose();
	}

	return;
}

void UHierarchicalPose::ConvertPoses(int NodeCount, PoseChannel Channel, PoseOrder Order)
{}

UHierarchyPosePool::UHierarchyPosePool()
{
	Hierarchy = NewObject<UHierarchy>();

	SpatialPoses = TArray<USpatialPose *>();

	HierarchicalPoses = TArray<UHierarchicalPose *>();

	Channels = TArray<PoseChannel>();

	EulerOrder = PoseOrder::PoseEulerOrder_xyz;

	return;
}

UHierarchyPosePool::~UHierarchyPosePool()
{
	if (Hierarchy)
		Hierarchy->ConditionalBeginDestroy();

	if (SpatialPoses.Num() > 0)
		SpatialPoses.Empty();

	if (HierarchicalPoses.Num() > 0)
		HierarchicalPoses.Empty();

	if (HierarchicalPoses.Num() > 0)
		Channels.Empty();

	return;
}

UHierarchyState::UHierarchyState()
{
	Hierarchy = NewObject<UHierarchy>();
	SamplePose = NewObject<UHierarchicalPose>();
	LocalSpacePose = NewObject<UHierarchicalPose>();
	ObjectSpacePose = NewObject<UHierarchicalPose>();
}

UHierarchyState::~UHierarchyState()
{
	if (Hierarchy)
		Hierarchy->ConditionalBeginDestroy();
	if (SamplePose)
		SamplePose->ConditionalBeginDestroy();
	if (LocalSpacePose)
		LocalSpacePose->ConditionalBeginDestroy();
	if (ObjectSpacePose)
		ObjectSpacePose->ConditionalBeginDestroy();
}
