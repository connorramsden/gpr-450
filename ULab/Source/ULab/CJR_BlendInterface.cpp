// Copyright 2020 Connor Ramsden

#include "CJR_BlendInterface.h"
#include "CJR_HelperFunctions.h"

// Return an Identity / Fully Reset SpatialPose
USPose* UCJR_BlendInterface::SPoseOpIdentity()
{
	USpatialPose* OutPose = NewObject<USpatialPose>();
	return OutPose;
}

// Return a Spatial Pose comprised of passed TRS
USpatialPose& UCJR_BlendInterface::SPoseOpConstruct(USpatialPose& Pose, const FVector Rotation, const FVector Scale,
                                                    const FVector Translation)
{
	Pose.SetRotation(Rotation);
	Pose.SetScale(Scale);
	Pose.SetTranslation(Translation);

	return Pose;
}

// Return a SpatialPose the same as the passed posed
USpatialPose& UCJR_BlendInterface::SPoseOpCopy(USPose& PoseOut, USPose* PoseIn)
{
	PoseOut.SetTransform(PoseIn->GetTransform());
	PoseOut.SetOrientation(PoseIn->GetOrientation());
	PoseOut.SetRotation(PoseIn->GetRotation());
	PoseOut.SetScale(PoseIn->GetScale());
	PoseOut.SetTranslation(PoseOut.GetTranslation());

	return PoseOut;
}

// Invert the passed pose
USpatialPose& UCJR_BlendInterface::SPoseOpInvert(USPose& Pose)
{
	Pose.GetRotation() *= -1.0f;
	Pose.SetScale(FVector(1.0f / Pose.GetScale().X, 1.0f / Pose.GetScale().Y, 1.0f / Pose.GetScale().Z));
	Pose.GetTranslation() *= -1.0f;

	return Pose;
}

// Concatenate the passed poses
USpatialPose& UCJR_BlendInterface::SPoseOpConcat(USPose& Lhs, USPose& Rhs)
{
	Lhs.SetRotation(Lhs.GetRotation() + Rhs.GetRotation());
	Lhs.SetScale(Lhs.GetScale() * Rhs.GetScale());
	Lhs.SetTranslation(Lhs.GetTranslation() + Rhs.GetTranslation());

	return Lhs;
}

// Blend using Nearest Neighbor
USpatialPose& UCJR_BlendInterface::SPoseOpNearest(USPose& Pose0, USPose& Pose1, const float U)
{
	if (U < 0.5f)
		return Pose0;

	return Pose1;
}

USpatialPose& UCJR_BlendInterface::SPoseOpLerp(USPose& Pose0, USPose& Pose1, const float U)
{
	Pose0.PoseLerp(&Pose1, U, EInterpMode::Mode_Linear);

	return Pose0;
}

