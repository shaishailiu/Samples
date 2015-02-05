precision mediump float;

uniform sampler2D tex0;

varying vec4 v_color;
varying vec2 texcoord0;

void main()
{
  //gl_FragColor = v_color;
  gl_FragColor = texture2D(tex0, texcoord0.xy);
  //gl_FragColor = vec4(1,0,0,1);
}