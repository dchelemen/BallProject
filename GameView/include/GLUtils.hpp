#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#include <GL/glew.h>
#include "Logger/include/GameLogger.h"

//Based on http://www.opengl-tutorial.org/
GLuint loadShader( GLenum aShaderType, const char* aFileName )
{
	CGameLogger logger( "loadShader" );

	// get shader id
	GLuint loadedShader = glCreateShader( aShaderType );
	if ( loadedShader == 0 )
	{
		logger.logError( "Error at " + std::string( aFileName ) + " shader initializing (glCreateShader)!" );
		return 0;
	}
	
	// load Shader
	std::string shaderCode = "";
	wchar_t buffer[ MAX_PATH ];
	GetModuleFileName( NULL, buffer, MAX_PATH );

	std::ifstream shaderStream( aFileName );
	if ( !shaderStream.is_open() )
	{
		logger.logError( "Error at " + std::string( aFileName ) + " loading shader (glCreateShader)!\n" );
		return 0;
	}

	std::string line = "";
	while ( std::getline( shaderStream, line ) )
	{
		shaderCode += line + "\n";
	}
	shaderStream.close();

	const char* sourcePointer = shaderCode.c_str();
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
