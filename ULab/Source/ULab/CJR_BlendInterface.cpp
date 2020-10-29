#include "CJR_BlendInterface.h"

FSpatialPose FBlendInterface::SPoseOpIdentity()
{
	FSpatialPose OutPose;
	OutPose.ResetPose();
	return OutPose;
}

FSpatialPose FBlendInterface::SPoseOpConstruct(FSPose Pose, FVector T, FVector R, FVector S)
{
	Pose.SetTranslation(T);
	Pose.SetRotation(R);
	Pose.SetScale(S);

	return Pose;
}

FSpatialPose FBlendInterface::SPoseOpCopy(FSPose PoseOut, FSPose PoseIn)
{
	PoseOut.SetTransform(PoseIn.GetTransform());
	PoseOut.SetOrientation(PoseIn.GetOrientation());

	PoseOut.SetTranslation(PoseIn.GetTranslation());
	PoseOut.SetRotation(PoseIn.GetRotation());
	PoseOut.SetScale(PoseOut.GetScale());

	return PoseOut;
}

FSpatialPose FBlendInterface::SPoseOpInvert(FSPose Pose)
{
	Pose.SetTranslation(Pose.GetTranslation() * -1.0f);
	Pose.SetRotation(Pose.GetRotation() * -1.0f);
	Pose.SetScale(FVector(1.0f / Pose.GetScale().X, 1.0f / Pose.GetScale().Y, 1.0f / Pose.GetScale().Z));

	return Pose;
}

FSpatialPose FBlendInterface::SPoseOpConcat(FSPose Lhs, FSPose Rhs)
{
	Lhs.SetTranslation(Lhs.GetTranslation() + Rhs.GetTranslation());
	Lhs.SetRotation(Lhs.GetRotation() + Rhs.GetRotation());
	Lhs.SetScale(Lhs.GetScale() * Rhs.GetScale());

	return Lhs;
}

FSpatialPose FBlendInterface::SPoseOpNearest(FSPose Pose0, FSPose Pose1, const float U)
{
	return U < 0.5f ? Pose0 : Pose1;
}

FSpatialPose FBlendInterface::SPoseOpLerp(FSPose Pose0, FSPose Pose1, const float U)
{
	Pose0.PoseLerp(Pose1, U, EInterpMode::Mode_Linear);

	return Pose0;
}

FSpatialPose FBlendInterface::SPoseOpCubic(FSPose Pose0, FSPose Pose1, FSPose Pose2, FSPose Pose3, const float U)
{
	// TODO: Figure out how Cubic works
	return Pose0;
}

FHierarchyPose FBlendInterface::HPoseOpIdentity(FHPose  OutPose, const int NumPoses)
{
	OutPose.Init(NumPoses, SPoseOpIdentity());

	return OutPose;
}

FHierarchyPose FBlendInterface::HPoseOpConstruct(FHPose Pose, FVector T, FVector R, FVector S,
                                                  const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		Pose.AddPose(SPoseOpConstruct(Pose.GetPose(i), T, R, S));
	}

	return Pose;
}

FHierarchyPose FBlendInterface::HPoseOpCopy(FHPose PoseOut, FHPose PoseIn, const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		PoseOut.PoseCopy(PoseIn, NumPoses, FirstIndex);
	}

	return PoseOut;
}

FHierarchyPose FBlendInterface::HPoseOpInvert(FHPose Pose, const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		SPoseOpInvert(Pose.GetPose(i));
	}
	return Pose;
}

FHierarchyPose FBlendInterface::HPoseOpConcat(FHPose Lhs, FHPose Rhs, const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		SPoseOpConcat(Lhs.GetPose(i), Rhs.GetPose(i));
	}

	return Lhs;
}

FHierarchyPose FBlendInterface::HPoseOpNearest(FHPose  OutPose, FHPose Pose0, FHPose Pose1, const float U, const int NumPoses,
                                                const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(SPoseOpNearest(Pose0.GetPose(i), Pose1.GetPose(i), U));
	}

	return OutPose;
}

FHierarchyPose FBlendInterface::HPoseOpLerp(FHPose  OutPose, FHPose Pose0, FHPose Pose1, const float U, const int NumPoses,
                                             const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(SPoseOpLerp(Pose0.GetPose(i), Pose1.GetPose(i), U));
	}

	return OutPose;
}

FHierarchyPose FBlendInterface::HPoseOpCubic(FHPose  OutPose, FHPose Pose0, FHPose Pose1, FHPose Pose2, FHPose Pose3, const float U,
                                              const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(SPoseOpCubic(Pose0.GetPose(i), Pose1.GetPose(i), Pose2.GetPose(i), Pose3.GetPose(i), U));
	}

	return OutPose;
}

FSpatialPose FBlendInterface::SPoseOpDeconcat(FSPose Lhs, FSPose Rhs)
{
	return SPoseOpConcat(Lhs, SPoseOpInvert(Rhs));
}

FSpatialPose FBlendInterface::SPoseOpScale(FSPose Pose, const float U)
{	
	return SPoseOpLerp(SPoseOpIdentity(), Pose, U);
}

