#pragma once

#include "GameCommon/include/Object.h"

#include <glm/mat4x4.hpp>

#include <map>

class CCamera : public CObject
{
private:
	class CKeyProperties
	{
	public:
		CKeyProperties( unsigned int aTime, bool aIsKeyDown ) : m_LastHandleTime_ms( aTime ), m_IsKeyDown( aIsKeyDown ) {};
		unsigned int	m_LastHandleTime_ms;
		bool			m_IsKeyDown;
	};

public:
	CCamera( CObject* aParent );
	~CCamera();

	glm::mat4 getViewMtx();
	void setView( const glm::vec3& aEye, const glm::vec3& aLookAt, const glm::vec3& aUpDirection );

	void keyDown( int aKeyCode, unsigned int aPushTime );
	void keyUp( int aKeyCode );

	void mouseMove( int aXmove, int aYmove );

private:
	void eraseKeys( const std::vector< int >& aEraseVect );
	void processKeyMap();

private:
	std::map< int, CKeyProperties >	m_KeysPushedDownMap;

	glm::vec3						m_CameraPos;
	glm::vec3						m_CameraDirection;
	glm::vec3						m_CameraUp;

	glm::vec2						m_OldMousePosition;
};