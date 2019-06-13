#include "GameView\include\ShaderPrivate.h"
#include "Logger\include\GameLogger.h"

#include <GL/glew.h>

#include <vector>

CShaderPrivate::CShaderPrivate( CObject* aParent )
	: CObject( aParent )
	, m_ShaderID( 0 )
	, m_GameLogger( new CGameLogger( "CShaderPrivate", this ) )
{
}

CShaderPrivate::~CShaderPrivate()
{
	glDeleteProgram( m_ShaderID );
}

bool CShaderPrivate::initialize( const std::string& aVS, const std::string& aFS, const std::vector< std::string >& aAttributesToBindVect )
{
	GLuint vsID = 0, fsID = 0;
	
	if ( !generateShader( GL_VERTEX_SHADER, &vsID, aVS.c_str() ) )
		return false;

	if ( !generateShader( GL_FRAGMENT_SHADER, &fsID, aFS.c_str() ) )
		return false;

	m_ShaderID = glCreateProgram(); // create program which contains the shaders
	glAttachShader( m_ShaderID, vsID );
	glAttachShader( m_ShaderID, fsID );

	int attribIdx = 0;
	for ( const auto& attribute : aAttributesToBindVect )
	{
		glBindAttribLocation( m_ShaderID, attribIdx, attribute.c_str() );
		attribIdx++;
	}

	glLinkProgram( m_ShaderID );

	glDeleteShader( vsID );
	glDeleteShader( fsID );

	return true;
}

void CShaderPrivate::use()
{
	glUseProgram( m_ShaderID );
}

void CShaderPrivate::setInt( const std::string& aName, int aInt )
{
	glUniform1i( glGetUniformLocation( m_ShaderID, aName.c_str() ), aInt );
}

void CShaderPrivate::setBool( const std::string& aName, bool aBool )
{
	glUniform1i( glGetUniformLocation( m_ShaderID, aName.c_str() ), (int)aBool );
}

void CShaderPrivate::setFloat( const std::string& aName, float aFloat )
{
	glUniform1f( glGetUniformLocation( m_ShaderID, aName.c_str() ), aFloat );
}

void CShaderPrivate::setMat4( const std::string& aName, glm::mat4& aMat4 )
{
	glUniformMatrix4fv( glGetUniformLocation( m_ShaderID, aName.c_str() ), 1, GL_FALSE, &( aMat4[ 0 ][ 0 ] ) );
}

bool CShaderPrivate::generateShader( unsigned int aShaderType, unsigned int* aShaderId, const char* aShaderRawStr )
{
	if ( !aShaderId )
		return false;

	*aShaderId = glCreateShader( aShaderType );

	glShaderSource( *aShaderId, 1, &aShaderRawStr, NULL );

	glCompileShader( *aShaderId );

	GLint result = GL_FALSE;
	int infoLogLength;
	glGetShaderiv( *aShaderId, GL_COMPILE_STATUS, &result );
	glGetShaderiv( *aShaderId, GL_INFO_LOG_LENGTH, &infoLogLength );

	if ( GL_FALSE == result )
	{
		std::vector<char> VertexShaderErrorMessage( infoLogLength );
		glGetShaderInfoLog( *aShaderId, infoLogLength, NULL, &VertexShaderErrorMessage[ 0 ] );

		m_GameLogger->logError( "Errror at compiling shader" );
		m_GameLogger->logError( VertexShaderErrorMessage.data() );
		return false;
	}

	return true;
}