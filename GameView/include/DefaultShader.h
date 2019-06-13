#pragma once

#include "GameView\include\Export.h"
#include "GameCommon\include\Object.h"

#include <glm/mat4x4.hpp>

class CShaderPrivate;
class CGameLogger;

class GAMEVIEW_API CDefaultShader : public CObject
{
public:
	CDefaultShader( CObject* aParent = nullptr );
	~CDefaultShader();

	bool isValid();
	void use();

	void setMVP_mtx( glm::mat4& aMVP );

private:
	CShaderPrivate*		m_Private;
	CGameLogger*		m_GameLogger;
	bool				m_IsValid;
};