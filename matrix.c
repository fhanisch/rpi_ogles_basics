//matrix.c
//Erstellt: 21.12.2015
#include <stdio.h>
#include <string.h>
#include "matrix.h"

Vector3 vec3(float x, float y, float z)
{
	Vector3 vOut={x,y,z};
	return vOut;
}

Matrix4 identity()
{
	Matrix4 I;
	memset(&I,0,sizeof(Matrix4));
	I.m11 = 1.0f;
	I.m22 = 1.0f;
	I.m33 = 1.0f;
	I.m44 = 1.0f;
	printf("Size of Matrix4: %i\n", sizeof(Matrix4));

	return I;
}

Matrix4 setFrustum(float r, float t, float n, float f)
{
	Matrix4 F;
	memset(&F,0,sizeof(Matrix4));

	F.m11=n/r;	F.m12=0;	F.m13=0;		F.m14=0;
	F.m21=0;	F.m22=n/t;	F.m23=0;		F.m24=0;
	F.m31=0;	F.m32=0;	F.m33=-(f+n)/(f-n);	F.m34=-2*f*n/(f-n);
	F.m41=0;	F.m42=0;	F.m43=-1;		F.m44=0;

	return F;
}

Matrix4 transpose(Matrix4 mIn)
{
	Matrix4 mOut;
	int i,j;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			((float*)&mOut)[i+4*j] = ((float*)&mIn)[j+4*i];
		}
	}

	return mOut;
}

