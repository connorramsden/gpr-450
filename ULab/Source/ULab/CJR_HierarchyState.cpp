// Copyright 2020 Connor Ramsden


#include "CJR_HierarchyState.h"

UHierarchyPose::UHierarchyPose()
{
	Pose = NewObject<USpatialPose>();

	return;
}

UHierarchyPose::~UHierarchyPose()
{
	Pose->ConditionalBeginDestroy();

	return;
}

void UHierarchyPose::Init()
{
}

void UHierarchyPose::PoseReset(const int NodeCount)
{
	Pose->ResetPose();
	
	return;
}

void UHierarchyPose::PoseConvert()
{
}

void UHierarchyPose::PoseRestore()
{
}

void UHierarchyPose::PoseCopy()
{
}

void UHierarchyPose::PoseConcat()
{
}

void UHierarchyPose::PoseLerp()
{
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
}

void UHierarchyPoseGroup::Init(UHierarchy* NewHier, const int PoseCount, const ESpatialPoseEulerOrder NewOrder)
{
	if (NewHier != nullptr)
	{
	}
}

UHierarchyState::UHierarchyState()
{
}

UHierarchyState::~UHierarchyState()
{
	if(Hierarchy)
		Hierarchy->ConditionalBeginDestroy();
	if(LocalSpace)
		LocalSpace->ConditionalBeginDestroy();
	if(ObjectSpace)
		ObjectSpace->ConditionalBeginDestroy();
	if(ObjectSpaceInverse)
		ObjectSpaceInverse->ConditionalBeginDestroy();
	if(ObjectSpaceBindToCurrent)
		ObjectSpaceBindToCurrent->ConditionalBeginDestroy();

	return;
}

void UHierarchyState::Init()
{
}

void UHierarchyState::UpdateObjectInverse()
{
}

void UHierarchyState::UpdateObjectBindToCurrent()
{
}
