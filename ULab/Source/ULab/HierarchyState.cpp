// Copyright 2020 Connor Ramsden


#include "HierarchyState.h"

FHierarchyPose::FHierarchyPose()
{}

FHierarchyPose::~FHierarchyPose()
{}

FHierarchyPoseGroup::FHierarchyPoseGroup()
{
	Hierarchy = FHierarchy();

	SpatialPosePool = SPosePool();

	HierarchicalPoses = TArray<FHierarchyPose>();

	Channels = TArray<SpatialPoseChannel>();

	EulerOrder = PoseOrder::PoseEulerOrder_xyz;

	HPoseCount = 0;

	SPoseCount = HPoseCount * Hierarchy.GetNumNodes();
}

FHierarchyPoseGroup::FHierarchyPoseGroup(FHierarchy NewHier, int NumPoses)
{
	
}

FHierarchyPoseGroup::~FHierarchyPoseGroup()
{}

FHierarchyState::FHierarchyState()
{

}

FHierarchyState::~FHierarchyState()
{}
