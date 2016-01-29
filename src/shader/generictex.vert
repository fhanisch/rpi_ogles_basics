//vertex shader

uniform mat4 mProj;
uniform vec3 vTrans;
uniform vec3 vScale;
attribute vec3 vertex;
attribute vec2 texCoordIn;
varying vec2 texCoordOut;

void main()
{
	mat4 mTrans = mat4(1.0);
	mat4 mScale = mat4(1.0);

	mTrans[3].xyz = vTrans;
	
	mScale[0].x = vScale.x;
	mScale[1].y = vScale.y;
	mScale[2].z = vScale.z;

	gl_Position = mProj*mTrans*mScale*vec4(vertex,1.0);
	texCoordOut = texCoordIn;
}

