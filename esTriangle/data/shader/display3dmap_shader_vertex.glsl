attribute vec4 vPosition;
attribute vec4 texcoord;

uniform vec4 wh;
varying vec4 texcoord0;

void main()
{
	vec4 t1 = vPosition;
	t1.xy = t1.xy * wh.xy;
	t1.xy = t1.xy + wh.zw;
	gl_Position = t1;
	texcoord0 = texcoord;
}