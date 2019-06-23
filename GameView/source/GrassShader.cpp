
#include "GameView\include\GrassShader.h"
#include "GameView\include\ShaderPrivate.h"
#include "Logger\include\GameLogger.h"

CGrassShader::CGrassShader( CObject* aParent )
	: CObject( aParent )
	, m_Private( new CShaderPrivate( this ) )
	, m_GameLogger( new CGameLogger( "CDefaultShader", this ) )
{
	const std::string vertex =
	{
#include "GameView\shaders\Grass.vs"
	};

	const std::string fragment =
	{
#include "GameView\shaders\Grass.fs"
	};

	std::vector< std::string > attribVect = { "vs_in_pos", "vs_in_col" };

	m_IsValid = m_Private->initialize( vertex, fragment, attribVect );
	if ( !m_IsValid )
	{
		m_GameLogger->logError( "Failed to initialize DefaultShader" );
	}
}

CGrassShader::~CGrassShader()
{
}

bool CGrassShader::isValid()
{
	return m_IsValid;
}

void CGrassShader::use()
{
	if ( m_IsValid )
		m_Private->use();
}

void CGrassShader::setMVP_mtx( glm::mat4& aMVP )
{
	m_Private->setMat4( "MVP", aMVP );
}
