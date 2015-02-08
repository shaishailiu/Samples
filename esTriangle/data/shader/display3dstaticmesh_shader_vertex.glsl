//=================================================================================================================================
//
// Author: Maurice Ribble
//         3D Application Research Group
//         ATI Research, Inc.
//
// Simple vertex shaders to test my simple ES triangle app.
//
//=================================================================================================================================
// $Id:  $ 
// 
// Last check-in:  $DateTime:  $ 
// Last edited by: $Author:  $
//=================================================================================================================================
//   (C) ATI Research, Inc. 2006 All rights reserved. 
//=================================================================================================================================

attribute vec4 position;
attribute vec4 normal;
attribute vec4 texcoord;

uniform mat4 modelView;
uniform mat4 rotationMat;
uniform mat4 camera;
uniform vec4 light;

varying vec4 texcoord0;
varying float normallight;

void main()
{
    gl_Position = camera * (modelView * position);

	vec4 nor = normalize(rotationMat * normal);

	normallight = dot(nor,light);
	
	//normallight += 1.0;

	//normallight *= 2.0;

    texcoord0 = texcoord;
}
