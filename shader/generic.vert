//vertex shader

uniform mat4 mProj;
uniform vec3 vScale;
uniform float rotZ;
attribute vec3 vertex;

void main()
{	
	mat4 mScale = mat4(1.0);
	mat4 mTrans = mat4(1.0);
	mat4 mRot = mat4(1.0);

	mScale[0].x = vScale.x;
	mScale[1].y = vScale.y;
	mScale[2].z = vScale.z;
	mTrans[3]=vec4(0.5,0.0,0.0,1.0);
	mRot[0].x=cos(rotZ);
	mRot[1].x=-sin(rotZ);
	mRot[0].y=sin(rotZ);
	mRot[1].y=cos(rotZ);
	
	gl_Position = mProj*mTrans*mRot*mScale*vec4(vertex,1.0);
}
