attribute vec4 vPosition;
uniform mat4 camera;
void main()
{
	vec4 t1 = camera * vPosition;
	gl_Position = t1;
}