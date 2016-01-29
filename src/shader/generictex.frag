//fragment shader
uniform vec4 color;
uniform sampler2D samp;
varying vec2 texCoordOut;

void main()
{
	//gl_FragColor = color;
	vec4 tex = texture2D(samp, texCoordOut);
	gl_FragColor = vec4(tex.rgb,1.0);
}
