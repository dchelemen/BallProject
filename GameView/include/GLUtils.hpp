#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#include <GL/glew.h>
#include "Logger/include/GameLogger.h"

//Based on http://www.opengl-tutorial.org/
GLuint loadShader( GLenum aShaderType, bool aIsVertex = true )
{
	CGameLogger logger( "loadShader" );

	std::string shaderType = aIsVertex ? "vertex" : "fragment";
	// get shader id
	GLuint loadedShader = glCreateShader( aShaderType );
	if ( loadedShader == 0 )
	{
		logger.logError( "Error at " + std::string( shaderType ) + " shader initializing (glCreateShader)!" );
		return 0;
	}
	
	// load Shader
	
	const std::string vertex =
	{
		#include "GameView\resources\myVert.vert"
	};

	const std::string fragment =
	{
		#include "GameView\resources\myFrag.frag"
	};

	const char* sourcePointer = aIsVertex ? vertex.c_str() : fragment.c_str();
	glShaderSource( loadedShader, 1, &sourcePointer, NULL );

	glCompileShader( loadedShader );

	GLint result = GL_FALSE;
	int infoLogLength;

	glGetShaderiv(loadedShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(loadedShader, GL_INFO_LOG_LENGTH, &infoLogLength);

	if ( GL_FALSE == result )
	{
		std::vector<char> VertexShaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(loadedShader, infoLogLength, NULL, &VertexShaderErrorMessage[0]);

		std::cerr << &VertexShaderErrorMessage[0];
	}

	return loadedShader;
}
