//=================================================================================================================================
//
// Author: Maurice Ribble
//         3D Application Research Group
//         ATI Research, Inc.
//
// Simple fragment shaders to test my simple ES triangle app.
//
//=================================================================================================================================
// $Id:  $ 
// 
// Last check-in:  $DateTime:  $ 
// Last edited by: $Author:  $
//=================================================================================================================================
//   (C) ATI Research, Inc. 2006 All rights reserved. 
//=================================================================================================================================

precision mediump float;

uniform sampler2D tex0;

varying vec4 texcoord0;
varying float normallight;

vec4 testTexture()
{
	vec4 color = texture2D(tex0, texcoord0.xy);
	color.xyz = color.xyz * normallight;
	return color;
}


void main()
{    
   gl_FragColor = testTexture();
}