USpatialPose& UCJR_BlendInterface::SPoseOpCubic(USPose& Pose0, USPose& Pose1, USPose& Pose2, USPose& Pose3,
                                                const float U)
{
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpIdentity(const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();

	for (int i = 0; i < NumPoses; ++i)
	{
		OutPose->AddPose(SPoseOpIdentity());
	}

	return OutPose;
}

UHierarchyPose& UCJR_BlendInterface::HPoseOpConstruct(UHPose& Pose, const FVector Rotation, const FVector Scale,
                                                      const FVector Translation, const int NumPoses)
{
	for (int i = 0; i < NumPoses; ++i)
	{
		Pose.AddPose(&SPoseOpConstruct(Pose.GetPose(i), Rotation, Scale, Translation));
	}

	return Pose;
}

UHierarchyPose& UCJR_BlendInterface::HPoseOpCopy(UHPose& PoseOut, UHPose* PoseIn, const int NumPoses)
{
	if (PoseOut.GetPoses().Num() <= PoseIn->GetPoses().Num())
	{
		for (int i = 0; i < NumPoses; ++i)
		{
			SPoseOpCopy(PoseOut.GetPose(i), &PoseIn->GetPose(i));
		}
	}

	return PoseOut;
}

UHierarchyPose& UCJR_BlendInterface::HPoseOpInvert(UHPose& Pose, const int NumPoses)
{
	for (int i = 0; i < NumPoses; ++i)
	{
		SPoseOpInvert(Pose.GetPose(i));
	}

	return Pose;
}

UHierarchyPose& UCJR_BlendInterface::HPoseOpConcat(UHPose& Lhs, UHPose& Rhs, const int NumPoses)
{
	for (int i = 0; i < NumPoses; ++i)
	{
		SPoseOpConcat(Lhs.GetPose(i), Rhs.GetPose(i));
	}

	return Lhs;
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpNearest(UHPose& Pose0, UHPose& Pose1, const float U, const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();
	for (int i = 0; i < NumPoses; ++i)
	{
		OutPose->AddPose(&SPoseOpNearest(Pose0.GetPose(i), Pose1.GetPose(i), U));
	}

	return OutPose;
}

UHierarchyPose& UCJR_BlendInterface::HPoseOpLerp(UHPose& Pose0, UHPose& Pose1, const float U, const int NumPoses)
{
	for (int i = 0; i < NumPoses; ++i)
	{
		SPoseOpLerp(Pose0.GetPose(i), Pose1.GetPose(i), U);
	}

	return Pose0;
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpCubic(UHPose& Pose0, UHPose& Pose1, UHPose& Pose2, UHPose& Pose3,
                                                  const float U, const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();

	for (int i = 0; i < NumPoses; ++i)
	{
		OutPose->AddPose(&SPoseOpCubic(Pose0.GetPose(i), Pose1.GetPose(i), Pose2.GetPose(i), Pose3.GetPose(i), U));
	}

	return OutPose;
}

USpatialPose& UCJR_BlendInterface::SPoseOpDeconcat(USPose& Lhs, USPose& Rhs)
{
	return SPoseOpConcat(Lhs, SPoseOpInvert(Rhs));
}

USpatialPose& UCJR_BlendInterface::SPoseOpScale(USPose& Pose, const float U)
{
	return SPoseOpLerp(*SPoseOpIdentity(), Pose, U);
}

USpatialPose& UCJR_BlendInterface::SPoseOpTri(USPose& Pose0, USPose& Pose1, USPose& Pose2, const float U1,
                                              const float U2)
{
	const float U = 1.0f - (U1 - U2);

	return SPoseOpConcat(SPoseOpConcat(SPoseOpScale(Pose0, U), SPoseOpScale(Pose1, U1)), SPoseOpScale(Pose1, U2));
}

USpatialPose& UCJR_BlendInterface::SPoseOpBinearest(USPose& Pose0, USPose& Pose1, USPose& Pose2, USPose& Pose3,
                                                    const float U0, const float U1, const float U)
{
	return SPoseOpNearest(SPoseOpNearest(Pose0, Pose1, U0), SPoseOpNearest(Pose2, Pose3, U1), U);
}

USpatialPose& UCJR_BlendInterface::SPoseOpBilerp(USPose& Pose0, USPose& Pose1, USPose& Pose2, USPose& Pose3,
                                                 const float U0, const float U1, const float U)
{
	return SPoseOpLerp(SPoseOpLerp(Pose0, Pose1, U0), SPoseOpLerp(Pose2, Pose3, U1), U);
}

USpatialPose& UCJR_BlendInterface::SPoseOpBicubic(USPose& PoseP0, USPose& PoseP1, USPose& PoseP2, USPose& PoseP3,
                                                  USPose& PoseN0, USPose& PoseN1, USPose& PoseN2, USPose& PoseN3,
                                                  USPose& Pose00, USPose& Pose01, USPose& Pose02, USPose& Pose03,
                                                  USPose& Pose10, USPose& Pose11, USPose& Pose12, USPose& Pose13,
                                                  const float U0, const float U1, const float U2, const float U3,
                                                  const float U)
{
	return SPoseOpCubic(SPoseOpCubic(PoseP0, PoseN0, Pose00, Pose10, U0),
	                    SPoseOpCubic(PoseP1, PoseN1, Pose01, Pose11, U1),
	                    SPoseOpCubic(PoseP2, PoseN2, Pose02, Pose12, U2),
	                    SPoseOpCubic(PoseP3, PoseN3, Pose03, Pose13, U3),
	                    U);
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpDeconcat(UHPose& Lhs, UHPose& Rhs, const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();
	for (int i = 0; i < NumPoses; ++i)
	{
		SPoseOpDeconcat(Lhs.GetPose(i), Rhs.GetPose(i));
	}

	return OutPose;
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpScale(UHPose& Pose, const float U, const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();
	for (int i = 0; i < NumPoses; ++i)
	{
		SPoseOpScale(Pose.GetPose(i), U);
	}

	return OutPose;
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpTri(UHPose& Pose0, UHPose& Pose1, UHPose& Pose2, const float U1,
                                                const float U2, const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();
	for (int i = 0; i < NumPoses; ++i)
	{
		SPoseOpTri(Pose0.GetPose(i), Pose1.GetPose(i), Pose2.GetPose(i), U1, U2);
	}

	return OutPose;
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpBinearest(UHPose& Pose0, UHPose& Pose1, UHPose& Pose2, UHPose& Pose3,
                                                      const float U0, const float U1, const float U, const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();
	for (int i = 0; i < NumPoses; ++i)
	{
		OutPose->AddPose(&SPoseOpBinearest(Pose0.GetPose(i), Pose1.GetPose(i), Pose2.GetPose(i), Pose3.GetPose(i), U0,
		                                   U1, U));
	}

	return OutPose;
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpBilerp(UHPose& Pose0, UHPose& Pose1, UHPose& Pose2, UHPose& Pose3,
                                                   const float U0, const float U1, const float U, const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();

	for (int i = 0; i < NumPoses; ++i)
	{
		OutPose->AddPose(&SPoseOpBilerp(Pose0.GetPose(i), Pose1.GetPose(i), Pose2.GetPose(i), Pose3.GetPose(i), U0, U1,
		                                U));
	}

	return OutPose;
}

UHierarchyPose* UCJR_BlendInterface::HPoseOpBicubic(UHPose& PoseP0, UHPose& PoseP1, UHPose& PoseP2, UHPose& PoseP3,
                                                    UHPose& PoseN0, UHPose& PoseN1, UHPose& PoseN2, UHPose& PoseN3,
                                                    UHPose& Pose00, UHPose& Pose01, UHPose& Pose02,
                                                    UHPose& Pose03, UHPose& Pose10, UHPose& Pose11, UHPose& Pose12,
                                                    UHPose& Pose13, const float U0, const float U1,
                                                    const float U2, const float U3, const float U,
                                                    const int NumPoses)
{
	UHierarchyPose* OutPose = NewObject<UHierarchyPose>();

	for (int i = 0; i < NumPoses; ++i)
	{
		OutPose->AddPose(&SPoseOpBicubic(PoseP0.GetPose(i), PoseP1.GetPose(i), PoseP2.GetPose(i), PoseP3.GetPose(i),
		                                 PoseN0.GetPose(i), PoseN1.GetPose(i), PoseN2.GetPose(i),
		                                 PoseN3.GetPose(i), Pose00.GetPose(i), Pose01.GetPose(i), Pose02.GetPose(i),
		                                 Pose03.GetPose(i), Pose10.GetPose(i), Pose11.GetPose(i),
		                                 Pose12.GetPose(i), Pose13.GetPose(i), U0, U1, U2, U3, U));
	}

	return OutPose;
}
