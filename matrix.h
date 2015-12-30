//matrix.h

typedef struct
{
	float x,y,z;
} Vector3;

typedef struct
{
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
} Matrix4;

Vector3 vec3(float x, float y, float z);
Matrix4 identity();
Matrix4 transpose(Matrix4 mIn);
