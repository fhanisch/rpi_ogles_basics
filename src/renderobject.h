//renderobject.h
#include "ogl.h"
#include "shader.h"
#include "matrix.h"

typedef int (*LoadObjShader)(void*);
typedef int (*CreateObjShader)(void*);
typedef int (*CreateObjShaderProgram)(void*);
typedef void (*DrawObj)(void*);
typedef void (*GeoCross)(void*);
typedef void (*GeoTriangle)(void*);
typedef void (*GeoRectangle)(void*);
typedef void (*CreateVBO)(void*);
typedef void (*CreateIBO)(void*);
typedef void (*CreateTCO)(void*);
typedef int (*LoadTexture)(void*);
typedef void (*BindTexture)(void*);
typedef void (*GetLetters)(void*);
typedef void (*SetText)(void*,char*);

enum drawObjMode {DRAW_OBJ, DRAW_OBJ_VBO, DRAW_OBJ_VBO_TEX};

typedef struct
{
	GLfloat x,y,z;
} Vertex;

typedef struct
{
	GLfloat x,y;
} TexCoords;

typedef struct
{
	GLfloat r,g,b,a;
} Color;

typedef struct
{
	//Member
	char *name;
	char *vertexShaderFileName;
	char *fragmentShaderFileName;
	char *textureFilename;
	GLchar *vertexShaderStr;
	GLchar *fragmentShaderStr;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	Vertex *v;
	uint vLen;
	uint vSize;
	GLushort *indices;
	uint indLen;
	uint indSize;
	TexCoords *texCoords;
	uint texCoordsSize;
	GLuint vboID;
	GLuint iboID;
	GLuint tcoID;
	GLuint texID;
	GLenum RENDER_MODE;
	Color color;
	GLubyte *texture;
	GLubyte *letter[100];
	GLubyte *text;
	int xSize, ySize;
	GLfloat rotZ;
	Vector3 vTrans;
	Vector3 vScale;
	Matrix4 mProj;
	
	//Methoden
	LoadObjShader pfcnLoadObjShader;
	CreateObjShader pfcnCreateObjShader;
	CreateObjShaderProgram pfcnCreateObjShaderProgram;
	DrawObj pfcnDrawObj;
	GeoCross pfcnGeoCross;
	GeoTriangle pfcnGeoTriangle;
	GeoRectangle pfcnGeoRectangle;
	CreateVBO pfcnCreateVBO;
	CreateIBO pfcnCreateIBO;
	CreateTCO pfcnCreateTCO;
	LoadTexture pfcnLoadTexture;
	BindTexture pfcnBindTexture;
	GetLetters pfcnGetLetters;
	SetText pfcnSetText;
} RenderObject;

RenderObject renderobject(char *name, char *vertexShaderFileName, char *fragmentShaderFileName,  char *textureFilename, Color c, int drawObjMode);
int loadObjShader(void *obj);
int createObjShader(void *obj);
int createObjShaderProgram(void *obj);
void drawObj(void *obj);
void drawObjVBO(void *obj);
void drawObjVBOTex(void *obj);
void geoCross(void *obj);
void geoTriangle(void *obj);
void geoRectangle(void *obj);
void createVBO(void *obj);
void createIBO(void *obj);
void createTCO(void *obj);
int loadTexture(void *obj);
void bindTexture(void *obj);
void getLetters (void *obj);
void setText(void *obj, char *str);
