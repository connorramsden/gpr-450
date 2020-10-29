#include "CJR_HierarchyState.h"
#include "CJR_HelperFunctions.h"
typedef FCJR_HelperFunctions FHF;

FHierarchyPose::FHierarchyPose()
{
	Pose = TArray<FSpatialPose>();
	bIsInitialized = false;
}

FHierarchyPose::~FHierarchyPose()
{
	if (Pose.Num() > 0)
	{
		Pose.Empty();
	}
}

void FHierarchyPose::Init(const int NumPoses)
{
	for (int i = 0; i < NumPoses; ++i)
	{
		// Create temp pose
		FSpatialPose TempPose;
		// Any additional init needed?
		// Add temp pose to pose array
		Pose.Add(TempPose);
	}
}


void FHierarchyPose::PoseReset(const int NodeCount, const int FirstIndex)
{
	// Error Handling
	if (Pose.Num() <= 0 || NodeCount <= 0 || Pose.Num() < NodeCount)
	{
		FHF::LogStringErr("FHP.PoseReset() passed invalid iterator count.");
		return;
	}

	// Loop through each pose from Pose[FirstIndex] to Pose[NodeCount]
	for (int i = FirstIndex; i < NodeCount; ++i)
	{
		// Reset the pose at the given index
		Pose[i].ResetPose();
	}
}

void FHierarchyPose::PoseConvert(EPoseChannel Channel, EPoseOrder Order, const int NodeCount, const int FirstIndex)
{
	// Error Handling
	if (Pose.Num() <= 0 || NodeCount <= 0 || Pose.Num() < NodeCount)
	{
		FHF::LogStringErr("FHP.PoseConvert() passed invalid iterator count.");
		return;
	}

	// Loop through each pose from Pose[FirstIndex] to Pose[NodeCount]
	for (int i = FirstIndex; i < NodeCount; ++i)
	{
		// Convert the pose at the given index
		Pose[i].PoseConvert(Channel, Order);
	}
}

void FHierarchyPose::PoseRestore(EPoseChannel Channel, EPoseOrder Order, const int NodeCount, const int FirstIndex)
{
	// Error Handling
	if (Pose.Num() <= 0 || NodeCount <= 0 || Pose.Num() < NodeCount)
	{
		FHF::LogStringErr("FHP.PoseRestore() passed invalid iterator count.");
		return;
	}

	// Loop through each pose from Pose[FirstIndex] to Pose[NodeCount]
	for (int i = FirstIndex; i < NodeCount; ++i)
	{
		// Restore the pose at the given index
		Pose[i].PoseRestore(Channel, Order);
	}
}

void FHierarchyPose::PoseCopy(FHierarchyPose Other, const int NodeCount, const int FirstIndex)
{
	// Error Handling for this Pose
	if (Pose.Num() <= 0 || NodeCount <= 0 || Pose.Num() < NodeCount)
	{
		FHF::LogStringErr("FHP.PoseCopy() passed invalid iterator count.");
		return;
	}

	// Error Handling for Other Pose
	if (Other.GetNumPoses() <= 0 || Other.GetNumPoses() < Pose.Num() || Other.GetNumPoses() < NodeCount)
	{
		FHF::LogStringErr("FHF.PoseCopy() passed invalid Other");
		return;
	}

	// Loop through each pose from Pose[FirstIndex] to Pose[NodeCount]
	for (int i = FirstIndex; i < NodeCount; ++i)
	{
		// Copy Other[i] to Pose[i]
		Pose[i].PoseCopy(Other.GetPose(i));
	}
}

void FHierarchyPose::PoseConcat(FHierarchyPose Other, const int NodeCount, const int FirstIndex)
{
	// Error Handling for this Pose
	if (Pose.Num() <= 0 || NodeCount <= 0 || Pose.Num() < NodeCount)
	{
		FHF::LogStringErr("FHP.PoseConcat() passed invalid iterator count.");
		return;
	}

	// Error Handling for Other Pose
	if (Other.GetNumPoses() <= 0 || Other.GetNumPoses() < Pose.Num() || Other.GetNumPoses() < NodeCount)
	{
		FHF::LogStringErr("FHF.PoseCopy() passed invalid Other");
		return;
	}

	for (int i = FirstIndex; i < NodeCount; ++i)
	{
		Pose[i].PoseConcat(Other.GetPose(i));
	}
}

void FHierarchyPose::PoseLerp(FHierarchyPose Other, const float U, const int NodeCount, const int FirstIndex)
{
	// Error Handling for this Pose
	if (Pose.Num() <= 0 || NodeCount <= 0 || Pose.Num() < NodeCount)
	{
		FHF::LogStringErr("FHP.PoseConcat() passed invalid iterator count.");
		return;
	}

	// Error Handling for Other Pose
	if (Other.GetNumPoses() <= 0 || Other.GetNumPoses() < Pose.Num() || Other.GetNumPoses() < NodeCount)
	{
		FHF::LogStringErr("FHF.PoseCopy() passed invalid Other");
		return;
	}

	for (int i = FirstIndex; i < NodeCount; ++i)
	{
		Pose[i].PoseLerp(Other.GetPose(i), U);
	}
}

FHierarchyPoseGroup::FHierarchyPoseGroup()
{
	Hierarchy = FHierarchy();
	HPose = TArray<FHierarchyPose>();
	Pose = TArray<FSpatialPose>();
	Channel = TArray<ESpatialPoseChannel>();
	Order = ESpatialPoseEulerOrder::PoseEulerOrder_xyz;
	HPoseCount = -1;
	PoseCount = -1;
	bIsInitialized = false;
}

FHierarchyPoseGroup::~FHierarchyPoseGroup()
{
	// Might need to clean up here, might not.
}

void FHierarchyPoseGroup::Init(FHierarchy NewH, const int NewC, const EPoseOrder NewO)
{
	if(NewH.bIsInitialized == false)
	{
		FHF::LogString("PoseGroup->Init() received an uninitialized Hierarchy");
		return;
	}

	if(NewC <= 0)
	{
		FHF::LogStringErr("PoseGroup->Init() received a PoseGroup with <= 0 PoseCount.");
		return;
	}

	// Assign members to passed variables
	Hierarchy = NewH;
	HPoseCount = NewC;
	PoseCount = HPoseCount * Hierarchy.NumNodes;
	Order = NewO;

	// Initialization complete
	bIsInitialized = true;
}

FHierarchyState::FHierarchyState()
{
	// Nothing to really Init here.
}

FHierarchyState::~FHierarchyState()
{
	// Nothing to explicitly clean up.
}

void FHierarchyState::Init(FHierarchy NewH)
{
	if(NewH.bIsInitialized == false)
	{
		FHF::LogStringErr("HierarchyState->Init() received an uninitialized Hierarchy.");
		return;
	}

	const int NodeCount = NewH.NumNodes;
	const int HPoseCount = 4;
	const int SPoseCount = HPoseCount * NodeCount;

	Hierarchy = NewH;

	// Init other poses from this Hierarchy;
	
}

void FHierarchyState::UpdateObjectInverse()
{
	FHF::NotImplemented();
}

void FHierarchyState::UpdateObjectBindToCurrent()
{
	FHF::NotImplemented();
}
