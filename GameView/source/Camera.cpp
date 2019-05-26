#include "GameView/include/Camera.h"

#include <SDL.h>

#include <glm/gtx/transform2.hpp>

static const float ROTATIONAL_SPEED = 0.5f;

CCamera::CCamera( CObject* aParent )
	: CObject( aParent )
{

}

CCamera::~CCamera()
{

}


///
glm::mat4 CCamera::getViewMtx()
{
	processKeyMap();

	return glm::lookAt( m_CameraPos, m_CameraPos + m_CameraDirection, m_CameraUp );;
}

void CCamera::setView( const glm::vec3& aEye, const glm::vec3& aLookAt, const glm::vec3& aUpDirection )
{
	m_CameraPos = aEye;
	m_CameraDirection = aLookAt - aEye;
	m_CameraUp = aUpDirection;
}

void CCamera::keyDown( int aKeyCode, unsigned int aPushTime )
{
	m_KeysPushedDownMap.insert( std::make_pair( aKeyCode, CKeyProperties( aPushTime, true ) ) );
}

void CCamera::keyUp( int aKeyCode )
{
	try
	{
		auto& keyProperties = m_KeysPushedDownMap.at( aKeyCode );
		keyProperties.m_IsKeyDown = false;
	}
	catch ( std::out_of_range ex )
	{
		return;
	}
}

void CCamera::mouseMove( int aXPos, int aYPos )
{
	glm::vec2 newMousePos( aXPos, aYPos );
	glm::vec2 mouseDelta = newMousePos - m_OldMousePosition;

	if ( glm::length( mouseDelta ) > 50.f )
	{
		m_OldMousePosition = newMousePos;
		return;
	}

	glm::vec3 toRotateAround = glm::cross( m_CameraDirection, m_CameraUp );
	glm::mat4 rotateMtx =
		glm::rotate( glm::radians( -mouseDelta.x * ROTATIONAL_SPEED ), m_CameraUp ) *
		glm::rotate( glm::radians( -mouseDelta.y * ROTATIONAL_SPEED ), toRotateAround );

	m_CameraDirection = glm::mat3( rotateMtx ) * m_CameraDirection;

	m_OldMousePosition = newMousePos;
}

void CCamera::eraseKeys( const std::vector< int >& aEraseVect )
{
	for ( int key : aEraseVect )
	{
		m_KeysPushedDownMap.erase( key );
	}
}

void CCamera::processKeyMap()
{
	if ( m_KeysPushedDownMap.empty() )
		return;

	std::vector<int> eraseList;
	int currTime = SDL_GetTicks();
	for ( std::map< int, CKeyProperties >::iterator it = m_KeysPushedDownMap.begin(); it != m_KeysPushedDownMap.end(); it++ )
	{
		float speed = ( currTime - it->second.m_LastHandleTime_ms ) / 100.f;

		switch ( it->first )
		{
		case SDLK_LCTRL:
			{
				m_CameraPos[ 1 ] -= speed;
			} break;
		case SDLK_SPACE:
			{
				m_CameraPos[ 1 ] += speed;
			} break;
		case SDLK_UP:
		case SDLK_w:
			{
				m_CameraPos += m_CameraDirection * ( speed / 50 );
			} break;
		case SDLK_DOWN:
		case SDLK_s:
			{
				m_CameraPos -= m_CameraDirection * ( speed / 50 );
			} break;
		case SDLK_LEFT:
		case SDLK_a:
			{
				m_CameraPos -= glm::normalize( glm::cross( m_CameraDirection, m_CameraUp ) ) * speed;
			} break;
		case SDLK_RIGHT:
		case SDLK_d:
			{
				m_CameraPos += glm::normalize( glm::cross( m_CameraDirection, m_CameraUp ) ) * speed;
			} break;
		}

		it->second.m_LastHandleTime_ms = currTime;

		if ( !it->second.m_IsKeyDown )
		{
			eraseList.push_back( it->first );
		}
	}

	eraseKeys( eraseList );
}

