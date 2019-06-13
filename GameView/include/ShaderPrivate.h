#pragma once

#include "GameCommon\include\Object.h"
#include <string>
#include <glm/mat4x4.hpp>

class CGameLogger;

class CShaderPrivate : public CObject
{
public:
	CShaderPrivate( CObject* aParent = nullptr );
	virtual ~CShaderPrivate();

	bool initialize( const std::string& aVS, const std::string& aFS, const std::vector< std::string >& aAttributesToBind );

	void use();

	void setInt( const std::string& aName, int aInt );
	void setBool( const std::string& aName, bool aBool );
	void setFloat( const std::string& aName, float aFloat );
	void setMat4( const std::string& aName, glm::mat4& aMat4 );

private:
	bool generateShader( unsigned int aShaderType, unsigned int* aShaderId, const char* aShaderRawStr );

protected:
	unsigned int	m_ShaderID;
	CGameLogger*	m_GameLogger;
};