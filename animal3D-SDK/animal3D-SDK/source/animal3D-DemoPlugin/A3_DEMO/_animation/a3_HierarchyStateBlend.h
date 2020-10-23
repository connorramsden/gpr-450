/*
	Copyright 2011-2020 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein

	a3_HierarchyStateBlend.h
	Hierarchy blend operations.
*/

#ifndef __ANIMAL3D_HIERARCHYSTATEBLEND_H
#define __ANIMAL3D_HIERARCHYSTATEBLEND_H


#include "a3_HierarchyState.h"

#include "a3_Kinematics.h"


#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
typedef struct a3_SpatialPoseBlendNode a3_SpatialPoseBlendNode; // application of each operation
typedef struct a3_SpatialPoseBlendTree a3_SpatialPoseBlendTree; // application of hierarchy

#endif	// __cplusplus

//-----------------------------------------------------------------------------

// execution template
typedef void (*a3_SpatialPoseOpExec)(a3_SpatialPoseBlendNode const* blendNode); // Take one blend node and execute it
void a3SpatialPoseOpExec0C0I(a3_SpatialPoseBlendNode const* blendNode);
void a3SpatialPoseOpExec2C1I(a3_SpatialPoseBlendNode const* blendNode);
void a3SpatialPoseTreeExec(a3_SpatialPoseBlendTree const * blendTree);

// operation template for any spatial pose operation
//typedef a3_SpatialPose* (*a3_spatialPoseOp)(a3_SpatialPose* pose_out); // identity
//typedef a3_SpatialPose* (*a3_spatialPoseOp)(a3_SpatialPose* pose_out, a3_SpatialPose const* pose_in); // copy
//typedef a3_SpatialPose* (*a3_spatialPoseOp)(a3_SpatialPose* pose_out, a3_SpatialPose const* pose_lhs, a3_SpatialPose const* pose_rhs); // concat
//typedef a3_SpatialPose* (*a3_spatialPoseOp)(a3_SpatialPose* pose_out, a3_SpatialPose* pose_0, a3_SpatialPose* pose_1, const float u); // lerp
typedef a3_SpatialPose * (*a3_spatialPoseOp)(a3_SpatialPose * pose_out, ...); // ALL OF THEM


//-----------------------------------------------------------------------------

// complete representation of a blend operation
// POINTER IMPLIES THING COMES FROM SOMETHING ELSE
// The sum of other blend nodes (conceptually speaking)
struct a3_SpatialPoseBlendNode
{
	// execution invokation
	a3_SpatialPoseOpExec exec;

	// the op itself
	a3_spatialPoseOp op;

	// output pose
	a3_SpatialPose * pose_out; // exactly 1 ptr/ref to externally-sourced pose (target)

	// control poses
	a3_SpatialPose const * pose_ctrl[16]; // up to 16 ptrs/refs to externally-sourced pose data

	// parameters - updated by who manages them
	a3real const* u[8]; // up to 8 ptrs/refs to externally-sourced params

	// how many ofthe above (optional)
	a3ui16 ctrlCount, paramCount;
};

struct a3_SpatialPoseBlendTree
{
	a3_Hierarchy const * blendTreeDescriptor; // tells us num nodes and parent of each node

	a3_SpatialPoseBlendNode * nodes;

	// optional: child indices
};

//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for single spatial pose
a3_SpatialPose * a3spatialPoseOpIdentity(a3_SpatialPose * pose_out);

// pointer-based LERP operation for single spatial pose
a3_SpatialPose * a3spatialPoseOpLERP(a3_SpatialPose * pose_out, a3_SpatialPose const * pose0, a3_SpatialPose const * pose1, a3real const u);

// const
a3_SpatialPose * a3SpatialPoseOpConst(a3_SpatialPose * pose_in);

// copy
a3_SpatialPose * a3SpatialPoseOpCopy(a3_SpatialPose * pose_out, a3_SpatialPose const * pose_in);


//-----------------------------------------------------------------------------

// data-based reset/identity
a3_SpatialPose a3spatialPoseDOpIdentity();

// data-based LERP
a3_SpatialPose a3spatialPoseDOpLERP(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3real const u);

// const
// a3_SpatialPose & a3SpatialPoseOpConst(a3_SpatialPose & pose_inout);

// a3_SpatialPose & a3SpatialPoseOpCopy(a3_SpatialPose const & pose_in);



//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for hierarchical pose
a3_HierarchyPose * a3hierarchyPoseOpIdentity(a3_HierarchyPose * pose_out);

// pointer-based LERP operation for hierarchical pose
a3_HierarchyPose * a3hierarchyPoseOpLERP(a3_HierarchyPose * pose_out, a3_HierarchyPose const * pose0, a3_HierarchyPose const * pose1, a3real const u);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#include "_inl/a3_HierarchyStateBlend.inl"


#endif	// !__ANIMAL3D_HIERARCHYSTATEBLEND_H