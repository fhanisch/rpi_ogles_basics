//view.c
#include <stdio.h>
#include <string.h>
#include "view.h"

#define RED	{1.0f, 0.0f, 0.0f, 1.0f}
#define GREEN	{0.0f, 1.0f, 0.0f, 1.0f}
#define BLUE	{0.0f, 0.0f, 1.0f, 1.0f}
#define YELLOW	{1.0f, 1.0f, 0.0f, 1.0f}

View view(char *name, char *hintergrund)
{
	Color red = RED;
	Color green = GREEN;
	Color blue = BLUE;
	Color yellow = YELLOW;
	View view;
	view.name = name;
	view.hintergrundbild = hintergrund;
	view.pfcnDrawView = drawView;
	RenderObject triangle = renderobject("Triangle","shader/generic.vert","shader/generic.frag", NULL, yellow);
	RenderObject rectangle = renderobject("Rectangle","shader/generictex.vert","shader/generictex.frag", view.hintergrundbild, blue);
	RenderObject square = renderobject("Square","shader/generic.vert","shader/generic.frag", NULL, red);
	RenderObject textfield = renderobject ("Textfield","shader/generictex.vert","shader/generictext.frag","res/font3.bmp",red);
	triangle.pfcnGeoTriangle(&triangle);
	rectangle.pfcnGeoRectangle(&rectangle);
	square.pfcnGeoRectangle(&square);
	textfield.pfcnGeoRectangle(&textfield);
	createObj(&triangle);
	createObj(&rectangle);
	createObj(&square);
	createObj(&textfield);
	triangle.mProj.m11 = 1080.0f/1920.0f;
	triangle.mProj = transpose(triangle.mProj);
	triangle.vScale = vec3(0.3f,0.3f,1.0f);
	square.mProj.m11 = 1080.0f/1920.0f;
	square.mProj = transpose(square.mProj);
	square.vScale = vec3(0.3f,0.3f,1.0f);
	rectangle.pfcnLoadTexture(&rectangle);
	
	rectangle.pfcnCreateTCO(&rectangle);
	textfield.pfcnLoadTexture(&textfield);
	textfield.pfcnGetLetters(&textfield);
	textfield.pfcnSetText(&textfield, "HALLO");
	//textfield.texture = textfield.letter[10];
	//textfield.texture = textfield.text;
	//textfield.xSize = 2*30;
	//textfield.ySize = 40;	
	textfield.pfcnBindTexture(&textfield);
	textfield.pfcnCreateTCO(&textfield);
	textfield.mProj.m11 = 1080.0f/1920.0f;
	textfield.mProj = transpose(textfield.mProj);
	textfield.vScale = vec3(0.25f,0.2f,1.0f);

	/*setImage2Texture(rectangle.texture,rectangle.xSize,rectangle.ySize,textfield.texture,textfield.xSize,textfield.ySize);*/
	testCharMap(rectangle.texture,rectangle.xSize);
	rectangle.pfcnBindTexture(&rectangle);	

	view.obj[0] = triangle;
	view.obj[1] = rectangle;
	view.obj[2] = square;
	view.obj[3] = textfield;
	return view;
}

void createObj(RenderObject *obj)
{
	obj->pfcnLoadObjShader(obj);
	obj->pfcnCreateObjShader(obj);
	obj->pfcnCreateObjShaderProgram(obj);
	obj->pfcnCreateVBO(obj);
	obj->pfcnCreateIBO(obj);
	obj->mProj = identity();
	obj->vScale=vec3(1.0f,1.0f,1.0f);
}

void drawView(void *view)
{
	View *vw = view;
	vw->obj[1].pfcnDrawObj(&vw->obj[1]);
	vw->obj[2].pfcnDrawObj(&vw->obj[2]);
	vw->obj[0].pfcnDrawObj(&vw->obj[0]);
	vw->obj[3].pfcnDrawObj(&vw->obj[3]);
}

void setImage2Texture(GLubyte *tex1, int xSize1, int ySize1, GLubyte *tex2, int xSize2, int ySize2)
{
	uint x,y;
	uint tex1Ptr;
	uint tex2Ptr=0;
	GLubyte value=250;

	for (y=0;y<ySize2;y++)
	{

		tex1Ptr=y*xSize1*4;		
		for (x=0;x<xSize2;x++)
		{
			if (tex2[tex2Ptr]<value && tex2[tex2Ptr+1]<value && tex2[tex2Ptr+2]<value) 
			{
				setPixel(tex1,xSize1,200+x,200+y);
			}
			tex1Ptr+=4;
			tex2Ptr+=4;
		}
	}
}

void testCharMap(GLubyte *tex, int xSize)
{
	FILE *file;
	byte charMap[128*16];
	byte test=1;
	uint character, zeile, bit;	
	uint charPtr=0;

	file = fopen("res/font.bin","rb");
	printf("Size Of CharMap: %i\n",sizeof(charMap));
	fread(charMap,sizeof(charMap),1,file);
	fclose(file);

	for (character=0;character<128;character++)
	{
		for (zeile=0;zeile<16;zeile++)
		{
			for (bit=0;bit<8;bit++)
			{
				if (charMap[charPtr]>>bit & test) setPixel(tex,xSize,200+bit+character*8,200-zeile);
			}
			charPtr++;
		}		
	}
}

void setPixel(GLubyte *tex, int xSize, int x, int y)
{
	GLubyte value = 255;
	uint pixelPtr;

	pixelPtr = (y*xSize+x)*4;
	tex[pixelPtr] = 0;
	tex[pixelPtr+1] = value;
	tex[pixelPtr+2] = 0;
}
