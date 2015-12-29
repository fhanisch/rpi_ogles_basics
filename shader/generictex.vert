//vertex shader

uniform mat4 mProj;
uniform vec3 vScale;
attribute vec3 vertex;
attribute vec2 texCoordIn;
varying vec2 texCoordOut;

void main()
{
	mat4 mScale = mat4(1.0);

	mScale[0].x = vScale.x;
	mScale[1].y = vScale.y;
	mScale[2].z = vScale.z;

	gl_Position = mProj*mScale*vec4(vertex,1.0);
	texCoordOut = texCoordIn;
}

