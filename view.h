//view.h
#include "renderobject.h"

typedef void (*DrawView)(void*);

typedef struct
{
	char *name;
	char *hintergrundbild;
	RenderObject obj[5];
	DrawView pfcnDrawView;
} View;

View view(char *name, char *hintergrund);
void drawView(void *view);
void createObj(RenderObject *obj);
void createObj2(RenderObject *obj);
void setImage2Texture(GLubyte *tex1, int xSize1, int ySize1, GLubyte *tex2, int xSize2, int ySize2);
void testCharMap(GLubyte *tex, int xSize);
void setPixel(GLubyte *tex, int xSize, int x, int y);
