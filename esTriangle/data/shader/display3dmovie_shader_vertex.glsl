attribute vec4 v1;
attribute vec4 v2;
attribute vec4 v3;
attribute vec4 v4;

attribute vec4 boneId;
attribute vec4 boneWeight;

attribute vec2 texcoord;

uniform mat4 modelView;
uniform mat4 camera;

uniform mat4 bone[27];

varying vec2 texcoord0;

void main()
{

	vec4 attribPos = bone[int(boneId[0])] * v1 * boneWeight[0];
	attribPos += bone[int(boneId[1])] * v2 * boneWeight[1];
	attribPos += bone[int(boneId[2])] * v3 * boneWeight[2];
	attribPos += bone[int(boneId[3])] * v4 * boneWeight[3];

	gl_Position = camera * (modelView * attribPos);

	texcoord0 = texcoord;

}