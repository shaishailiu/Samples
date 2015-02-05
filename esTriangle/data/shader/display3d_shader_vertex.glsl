attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec4 texcoord;

uniform mat4 modelView;

uniform mat4 mas[10];

varying vec4 v_color;
varying vec4 texcoord0;



void main()
{
	//v_color = vColor;
	vec4 t1 = mas[int(vColor.x)] * vPosition;
	gl_Position = t1;
	texcoord0 = texcoord;
}