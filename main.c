//main.c
#include <stdio.h>
#include <stdbool.h>
#include "ogl.h"
#include "bcm_host.h"
#include "types.h"
#include "view.h"
#include "ui/key.h"


typedef struct {
   DISPMANX_ELEMENT_HANDLE_T element;
   int width;
   int height;
 } EGL_DISPMANX_WINDOW_T;

typedef struct
{
	uint32_t screen_width;
	uint32_t screen_height;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
}  CUBE_STATE_T;

CUBE_STATE_T state;

void initOpenGL(CUBE_STATE_T *p_state)
{
	int32_t success;
	EGLBoolean result;
	EGLint num_config;
	EGLConfig config;
	static EGL_DISPMANX_WINDOW_T nativewindow;

	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;

	static const EGLint attribute_list[] =
	{
	    EGL_RED_SIZE, 8,
	    EGL_GREEN_SIZE, 8,
	    EGL_BLUE_SIZE, 8,
	    EGL_ALPHA_SIZE, 8,
	    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	    EGL_NONE
	};

    	static const EGLint context_attributes[] =
	{
	    EGL_CONTEXT_CLIENT_VERSION, 2,
	    EGL_NONE
	};

	bcm_host_init();
	p_state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);	
	result = eglInitialize(p_state->display, NULL, NULL);
	result = eglChooseConfig(p_state->display, attribute_list, &config, 1, &num_config);		
	result = eglBindAPI(EGL_OPENGL_ES_API);	
	p_state->context = eglCreateContext(p_state->display, config, EGL_NO_CONTEXT,context_attributes);	
	success = graphics_get_display_size(0, &p_state->screen_width,&p_state->screen_height);	
	p_state->screen_width = 1920;
	p_state->screen_height = 1080;
	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width = p_state->screen_width;
	dst_rect.height = p_state->screen_height;
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = p_state->screen_width << 16;
	src_rect.height = p_state->screen_height << 16;        
	dispman_display = vc_dispmanx_display_open(0);
	dispman_update = vc_dispmanx_update_start(0);
	dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display,0, &dst_rect, 0,&src_rect, DISPMANX_PROTECTION_NONE, 0, 0, 0);
	nativewindow.element = dispman_element;
	nativewindow.width = p_state->screen_width;
	nativewindow.height = p_state->screen_height;
	vc_dispmanx_update_submit_sync( dispman_update );
	p_state->surface = eglCreateWindowSurface( p_state->display, config, (EGLNativeWindowType)&nativewindow, NULL );		
	result = eglMakeCurrent(p_state->display, p_state->surface, p_state->surface, p_state->context);	
}

int main(int val, char **str)
{
	int key;
	View myView;

	const GLubyte *vendor		= glGetString(GL_VENDOR);
	const GLubyte *renderer		= glGetString(GL_RENDERER);
	const GLubyte *oglVersion	= glGetString(GL_VERSION);
	const GLubyte *glslVersion	= glGetString(GL_SHADING_LANGUAGE_VERSION);

	printf("Programm: %s\n",str[0]+2);
	printf("Vendor: %s\n", vendor);
	printf("Renderer: %s\n",renderer);
	printf("OpenGL Version: %s\n",oglVersion);
	printf("GLSL Version: %s\n", glslVersion);

	initOpenGL(&state);
	myView = view("MyView",str[1]);

	glClearColor(0.0f,0.0f,0.0f,1.0f);
	//glClearDepthf(1.0f);
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//Transparenz
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	while(key!=27)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		myView.pfcnDrawView(&myView);
		eglSwapBuffers(state.display, state.surface);
		myView.obj[0].rotZ+=0.01;
		
		if (keyPressed(&key)) printf("Taste: %i\n",key);	
	}	
	keyboardReset();

	return 0;
}
