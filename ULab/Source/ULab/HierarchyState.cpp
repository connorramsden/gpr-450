// Copyright 2020 Connor Ramsden

#include "HierarchyState.h"

typedef SpatialPoseEulerOrder PoseOrder;

FHierarchyPose::FHierarchyPose()
{
	Pool = TArray<FSpatialPose>();

	return;
}

FHierarchyPose::FHierarchyPose(TArray<FSpatialPose> NewPool)
{
	Pool = NewPool;

	return;
}

FHierarchyPose::~FHierarchyPose()
{
	Pool.Empty();

	return;
}

FHierarchyPoseGroup::FHierarchyPoseGroup()
{
	Hierarchy = FHierarchy();

	SpatialPosePool = TArray<FSpatialPose>();

	HierarchicalPoses = TArray<FHierarchyPose>();

	Channels = TArray<SpatialPoseChannel>();

	EulerOrder = PoseOrder::PoseEulerOrder_xyz;

	HPoseCount = 0;

	SPoseCount = HPoseCount * Hierarchy.GetNumNodes();

	return;
}

FHierarchyPoseGroup::FHierarchyPoseGroup(FHierarchy NewHier, int NumPoses)
{
	Hierarchy = NewHier;

	HPoseCount = NumPoses;
	SPoseCount = NumPoses * Hierarchy.GetNumNodes();

	HierarchicalPoses = TArray<FHierarchyPose>();
	HierarchicalPoses.Init(FHierarchyPose(), HPoseCount);

	SpatialPosePool = TArray<FSpatialPose>();
	SpatialPosePool.Init(FSpatialPose(), SPoseCount);

	Channels = TArray<SpatialPoseChannel>();
	EulerOrder = PoseOrder::PoseEulerOrder_xyz;

	return;
}

FHierarchyPoseGroup::~FHierarchyPoseGroup()
{
	HierarchicalPoses.Empty();
	SpatialPosePool.Empty();

	return;
}

FHierarchyState::FHierarchyState()
{
	Hierarchy = FHierarchy();

	SamplePose = FHierarchyPose();
	LocalSpacePose = FHierarchyPose();
	ObjectSpacePose = FHierarchyPose();

	return;
}

FHierarchyState::FHierarchyState(FHierarchy NewHier, TArray<FHierarchyPose> Poses)
{
	Hierarchy = NewHier;

	SamplePose = Poses[0];
	LocalSpacePose = Poses[1];
	ObjectSpacePose = Poses[2];

	return;
}

FHierarchyState::~FHierarchyState()
{
	return;
}
