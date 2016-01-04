//bmp_rw.c
//Erstellt: 03.01.2016

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../types.h"
#include "bmp_rw.h"

typedef struct
{
	byte r,g,b;
} Color;

Color getColor(byte r, byte g, byte b)
{
	Color c={r,g,b};
	return c;
}

void setpixel(byte *bild, int xSize, int x, int y, Color c)
{	
	uint pixelPtr;

	pixelPtr = (y*xSize+x)*3;
	bild[pixelPtr] = c.r;
	bild[pixelPtr+1] = c.g;
	bild[pixelPtr+2] = c.b;
}

void drawHorzLine(byte *bild, int xStart, int xEnd, int y)
{
	int i;
	for (i=0;i<xEnd;i++)
		setpixel(bild, 400, xStart+i, y, getColor(255,0,0));
}

void drawVertLine(byte *bild, int x, int yStart, int yEnd)
{
	int i;
	for (i=0;i<yEnd;i++)
		setpixel(bild, 400, x, yStart+i, getColor(255,0,0));
}

void drawSine(byte *bild)
{
	int i;
	double x=0;
	double y;
	double pi=3.14159;
	int ix;
	int iy;

	for(i=0;i<1000;i++)
	{
		x+=2*pi/1000;
		y=sin(x);
		ix=63.6*x;
		iy=100*y+200;
		setpixel(bild, 400, ix, iy, getColor(0,255,0));
	}
		
}

void drawCircle(byte *bild)
{
	int i;
	double phi=0;
	double x;
	double y;
	double pi=3.14159;
	int ix;
	int iy;

	for(i=0;i<1000;i++)
	{
		phi+=2*pi/1000;
		x=cos(phi);
		y=sin(phi);		
		ix=100*x+200;
		iy=100*y+200;
		setpixel(bild, 400, ix, iy, getColor(0,0,255));
	}
}

int writeBMP(char *filename)
{
	BMP_HEADER BMPheader;
	byte *bild;
	uint bildSize;
	FILE *file;
		
	BMPheader.fileSize=54+400*400*3;
	BMPheader.reserved=0;
	BMPheader.offset=54;
	BMPheader.infoHeaderSize=40;
	BMPheader.xSize=400;
	BMPheader.ySize=400;
	BMPheader.planes=1;
	BMPheader.farbtiefe=24;
	BMPheader.compression=0;
	BMPheader.bildSize = 400*400*3;
	BMPheader.XPelsPerMeter=0;
	BMPheader.YPelsPerMeter=0;
	BMPheader.ClrUsed=0;
	BMPheader.ClrImportant=0;
	printf("Size of BMP-Header: %i\n",sizeof(BMP_HEADER));

	bild = malloc(BMPheader.bildSize);
	memset(bild,255,BMPheader.bildSize);
	drawHorzLine(bild, 0, 400, 200);
	drawVertLine(bild, 200, 0, 400);
	drawSine(bild);
	drawCircle(bild);
	
	file = fopen(filename,"w");
	fwrite("BM",2,1,file);
	fwrite(&BMPheader,sizeof(BMP_HEADER),1,file);
	fwrite(bild,BMPheader.bildSize,1,file);
	fclose(file);
	
	return 0;
}
