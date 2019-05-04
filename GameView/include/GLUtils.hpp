#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#include <GL/glew.h>
#include "Logger/include/GameLogger.h"
/* 

Az http://www.opengl-tutorial.org/ oldal alapján.

*/
GLuint loadShader( GLenum _shaderType, const char* _fileName )
{
	std::string funcName( "loadShader" );
	CGameLogger logger( funcName.c_str(), funcName.length() );
	// shader azonosito letrehozasa
	GLuint loadedShader = glCreateShader( _shaderType );

	// ha nem sikerult hibauzenet es -1 visszaadasa
	if ( loadedShader == 0 )
	{
		std::string message = "Error at " + std::string( _fileName ) + " shader initializing (glCreateShader)!";
		logger.logError( message.c_str() );
		return 0;
	}
	
	// shaderkod betoltese _fileName fajlbol
	std::string shaderCode = "";
	wchar_t buffer[ MAX_PATH ];
	GetModuleFileName( NULL, buffer, MAX_PATH );
	// _fileName megnyitasa
	std::ifstream shaderStream( _fileName );

	if ( !shaderStream.is_open() )
	{
		std::string message = "Error at " + std::string( _fileName ) + " loading shader (glCreateShader)!\n";
		logger.logError( message.c_str() );
		return 0;
	}

	// file tartalmanak betoltese a shaderCode string-be
	std::string line = "";
	while ( std::getline(shaderStream, line) )
	{
		shaderCode += line + "\n";
	}

	shaderStream.close();

	// fajlbol betoltott kod hozzarendelese a shader-hez
	const char* sourcePointer = shaderCode.c_str();
	glShaderSource( loadedShader, 1, &sourcePointer, NULL );

	// shader leforditasa
	glCompileShader( loadedShader );

	// ellenorizzuk, h minden rendben van-e
	GLint result = GL_FALSE;
    int infoLogLength;

	// forditas statuszanak lekerdezese
	glGetShaderiv(loadedShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(loadedShader, GL_INFO_LOG_LENGTH, &infoLogLength);

	if ( GL_FALSE == result )
	{
		// hibauzenet elkerese es kiirasa
		std::vector<char> VertexShaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(loadedShader, infoLogLength, NULL, &VertexShaderErrorMessage[0]);

		std::cerr << &VertexShaderErrorMessage[0];
	}

	return loadedShader;
}
