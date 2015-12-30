//renderobject.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderobject.h"

RenderObject renderobject(char *name, char *vertexShaderFileName, char *fragmentShaderFileName, char *textureFilename, Color c)
{
	RenderObject obj;
	obj.name=name;
	obj.vertexShaderFileName=vertexShaderFileName;
	obj.fragmentShaderFileName=fragmentShaderFileName;
	obj.textureFilename = textureFilename;
	obj.color = c;
	obj.rotZ=0.0f;
	obj.pfcnLoadObjShader=loadObjShader;
	obj.pfcnCreateObjShader=createObjShader;
	obj.pfcnCreateObjShaderProgram = createObjShaderProgram;
	if (textureFilename==NULL) obj.pfcnDrawObj = drawObjVBO; else obj.pfcnDrawObj = drawObjVBOTex;
	obj.pfcnGeoTriangle = geoTriangle;
	obj.pfcnGeoRectangle = geoRectangle;
	obj.pfcnCreateVBO = createVBO;
	obj.pfcnCreateIBO = createIBO;
	obj.pfcnCreateTCO = createTCO;
	obj.pfcnLoadTexture = loadTexture;
	obj.pfcnBindTexture = bindTexture;
	obj.pfcnGetLetters = getLetters;
	obj.pfcnSetText = setText;
	return obj;
}

int loadObjShader(void *obj)
{
	RenderObject *o = obj;
	loadShader(&o->vertexShaderStr, o->vertexShaderFileName);
	loadShader(&o->fragmentShaderStr, o->fragmentShaderFileName);
	return 0;
}

int createObjShader(void *obj)
{
	RenderObject *o = obj;
	o->vertexShader = createShader(GL_VERTEX_SHADER, o->vertexShaderStr);
	o->fragmentShader = createShader(GL_FRAGMENT_SHADER, o->fragmentShaderStr);
	return 0;
}

int createObjShaderProgram(void *obj)
{
	RenderObject *o = obj;
	o->shaderProgram = createShaderProgram(o->vertexShader, o->fragmentShader);
	return 0;
}

