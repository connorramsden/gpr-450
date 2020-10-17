// Copyright 2020 Connor Ramsden

#include "CJR_BlendInterface.h"
#include "CJR_HelperFunctions.h"

USPose* UCJR_BlendInterface::SPoseOpIdentity()
{
	USpatialPose* OutPose = NewObject<USpatialPose>();
	return OutPose;
}

USpatialPose& UCJR_BlendInterface::SPoseOpConstruct(USpatialPose& Pose, const FVector Rotation, const FVector Scale,
                                                    const FVector Translation)
{
	Pose.SetRotation(Rotation);
	Pose.SetScale(Scale);
	Pose.SetTranslation(Translation);

	return Pose;
}

USpatialPose& UCJR_BlendInterface::SPoseOpCopy(USPose& PoseOut, USPose* PoseIn)
{
	PoseOut.SetRotation(PoseIn->GetRotation());
	PoseOut.SetScale(PoseIn->GetScale());
	PoseOut.SetTranslation(PoseOut.GetTranslation());

	return PoseOut;
}

USpatialPose& UCJR_BlendInterface::SPoseOpInvert(USPose& Pose)
{
	Pose.GetRotation() *= -1.0f;
	Pose.SetScale(FVector(1.0f / Pose.GetScale().X, 1.0f / Pose.GetScale().Y, 1.0f / Pose.GetScale().Z));
	Pose.GetTranslation() *= -1.0f;

	return Pose;
}

USpatialPose& UCJR_BlendInterface::SPoseOpConcat(USPose& Lhs, USPose& Rhs)
{
	Lhs.SetRotation(Lhs.GetRotation() + Rhs.GetRotation());
	Lhs.SetScale(Lhs.GetScale() * Rhs.GetScale());
	Lhs.SetTranslation(Lhs.GetTranslation() + Rhs.GetTranslation());

	return Lhs;
}

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
	float Mat[16] = {
		0.0f, 2.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		2.0f, -5.0f, 4.0f, -1.0f,
		-1.0f, 3.0f, -3.0f, 1.0f
	};

	FMatrix RotationMatrix(Pose0.GetRotation(), Pose1.GetRotation(), Pose2.GetRotation(), Pose3.GetRotation());
	FMatrix ScaleMatrix(Pose0.GetScale(), Pose1.GetScale(), Pose2.GetScale(), Pose3.GetScale());
	FMatrix TransMatrix(Pose0.GetTranslation(), Pose1.GetTranslation(), Pose2.GetTranslation(), Pose3.GetTranslation());

	const float T0 = 0.5f;
	const float T1 = T0 * U;
	const float T2 = T1 * U;
	const float T3 = T2 * U;

	float T[4] = {T0, T1, T2, T3};

	USpatialPose OutPose;

	OutPose.SetRotation(RotationMatrix * (Mat * T));
	OutPose.SetScale(ScaleMatrix * (Mat * T));
	OutPose.SetTranslation(TransMatrix * (Mat * T));

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
