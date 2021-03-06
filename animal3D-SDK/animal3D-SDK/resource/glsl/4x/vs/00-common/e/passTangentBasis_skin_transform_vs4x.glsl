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
	
	passTangentBasis_skin_transform_vs4x.glsl
	Calculate and pass tangent basis with skinning.
*/

#version 450

layout (location = 0) in vec4 aPosition;
layout (location = 2) in vec4 aNormal;
layout (location = 8) in vec4 aTexcoord;
layout (location = 10) in vec4 aTangent;
layout (location = 11) in vec4 aBitangent;

// skinning attributes
// layout (location = 7) in int aSkinIndex; // which joint influences skinning
layout (location = 7) in ivec4 aSkinIndex; // smooth bind - multiple (using maximum num components for a single attribute slot)
layout (location = 1) in vec4 aSkinWeight; // how much influence

uniform mat4 uP;
uniform mat4 uMV, uMV_nrm;
uniform mat4 uAtlas;

// Max number of nodes in a skeleton
#define MAX_NODES 128

// Define our own type for dual quaternions
#define dquat mat2x4

uniform ubTransformBlend {
	mat4 uSkinMat[MAX_NODES]; // the actual skeleton in our shader
	dquat uSkinDQ[MAX_NODES];
};

// we have a list of matrices and must index it for the current vertex

out vbVertexData {
	mat4 vTangentBasis_view;
	vec4 vTexcoord_atlas;
};

flat out int vVertexID;
flat out int vInstanceID;

// a function that performs skinning without skin weights
// this will look wack: our artist is painting weights, 
	// and we need to use them
vec4 skinRigid(in vec4 v, in int index) 
{
	// v' = ()
	return (uSkinMat[index] * v);
}

// This function performs skinning with skin weights
// this has summation (sigma)
// Smooth, by Santana and Rob Thomas
vec4 skinSmooth(in vec4 v, in ivec4 index, in vec4 weight)
{
	// The vector to be returned
	vec4 result = vec4(0.0);
	
	// Key: skin matrix of joint (S_j) || i == index || weight of index (w_i)
	
	// multiplying the vertex by the influence matrix first, and doing the weighted average after
	// order of operations is key here
	// 	(pre-multiplied, candy-wrapping effect) 
	// 		v' = sum(w[i] * S_j[i] * v)
	
	result += weight[0] * skinRigid(v, index[0]);
	result += weight[1] * skinRigid(v, index[1]);
	result += weight[2] * skinRigid(v, index[2]);
	result += weight[3] * skinRigid(v, index[3]);
	
	return result;
}

// Implement this ourselves
mat4 dq2mat(in dquat dq)
{
	mat4 result = mat4(
		1.0
	);
	
	return result;
}

// Smooth skinning featuring Dual Quaternions
mat4 skinSmoothDQ(in ivec4 index, in vec4 weight)
{	
	// The thing we're summing
	dquat dq = dquat(0.0);

	// Key: skin matrix of joint (S_j) || i == index || weight of index (w_i) || dual quat (Q_j)
	
	//	(not pre-mult, no candy-wrapping effect (it's DualQuaternion TIME!!!))
	// 		Q' = (sum(w[i] * Q_j[i])
	//		v' = conv(norm(Q')) * v
	
	dq += weight[0] * uSkinDQ[index[0]];
	dq += weight[1] * uSkinDQ[index[1]];
	dq += weight[2] * uSkinDQ[index[2]];
	dq += weight[3] * uSkinDQ[index[3]];
	
	return dq2mat(dq / length(dq[0]));
}

void main()
{
	// DUMMY OUTPUT: directly assign input position to output position
//	gl_Position = aPosition;

	//vTangentBasis_view = uMV_nrm * mat4(aTangent, aBiftangent, aNormal, vec4(0.0));
	
	mat4 skinMat = skinSmoothDQ(aSkinIndex, aSkinWeight);
	
	vTangentBasis_view = uMV_nrm * skinMat * mat4(
	// skinSmooth(vec4(aTangent.xyz, 0.0), aSkinIndex, aSkinWeight), 
	// skinSmooth(vec4(aBitangent.xyz, 0.0), aSkinIndex, aSkinWeight), 
	// skinSmooth(vec4(aNormal.xyz, 0.0), aSkinIndex, aSkinWeight), 
		vec4(aTangent.xyz, 0.0), 
		vec4(aBitangent.xyz, 0.0), 
		vec4(aNormal.xyz, 0.0), 
	vec4(0.0));
	
	//vTangentBasis_view[3] = uMV * aPosition;
	// vTangentBasis_view[3] = uMV * skinSmooth(aPosition, aSkinIndex, aSkinWeight);
	vTangentBasis_view[3] = uMV * skinMat * aPosition;
	gl_Position = uP * vTangentBasis_view[3];
	
	vTexcoord_atlas = uAtlas * aTexcoord;

	vVertexID = gl_VertexID;
	vInstanceID = gl_InstanceID;
}
