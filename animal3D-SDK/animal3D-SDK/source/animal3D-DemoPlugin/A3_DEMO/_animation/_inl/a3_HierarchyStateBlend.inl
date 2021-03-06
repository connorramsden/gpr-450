#include "..\a3_HierarchyStateBlend.h"
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
	
	a3_HierarchyStateBlend.inl
	Implementation of inline hierarchical blend operations.
*/


#ifdef __ANIMAL3D_HIERARCHYSTATEBLEND_H
#ifndef __ANIMAL3D_HIERARCHYSTATEBLEND_INL
#define __ANIMAL3D_HIERARCHYSTATEBLEND_INL


//-----------------------------------------------------------------------------

inline void a3SpatialPoseOpExec0C0I(a3_SpatialPoseBlendNode const * blendNode)
{
	blendNode->op(blendNode->pose_out);
}

inline void a3SpatialPoseOpExec2C1I(a3_SpatialPoseBlendNode const * blendNode)
{
	blendNode->op(blendNode->pose_out, blendNode->pose_ctrl[0], blendNode->pose_ctrl[1], blendNode->u[0]);
}

inline void a3SpatialPoseTreeExec(a3_SpatialPoseBlendTree const * blendTree)
{
	// iterate through nodes IN REVERSE ORDER (child nodes execute first)
	a3i32 i;

	for (i = blendTree->blendTreeDescriptor->numNodes - 1;
		i >= 0; --i)
	{
		blendTree->nodes[i].exec(blendTree->nodes + i);
	}
}

// pointer-based reset/identity operation for single spatial pose
inline a3_SpatialPose* a3spatialPoseOpIdentity(a3_SpatialPose* pose_out)
{
	pose_out->transform = a3mat4_identity;
	// ...

	pose_out->orientation = a3vec4_w;
	pose_out->angles = a3vec4_w;
	pose_out->scale = a3vec4_one;
	pose_out->translation = a3vec4_w;

	// done
	return pose_out;
}

// pointer-based LERP operation for single spatial pose
inline a3_SpatialPose* a3spatialPoseOpLERP(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3real const u)
{
	a3real4Lerp(pose_out->angles.v, pose0->angles.v, pose1->angles.v, u);
	a3real4Lerp(pose_out->scale.v, pose0->scale.v, pose1->scale.v, u);
	a3real4Lerp(pose_out->translation.v, pose0->translation.v, pose1->translation.v, u);

	// quat
	// a3...lerp(pose_out->orientation.v, ...);
	// slerp
	// nlerp

	// done
	return pose_out;
}

// concat ...


inline a3_SpatialPose * a3SpatialPoseOpConst(a3_SpatialPose * pose_in)
{
	return pose_in;
}

inline a3_SpatialPose * a3SpatialPoseOpCopy(a3_SpatialPose * pose_out, a3_SpatialPose const * pose_in)
{
	return pose_out;
}

//-----------------------------------------------------------------------------

// data-based reset/identity
inline a3_SpatialPose a3spatialPoseDOpIdentity()
{
	a3_SpatialPose const result = { a3mat4_identity /*, ...*/ };
	return result;
}

// data-based LERP
inline a3_SpatialPose a3spatialPoseDOpLERP(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3real const u)
{
	a3_SpatialPose result = { 0 };
	// ...

	// done
	return result;
}


//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for hierarchical pose
inline a3_HierarchyPose* a3hierarchyPoseOpIdentity(a3_HierarchyPose* pose_out)
{

	// done
	return pose_out;
}

// pointer-based LERP operation for hierarchical pose
inline a3_HierarchyPose* a3hierarchyPoseOpLERP(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3real const u)
{

	// done
	return pose_out;
}


//-----------------------------------------------------------------------------


#endif	// !__ANIMAL3D_HIERARCHYSTATEBLEND_INL
#endif	// __ANIMAL3D_HIERARCHYSTATEBLEND_H