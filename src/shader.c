//shader.c
#include <stdlib.h>
#include <stdio.h>
#include "shader.h"


int loadShader(GLchar **shaderStr, char *fileName)
{
	uint filesize;
	uint readElements;
	FILE *file = fopen(fileName,"r");

	fseek(file,0,SEEK_END);
	filesize=ftell(file);
	rewind(file);
	printf("File Size: %i\n",filesize);
	*shaderStr = malloc(filesize+1);
	readElements = fread(*shaderStr,filesize,1,file);
	printf("Elements read: %i\n",readElements);
	(*shaderStr)[filesize]='\0';
	fclose(file);

	return 0;
}

GLuint createShader(GLenum shaderType, GLchar *shaderStr)
{
	GLuint shader;
	GLint compiled;
	GLint infoLen = 0;
	char *infoLog;

	shader = glCreateShader(shaderType);
	glShaderSource(shader,1,(const GLchar**)&shaderStr,NULL);
	glCompileShader(shader);
	if(!compiled)
	{
	    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
	    if(infoLen > 1)
		{
		    infoLog = malloc(sizeof(char) * infoLen);
		    glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
		    fprintf(stderr, "Error compiling shader:\n%s\n", infoLog);
		    free(infoLog);
		}
	    glDeleteShader(shader);
	    return 0;
	}

	return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}
