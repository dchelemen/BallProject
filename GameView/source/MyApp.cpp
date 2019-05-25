#include "GameView/include/MyApp.h"
#include "GameView/include/GLUtils.hpp"
#include "Logger/include/GameLogger.h"

#include <math.h>

#include <vector>

CMyApp::CMyApp( CObject* aParent )
	: CObject( aParent )
	, m_Logger( nullptr )
	, m_programID( 0 )
	, m_VAO_id( 0 )
	, m_VBO_id( 0 )
	, m_IndexBuffers_id( 0 )
{
	m_Logger = new CGameLogger( "CMyApp", this );
}


CMyApp::~CMyApp()
{
}

bool CMyApp::Init()
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
	
	GLuint vs_ID = loadShader( GL_VERTEX_SHADER, "../GameView/resources/myVert.vert" );
	GLuint fs_ID = loadShader( GL_FRAGMENT_SHADER, "../GameView/resources/myFrag.frag" );

	m_programID = glCreateProgram(); // create program which contains the shaders
	glAttachShader( m_programID, vs_ID );
	glAttachShader( m_programID, fs_ID );

	glBindAttribLocation( m_programID, 0, "vs_in_pos" );
	glBindAttribLocation( m_programID, 1, "vs_in_col" );

	glLinkProgram( m_programID );

	GLint infoLogLength = 0, result = 0;
	glGetProgramiv( m_programID, GL_LINK_STATUS, &result );
	glGetProgramiv( m_programID, GL_INFO_LOG_LENGTH, &infoLogLength );
	if ( GL_FALSE == result )
	{
		char* error = new char[ infoLogLength ];
		glGetProgramInfoLog( m_programID, infoLogLength, NULL, error );
		m_Logger->logError( "[ app.Init() ] Problems at creating shaders: " + std::string( error ) );
		delete[] error;
		return false;
	}

	glDeleteShader( vs_ID );
	glDeleteShader( fs_ID );

	m_Proj_mtx = glm::perspective( glm::radians( 45.f ), 1024/720.f, 1.0f, 1000.0f );
	m_MVPLocation = glGetUniformLocation( m_programID, "MVP" );

	return true;
}

void CMyApp::Clean()
{
	glDeleteBuffers( 1, &m_VBO_id );
	glDeleteVertexArrays( 1, &m_VAO_id );

	glDeleteProgram( m_programID );
}

void CMyApp::Update()
{
	m_View_mtx = glm::lookAt( glm::vec3( 0, 20, 20 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
}


void CMyApp::Render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glUseProgram( m_programID ); // activate shaders
	glBindVertexArray( m_VAO_id ); // Activate VAO ( VBO automatically comes with it )

	glm::mat4 mvp( 0 );

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

		mvp = m_Proj_mtx * m_View_mtx * m_Model_mtx;
		glUniformMatrix4fv( m_MVPLocation, 1, GL_FALSE, &( mvp[ 0 ][ 0 ] ) );
		glDrawElements( GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0 );
	}

	m_Model_mtx =
		glm::rotate <float>( SDL_GetTicks() / 10000.0f, glm::vec3( 0, 1, 0 ) ) *
		glm::scale<float>( glm::vec3( 1, abs( sin( SDL_GetTicks() / 10000.0 * 2 * M_PI ) * 2 ), 1 ) );

	mvp = m_Proj_mtx * m_View_mtx * m_Model_mtx;
	glUniformMatrix4fv( m_MVPLocation, 1, GL_FALSE, &( mvp[ 0 ][ 0 ] ) );
	glDrawElements( GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0 );

	glBindVertexArray( 0 ); // inactivate VAO
	glUseProgram( 0 ); // inactivate shaders
}

void CMyApp::KeyboardDown( SDL_KeyboardEvent& key )
{
	switch ( key.keysym.sym )
	{
	case SDLK_DOWN:
	case SDLK_s: break;
	case SDLK_UP:
	case SDLK_w: break;
	case SDLK_LEFT:
	case SDLK_a: break;
	case SDLK_RIGHT:
	case SDLK_d: break;
	}
}

void CMyApp::KeyboardUp( SDL_KeyboardEvent& key )
{
}

void CMyApp::MouseMove( SDL_MouseMotionEvent& mouse )
{
}

void CMyApp::MouseDown( SDL_MouseButtonEvent& mouse )
{
}

void CMyApp::MouseUp( SDL_MouseButtonEvent& mouse )
{
}

void CMyApp::MouseWheel( SDL_MouseWheelEvent& wheel )
{
}

void CMyApp::Resize( int _w, int _h )
{
	glViewport( 0, 0, _w, _h );

	m_Proj_mtx = glm::perspective( 45.0f, (float) _w/ _h, 1.0f, 1000.0f );
}
