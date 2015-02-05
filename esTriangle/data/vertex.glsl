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
attribute vec4 color;
attribute vec4 texcoord;

uniform mat4 mvp;
varying vec4 texcoord0;
varying vec4 outcolor;

void main()
{
    gl_Position = mvp * position;
    outcolor = color;
    texcoord0 = texcoord;
}
