precision mediump float;

uniform sampler2D tex0;

varying vec4 v_color;
varying vec4 texcoord0;

void main()
{
  //gl_FragColor = v_color;
  gl_FragColor = texture2D(tex0, texcoord0.xy);
}