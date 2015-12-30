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

