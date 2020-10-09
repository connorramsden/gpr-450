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
	
	a3_SpatialPose.inl
	Implementation of inline spatial pose operations.
*/

#include "..\a3_SpatialPose.h"


#ifdef __ANIMAL3D_SPATIALPOSE_H
#ifndef __ANIMAL3D_SPATIALPOSE_INL
#define __ANIMAL3D_SPATIALPOSE_INL


//-----------------------------------------------------------------------------

// set rotation values for a single node pose
inline a3i32 a3spatialPoseSetRotation(a3_SpatialPose* spatialPose, const a3f32 rx_degrees, const a3f32 ry_degrees, const a3f32 rz_degrees)
{
	if (spatialPose)
	{

	}
	return -1;
}

// scale
inline a3i32 a3spatialPoseSetScale(a3_SpatialPose* spatialPose, const a3f32 sx, const a3f32 sy, const a3f32 sz)
{
	if (spatialPose)
	{

	}
	return -1;
}

// translation
inline a3i32 a3spatialPoseSetTranslation(a3_SpatialPose* spatialPose, const a3f32 tx, const a3f32 ty, const a3f32 tz)
{
	if (spatialPose)
	{

	}
	return -1;
}


//-----------------------------------------------------------------------------
/*
// reset single node pose
inline a3i32 a3spatialPoseReset(a3_SpatialPose* spatialPose)
{
	if (spatialPose)
	{
		spatialPose->transform = a3mat4_identity;
		spatialPose->orientation = a3quat_identity;
		spatialPose->scale = a3vec4_one;
		spatialPose->translation = a3vec4_zero;

		// formula in slides

		// done
		return 1;
	}
	return -1;
}
*/
// convert single node pose to matrix
inline a3i32 a3spatialPoseConvert(a3mat4* mat_out, const a3_SpatialPose* spatialPose_in, const a3_SpatialPoseChannel channel, const a3_SpatialPoseEulerOrder order)
{
	if (mat_out && spatialPose_in)
	{
		// slides!

		// translate matrix
		// scale matrix
		// rotate matrix
		//	-> e.g. xyz: R(x) * R(y) * R(z) (actual aoccurrence is right to left)
		// Quaternions are NOT immune to gimbal lock
		// final = T * R* S
	}
	return -1;
}
/*
// copy operation for single node pose
inline a3i32 a3spatialPoseCopy(a3_SpatialPose* spatialPose_out, const a3_SpatialPose* spatialPose_in)
{
	if (spatialPose_out && spatialPose_in)
	{
		// step 
		// *spatialPose_out = *spatialPose_in
		// spatialPose_out->transform = spatialPose_in->transform; // no other algo will do this :(

		// Raw description of the change
		spatialPose_out->orientation = spatialPose_in->orientation;
		spatialPose_out->scale = spatialPose_in->scale;
		spatialPose_out->translation = spatialPose_in->translation;

		// lerp


		// done

		return 1;
	}
	return -1;
}
*/

inline a3i32 a3spatialPoseConcat(a3_SpatialPose * spatialPose_out, const a3_SpatialPose * spatialPose_lhs, const a3_SpatialPose * spatialPose_rhs, const a3boolean usingQuaternions)
{
	if (spatialPose_out && spatialPose_lhs && spatialPose_rhs)
	{
		// how do they concat?
		// angles:
		// orientation ->	o_lhs + o_rhs
		// scale ->			s_lhs * s_rhs (component-wise)
		// translation ->	t_slhs + t_rhs

		// quaternions:
		// orientation -> o_lhs * oh_rhs
		
		// done
		return 1;
	}

	return -1;
}

inline a3i32 a3spatialPoseLerp(a3_SpatialPose * spatialPose_out, const a3_SpatialPose * spatialPose_0, const a3_SpatialPose * spatialPose_1, const a3real u)
{
	if (spatialPose_out && spatialPose_0 && spatialPose_1)
	{
		// how do they lerp?
		// transform	->	can't / don't / won't 
		// orientation	->	lerp(o0, o1, u)
		// scale		->	lerp(s0, s1, u)
		// translation	->	lerp(t0, t1, u)

		// quaternions :
		// orientation -> lerp(o0, 01, u) -> just another 4D vector :)
		//					|q| < 1			-> s = |q|
		//				-> nlerp(...)
		//					|q| = 1
		//				-> slerp(...)
		//					|q| = 1

		// done
		return 1;
	}

	return -1;
}


//-----------------------------------------------------------------------------


#endif	// !__ANIMAL3D_SPATIALPOSE_INL
#endif	// __ANIMAL3D_SPATIALPOSE_H
