
#include "GameView\include\DefaultShader.h"
#include "GameView\include\ShaderPrivate.h"
#include "Logger\include\GameLogger.h"

CDefaultShader::CDefaultShader( CObject* aParent )
	: CObject( aParent )
	, m_Private( new CShaderPrivate( this ) )
	, m_GameLogger( new CGameLogger( "CDefaultShader", this ) )
{
	const std::string vertex =
	{
		#include "GameView\shaders\Default.vs"
	};

	const std::string fragment =
	{
		#include "GameView\shaders\Default.fs"
	};

	std::vector< std::string > attribVect = { "vs_in_pos", "vs_in_col" };

	m_IsValid = m_Private->initialize( vertex, fragment, attribVect );
	if ( !m_IsValid )
	{
		m_GameLogger->logError( "Failed to initialize DefaultShader" );
	}
}

CDefaultShader::~CDefaultShader()
{
}

bool CDefaultShader::isValid()
{
	return m_IsValid;
}

void CDefaultShader::use()
{
	if ( m_IsValid )
		m_Private->use();
}

void CDefaultShader::setMVP_mtx( glm::mat4& aMVP )
{
	m_Private->setMat4( "MVP", aMVP );
}