FSpatialPose FBlendInterface::SPoseOpTri(FSPose Pose0, FSPose Pose1, FSPose Pose2, const float U0, const float U1)
{
	const float U = 1.0f - (U0 - U1);

	return SPoseOpConcat(
		SPoseOpConcat(
			SPoseOpScale(Pose0, U), SPoseOpScale(Pose1, U0)
		), SPoseOpScale(Pose1, U1)
	);
}

FSpatialPose FBlendInterface::SPoseOpBinearest(FSPose Pose0, FSPose Pose1, FSPose Pose2, FSPose Pose3,
                                                const float U0, const float U1, const float U)
{
	return SPoseOpNearest(
		SPoseOpNearest(Pose0, Pose1, U0), SPoseOpNearest(Pose2, Pose3, U1), U);
}

FSpatialPose FBlendInterface::SPoseOpBilerp(FSPose Pose0, FSPose Pose1, FSPose Pose2, FSPose Pose3,
                                             const float U0, const float U1, const float U)
{
	return SPoseOpLerp(SPoseOpLerp(Pose0, Pose1, U0), SPoseOpLerp(Pose2, Pose3, U1), U);
}

FSpatialPose FBlendInterface::SPoseOpBicubic(FSPose PoseP0, FSPose PoseP1, FSPose PoseP2, FSPose PoseP3,
                                              FSPose PoseN0, FSPose PoseN1, FSPose PoseN2, FSPose PoseN3,
                                              FSPose Pose00, FSPose Pose01, FSPose Pose02, FSPose Pose03,
                                              FSPose Pose10, FSPose Pose11, FSPose Pose12, FSPose Pose13,
                                              const float U0, const float U1, const float U2, const float U3,
                                              const float U)
{
	return SPoseOpCubic(SPoseOpCubic(PoseP0, PoseN0, Pose00, Pose10, U0),
	                    SPoseOpCubic(PoseP1, PoseN1, Pose01, Pose11, U1),
	                    SPoseOpCubic(PoseP2, PoseN2, Pose02, Pose12, U2),
	                    SPoseOpCubic(PoseP3, PoseN3, Pose03, Pose13, U3), U);
}

FHierarchyPose FBlendInterface::HPoseOpDeconcat(FHPose  OutPose, FHPose Lhs, FHPose Rhs, const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(SPoseOpDeconcat(Lhs.GetPose(i), Rhs.GetPose(i)));
	}

	return OutPose;
}

FHierarchyPose FBlendInterface::HPoseOpScale(FHPose  OutPose, FHPose Pose, const float U, const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(SPoseOpScale(Pose.GetPose(i), U));
	}

	return OutPose;
}

FHierarchyPose FBlendInterface::HPoseOpTri(FHPose  OutPose, FHPose Pose0, FHPose Pose1, FHPose Pose2, const float U0, const float U1,
                                            const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(SPoseOpTri(Pose0.GetPose(i), Pose1.GetPose(i), Pose2.GetPose(i), U0, U1));
	}

	return OutPose;
}

FHierarchyPose FBlendInterface::HPoseOpBinearest(FHPose  OutPose, FHPose Pose0, FHPose Pose1, FHPose Pose2, FHPose Pose3,
                                                  const float U0, const float U1, const float U, const int NumPoses,
                                                  const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(SPoseOpBinearest(Pose0.GetPose(i), Pose1.GetPose(i), Pose2.GetPose(i), Pose3.GetPose(i), U0, U1,
		                                 U));
	}

	return OutPose;
}

FHierarchyPose FBlendInterface::HPoseOpBilerp(FHPose  OutPose, FHPose Pose0, FHPose Pose1, FHPose Pose2, FHPose Pose3,
                                               const float U0, const float U1, const float U, const int NumPoses,
                                               const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(
			SPoseOpBilerp(Pose0.GetPose(i), Pose1.GetPose(i), Pose2.GetPose(i), Pose3.GetPose(i), U0, U1, U));
	}

	return OutPose;
}

FHierarchyPose FBlendInterface::HPoseOpBicubic(FHPose  OutPose, FHPose PoseP0, FHPose PoseP1, FHPose PoseP2, FHPose PoseP3,
                                                FHPose PoseN0, FHPose PoseN1, FHPose PoseN2, FHPose PoseN3,
                                                FHPose Pose00, FHPose Pose01, FHPose Pose02,
                                                FHPose Pose03, FHPose Pose10, FHPose Pose11, FHPose Pose12,
                                                FHPose Pose13, const float U0, const float U1,
                                                const float U2, const float U3, const float U,
                                                const int NumPoses, const int FirstIndex)
{
	for (int i = FirstIndex; i < NumPoses; ++i)
	{
		OutPose.AddPose(SPoseOpBicubic(PoseP0.GetPose(i), PoseP1.GetPose(i), PoseP2.GetPose(i), PoseP3.GetPose(i),
		                               PoseN0.GetPose(i), PoseN1.GetPose(i), PoseN2.GetPose(i), PoseN3.GetPose(i),
		                               Pose00.GetPose(i), Pose01.GetPose(i), Pose02.GetPose(i), Pose03.GetPose(i),
		                               Pose10.GetPose(i), Pose11.GetPose(i), Pose12.GetPose(i),
		                               Pose13.GetPose(i), U0, U1, U2, U3, U));
	}

	return OutPose;
}
