precision mediump float;

uniform sampler2D tex0;
uniform sampler2D tex1;

//uniform vec2 uv;

//uniform vec4 color;

varying vec4 texcoord0;
varying vec4 texcoord1;

void main()
{
  //vec4 t2 = texcoord0;
  //t2.y = 1.0 - t2.y;
  //vec4 t3 = texcoord1;

  vec4 op = texture2D(tex0, texcoord0.xy);
  if(texcoord0.z > 0.0){
	op = op * texture2D(tex1, texcoord1.xy);
  }

  if(texcoord0.w > 0.0){
	op = op * texture2D(tex1, texcoord1.zw);
  }

  //vec4 op = perop;

  //vec4 op = texture2D(tex0, t2.xy) * texture2D(tex1, t3.xy) * texture2D(tex1, t3.zw);

  op.xyz = op.xyz * op.w;

  gl_FragColor = op;

 //gl_FragColor = vec4(1,0,0,1);
}