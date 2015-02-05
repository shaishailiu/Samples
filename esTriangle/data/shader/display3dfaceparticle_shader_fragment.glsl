precision mediump float;

uniform sampler2D tex0;

uniform vec2 uv;

uniform vec4 color;

varying vec2 texcoord0;

void main()
{
  vec2 t2 = texcoord0 + uv;

  t2.y = 1.0 - t2.y;

  vec4 op = texture2D(tex0, t2.xy) * color;

  op.xyz = op.xyz * op.w;

  gl_FragColor = op;

 //gl_FragColor = vec4(1,0,0,1);
}