void drawObjVBO(void *obj)
{
	//GLenum err;
	RenderObject *o = obj;
	GLint mProjHandle = glGetUniformLocation(o->shaderProgram,"mProj");
	GLint vScaleHandle = glGetUniformLocation(o->shaderProgram,"vScale");
	GLint rotZHandle = glGetUniformLocation(o->shaderProgram,"rotZ");
	GLint colorHandle = glGetUniformLocation(o->shaderProgram,"color");	
	GLuint vertexHandle = glGetAttribLocation(o->shaderProgram,"vertex");	

	glUseProgram(o->shaderProgram);

	glEnableVertexAttribArray(vertexHandle);

	glUniformMatrix4fv(mProjHandle,1,GL_FALSE,(GLfloat*)&o->mProj);
	glUniform3fv(vScaleHandle,1,(GLfloat*)&o->vScale);
	glUniform1f(rotZHandle, o->rotZ);
	glUniform4fv(colorHandle,1, (GLfloat*)&o->color);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->iboID);

	glBindBuffer(GL_ARRAY_BUFFER, o->vboID);
	//glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, o->v);
	glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glDrawArrays(GL_TRIANGLES,0,3);
	//glDrawElements(GL_TRIANGLES, o->indLen, GL_UNSIGNED_SHORT, o->indices);
	glDrawElements(o->RENDER_MODE, o->indLen, GL_UNSIGNED_SHORT, 0);
	//err = glGetError();
	//printf("Error: %i    %i\n",err,GL_INVALID_ENUM);

	glDisableVertexAttribArray(vertexHandle);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void drawObjVBOTex(void *obj)
{
	RenderObject *o = obj;
	GLint mProjHandle = glGetUniformLocation(o->shaderProgram,"mProj");
	GLint vScaleHandle = glGetUniformLocation(o->shaderProgram,"vScale");
	GLint colorHandle = glGetUniformLocation(o->shaderProgram,"color");
	GLint textureHandle = glGetUniformLocation(o->shaderProgram,"samp");
	GLuint vertexHandle = glGetAttribLocation(o->shaderProgram,"vertex");
	GLuint texCoordHandle = glGetAttribLocation(o->shaderProgram, "texCoordIn");

	glUseProgram(o->shaderProgram);

	glEnableVertexAttribArray(vertexHandle);
	glEnableVertexAttribArray(texCoordHandle);

	glUniformMatrix4fv(mProjHandle,1,GL_FALSE,(GLfloat*)&o->mProj);
	glUniform3fv(vScaleHandle,1,(GLfloat*)&o->vScale);
	glUniform4fv(colorHandle,1,(GLfloat*)&o->color);
	glUniform1i(textureHandle,0);

	glBindTexture(GL_TEXTURE_2D,o->texID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->iboID);

	glBindBuffer(GL_ARRAY_BUFFER, o->vboID);
	glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, o->tcoID);
	glVertexAttribPointer(texCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(o->RENDER_MODE, o->indLen, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(vertexHandle);
	glDisableVertexAttribArray(texCoordHandle);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindTexture(GL_TEXTURE_2D,0);
}

void geoTriangle(void *obj)
{
	RenderObject *o=obj;
	GLfloat v[] = {	0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
		 	1.0f, -1.0f, 0.0f};
	GLushort  indices[] = {0,1,2};
	o->vSize = 3*sizeof(Vertex);
	o->indSize = 3*sizeof(GLushort);
	o->indLen = 3;
	o->v=malloc(o->vSize);
	o->indices = malloc(o->indSize);
	memcpy(o->v,v,o->vSize);
	memcpy(o->indices,indices,o->indSize);
	o->RENDER_MODE = GL_TRIANGLES;
}

void geoRectangle (void *obj)
{
	RenderObject *o=obj;
	GLfloat v[] = {-1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f};
	GLushort  indices[] = {0,1,2,3};
	GLfloat texCoords[] = {	0.0f, 1.0f,
				1.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f};
	o->vSize = 4*sizeof(Vertex);
	o->indSize = 4*sizeof(GLushort);
	o->indLen = 4;
	o->texCoordsSize = 4*sizeof(TexCoords);
	o->v=malloc(o->vSize);
	o->indices = malloc(o->indSize);
	o->texCoords = malloc(o->texCoordsSize);
	memcpy(o->v,v,o->vSize);
	memcpy(o->indices,indices,o->indSize);
	memcpy(o->texCoords, texCoords, o->texCoordsSize);
	o->RENDER_MODE = GL_TRIANGLE_STRIP;
}

void createVBO(void *obj)
{
	RenderObject *o = obj;
	glGenBuffers(1,&o->vboID);
	glBindBuffer(GL_ARRAY_BUFFER, o->vboID);
	glBufferData(GL_ARRAY_BUFFER, o->vSize, o->v, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void createIBO(void *obj)
{
	RenderObject *o=obj;
	glGenBuffers(1,&o->iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, o->indSize, o->indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void createTCO(void *obj)
{
	RenderObject *o = obj;
	glGenBuffers(1,&o->tcoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->tcoID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, o->texCoordsSize, o->texCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int loadTexture (void *obj)
{
	char signature[2];
	unsigned short  farbtiefe;	
	uint offset;
	uint bytePtr=0;
	uint x,y;
	
	RenderObject *o=obj;
	FILE *file = fopen (o->textureFilename,"r");
	fseek(file,0,SEEK_SET);
	fread(signature,2,1,file);
	printf("Bitmap Signature: %c%c\n", signature[0],signature[1]);
	fseek(file,28,SEEK_SET);
	fread(&farbtiefe,2,1,file);
	printf("Farbtiefe: %i\n", farbtiefe);
	fseek(file,18,SEEK_SET);
	fread(&o->xSize,4,1,file);
	fread(&o->ySize,4,1,file);
	printf("Texture size: %i x %i\n", o->xSize, o->ySize);
	o->texture = malloc(o->xSize*o->ySize*4);
	fseek(file,10,SEEK_SET);
	fread(&offset,4,1,file);
	printf("Offset: %i\n",offset);
	fseek(file,offset,SEEK_SET);
	for (y=0;y<o->ySize;y++)
	{
		for (x=0;x<o->xSize;x++)
		{
			fread(o->texture+bytePtr+2,1,1,file);
			fread(o->texture+bytePtr+1,1,1,file);
			fread(o->texture+bytePtr,1,1,file);
			o->texture[bytePtr+3] = 0xff;
			bytePtr+=4;
		}
		fseek(file,o->xSize%4,SEEK_CUR);
	}

	close(file);
	return 0;
}

void bindTexture(void *obj)
{
	RenderObject *o = obj;
	glGenTextures(1, &o->texID);
	glBindTexture(GL_TEXTURE_2D,o->texID);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, o->xSize, o->ySize, 0, GL_RGBA, GL_UNSIGNED_BYTE, o->texture);
	glBindTexture(GL_TEXTURE_2D,0);
}

void getLetters (void *obj)
{
	RenderObject *o = obj;
	uint letterWidth = 30;
	uint letterHeight = 40;
	uint farbtiefe = 4;
	uint i,j,y;
	uint letterPtr;
	uint texPtr;
	for (i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
		{
			letterPtr=0;
			texPtr=(31*o->xSize+36+j*102+i*103*o->xSize)*farbtiefe;
			o->letter[j+i*10]=malloc(letterWidth*letterHeight*farbtiefe);
			for (y=0;y<letterHeight;y++)
			{
				memcpy(o->letter[j+i*10]+letterPtr, o->texture+texPtr, letterWidth*farbtiefe);
				letterPtr+=letterWidth*farbtiefe;
				texPtr+=o->xSize*farbtiefe;
			}
		}
	}
}

void setText(void *obj, char *str)
{
	RenderObject *o = obj;
	uint y;
	uint letterPtr=0;
	uint textPtr=0;
	uint letterIndices[255];
	letterIndices[65] = 63;
	letterIndices[72] = 50;

	o->text=malloc(2*30*40*4);
	for (y=0;y<40;y++)
	{
		memcpy(o->text+textPtr,o->letter[letterIndices[str[0]]]+letterPtr,30*4);
		textPtr+=30*4;
		memcpy(o->text+textPtr,o->letter[letterIndices[str[1]]]+letterPtr,30*4);
		textPtr+=30*4;
		letterPtr+=30*4;
	}
}
