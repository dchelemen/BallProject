#include "GameView/include/GameViewPrivate.h"
#include "GameView/include/DefaultShader.h"
#include "GameView/include/Camera.h"
#include "Logger/include/GameLogger.h"

#include <glm/gtx/transform2.hpp>

#include <math.h>

#include <vector>

CGameViewPrivate::CGameViewPrivate( CObject* aParent )
	: CObject( aParent )
	, m_Logger( nullptr )
	, m_VAO_id( 0 )
	, m_VBO_id( 0 )
	, m_IndexBuffers_id( 0 )
	, m_Camera( new CCamera( this ) )
	, m_DefaultShader( new CDefaultShader( this ) )
{
	m_Logger = new CGameLogger( "CMyApp", this );
}


CGameViewPrivate::~CGameViewPrivate()
{
	Clean();
}

bool CGameViewPrivate::Init()
{
	glClearColor( 0.529f, 0.808f, 0.922f, 1.0f ); // skyblue

	//glEnable( GL_CULL_FACE );
	glEnable( GL_DEPTH_TEST );
	glPolygonMode( GL_BACK, GL_LINE );

	std::vector<SVertex> vertices;
	
	//bottom
	vertices.push_back( { glm::vec3( 1, 0, 1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( -1, 0, 1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( -1, 0, -1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( 1, 0, -1 ), glm::vec3( 1, 0, 0 ) } );

	//green side
	vertices.push_back( { glm::vec3( 1, 0, 1 ), glm::vec3( 0, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 1, 0, -1 ), glm::vec3( 0, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 0, 2, 0 ), glm::vec3( 0, 1, 0 ) } );

	//purple side
	vertices.push_back( { glm::vec3( 1, 0, -1 ), glm::vec3( 1, 0, 1 ) } );
	vertices.push_back( { glm::vec3( -1, 0, -1 ), glm::vec3( 1, 0, 1 ) } );
	vertices.push_back( { glm::vec3( 0, 2, 0 ), glm::vec3( 1, 0, 1 ) } );

	//blue side
	vertices.push_back( { glm::vec3( -1, 0, -1 ), glm::vec3( 0, 0, 1 ) } );
	vertices.push_back( { glm::vec3( -1, 0, 1 ), glm::vec3( 0, 0, 1 ) } );
	vertices.push_back( { glm::vec3( 0, 2, 0 ), glm::vec3( 0, 0, 1 ) } );

	//yellow side
	vertices.push_back( { glm::vec3( -1, 0, 1 ), glm::vec3( 1, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 1, 0, 1 ), glm::vec3( 1, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 0, 2, 0 ), glm::vec3( 1, 1, 0 ) } );


	GLushort indexes[] =
		{
			0, 1, 2, 0, 2, 3,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

	glGenVertexArrays( 1, &m_VAO_id ); // generate VAO
	glBindVertexArray( m_VAO_id ); // set this VAO active

	glGenBuffers( 1, &m_VBO_id ); // generate VBO
	glBindBuffer( GL_ARRAY_BUFFER, m_VBO_id ); // set this VBO active

	glBufferData( GL_ARRAY_BUFFER,	// set the data to the active vbo
				  vertices.size() * sizeof( SVertex ),
				  vertices.data(),
				  GL_STATIC_DRAW );

	glGenBuffers( 1, &m_IndexBuffers_id );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffers_id );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indexes ), indexes, GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 ); // set the position to VAO
	glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof( SVertex ), 0 );

	glEnableVertexAttribArray( 1 ); // set the color to VAO
	glVertexAttribPointer( (GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof( SVertex ), (void*)( sizeof( glm::vec3 ) ) );

	glBindVertexArray( 0 ); // set VAO inactive
	glBindBuffer( GL_ARRAY_BUFFER, 0 ); // set VBO inactive
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // set VBO inactive
	
	if ( !m_DefaultShader->isValid() )
	{
		m_Logger->logError( "Invalid Shader" );
		return false;
	}

	m_Proj_mtx = glm::perspective( glm::radians( 45.f ), 1280/720.f, 1.0f, 1000.0f );
	m_Camera->setView( glm::vec3( 0, 20, 20 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );

	return true;
}

void CGameViewPrivate::Clean()
{
	glDeleteBuffers( 1, &m_VBO_id );
	glDeleteBuffers( 1, &m_IndexBuffers_id );
	glDeleteVertexArrays( 1, &m_VAO_id );
}

void CGameViewPrivate::Render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_DefaultShader->use(); // activate default shader
	glBindVertexArray( m_VAO_id ); // Activate VAO ( VBO automatically comes with it )

	glm::mat4 mvp( 0 );

	auto viewMtx = m_Camera->getViewMtx();
	float rotateDeg = SDL_GetTicks() / 1000.0f;
	for ( int i = 0; i < 10; i++ )
	{
		m_Model_mtx =
			glm::rotate<float>( glm::radians( ( 360.f / 10 ) * i ), glm::vec3( 0, 1, 0 ) ) *
			glm::rotate<float>( rotateDeg, glm::vec3( 0, 1, 0 ) ) *
			glm::translate<float>( glm::vec3( 0, 0, -5 ) ) *
			glm::rotate<float>( SDL_GetTicks() / 1000.f, glm::vec3( 0, 0, 1 ) ) *
			glm::rotate<float>( glm::radians( 90.f ), glm::vec3( 1.f, 0, 0 ) ) *
			glm::translate<float>( glm::vec3( 0, -1, 0 ) );

		mvp = m_Proj_mtx * viewMtx * m_Model_mtx;
		m_DefaultShader->setMVP_mtx( mvp );

		glDrawElements( GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0 );
	}

	m_Model_mtx =
		glm::rotate <float>( SDL_GetTicks() / 10000.0f, glm::vec3( 0, 1, 0 ) ) *
		glm::scale<float>( glm::vec3( 1, abs( sin( SDL_GetTicks() / 10000.0 * 2 * M_PI ) * 2 ), 1 ) );

	mvp = m_Proj_mtx * viewMtx * m_Model_mtx;
	m_DefaultShader->setMVP_mtx( mvp );

	glDrawElements( GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0 );

	glBindVertexArray( 0 ); // inactivate VAO
	glUseProgram( 0 ); // inactivate shaders
}

void CGameViewPrivate::KeyboardDown( SDL_KeyboardEvent& key )
{
	m_Camera->keyDown( key.keysym.sym, SDL_GetTicks() );
}

void CGameViewPrivate::KeyboardUp( SDL_KeyboardEvent& key )
{
	m_Camera->keyUp( key.keysym.sym );
}

void CGameViewPrivate::MouseMove( SDL_MouseMotionEvent& mouse )
{
	m_Camera->mouseMove( mouse.x, mouse.y );
}

void CGameViewPrivate::MouseDown( SDL_MouseButtonEvent& mouse )
{
}

void CGameViewPrivate::MouseUp( SDL_MouseButtonEvent& mouse )
{
}

void CGameViewPrivate::MouseWheel( SDL_MouseWheelEvent& wheel )
{
}

void CGameViewPrivate::Resize( int _w, int _h )
{
	glViewport( 0, 0, _w, _h );

	m_Proj_mtx = glm::perspective( 45.0f, (float) _w/ _h, 1.0f, 1000.0f );
}
