//fragment shader
uniform vec4 color;
uniform sampler2D samp;
varying vec2 texCoordOut;

void main()
{
	//gl_FragColor = color;
	vec4 tex = texture2D(samp, texCoordOut);
	if (tex.g<0.8)
		gl_FragColor = vec4(0.3, 0.3, 0.3, 1.0);
	else
		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.25);
}
