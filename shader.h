//shader.h
#include "ogl.h"
#include "types.h"

int loadShader(GLchar **shaderStr, char *fileName);
GLuint createShader(GLenum shaderType, GLchar *shaderStr);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
