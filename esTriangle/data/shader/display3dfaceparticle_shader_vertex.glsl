attribute vec4 vPosition;

attribute vec2 texcoord;


uniform mat4 modelView;
uniform mat4 camera;

varying vec2 texcoord0;

void main()
{

	gl_Position = camera * modelView * vPosition;

	texcoord0 = texcoord;

}