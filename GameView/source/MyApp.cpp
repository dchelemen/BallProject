#include "GameView/include/MyApp.h"
#include "GameView/include/GLUtils.hpp"
#include "Logger/include/GameLogger.h"

#include <math.h>

#include <vector>

CMyApp::CMyApp(void)
	: m_Logger( nullptr )
	, m_programID( 0 )
	, m_vaoID( 0 )
	, m_vboID( 0 )
{
	std::string className( "CMyApp" );
	m_Logger = new CGameLogger( className.c_str(), className.size() );
}


CMyApp::~CMyApp(void)
{
	delete m_Logger;
}

bool CMyApp::Init()
{
	// törlési szín legyen kékes
	glClearColor( 0.125f, 0.25f, 0.5f, 1.0f );

	//glEnable( GL_CULL_FACE ); // kapcsoljuk be a hatrafele nezo lapok eldobasat
	glEnable( GL_DEPTH_TEST ); // mélységi teszt bekapcsolása (takarás)
	glPolygonMode( GL_BACK, GL_LINE );
							   //
							   // geometria letrehozasa
							   //


	std::vector<Vertex> vertices;
	
	vertices.push_back( { glm::vec3( 1, 0, 1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( -1, 0, -1 ), glm::vec3( 1, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 1, 0, -1 ), glm::vec3( 1, 0, 1 ) } );

	vertices.push_back( { glm::vec3( -1, 0, 1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( -1, 0, -1 ), glm::vec3( 1, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 1, 0, 1 ), glm::vec3( 1, 0, 1 ) } );

	vertices.push_back( { glm::vec3( -1, 0, 1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( 1, 0, 1 ), glm::vec3( 1, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 0, 2, 0 ), glm::vec3( 1, 0, 1 ) } );

	vertices.push_back( { glm::vec3( 1, 0, 1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( 1, 0, -1 ), glm::vec3( 1, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 0, 2, 0 ), glm::vec3( 1, 0, 1 ) } );
	
	vertices.push_back( { glm::vec3( 1, 0, -1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( -1, 0, -1 ), glm::vec3( 1, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 0, 2, 0 ), glm::vec3( 1, 0, 1 ) } );

	vertices.push_back( { glm::vec3( -1, 0, -1 ), glm::vec3( 1, 0, 0 ) } );
	vertices.push_back( { glm::vec3( -1, 0, 1 ), glm::vec3( 1, 1, 0 ) } );
	vertices.push_back( { glm::vec3( 0, 2, 0 ), glm::vec3( 1, 0, 1 ) } );

	// 1 db VAO foglalasa
	glGenVertexArrays( 1, &m_vaoID );
	// a frissen generált VAO beallitasa aktívnak
	glBindVertexArray( m_vaoID );

	// hozzunk létre egy új VBO erõforrás nevet
	glGenBuffers( 1, &m_vboID );
	glBindBuffer( GL_ARRAY_BUFFER, m_vboID ); // tegyük "aktívvá" a létrehozott VBO-t
											  // töltsük fel adatokkal az aktív VBO-t
	glBufferData( GL_ARRAY_BUFFER,	// az aktív VBO-ba töltsünk adatokat
				  vertices.size() * sizeof( Vertex ),		// ennyi bájt nagyságban
				  vertices.data(),	// errõl a rendszermemóriabeli címrõl olvasva
				  GL_STATIC_DRAW );	// úgy, hogy a VBO-nkba nem tervezünk ezután írni és minden kirajzoláskor felhasnzáljuk a benne lévõ adatokat


									// VAO-ban jegyezzük fel, hogy a VBO-ban az elsõ 3 float sizeof(Vertex)-enként lesz az elsõ attribútum (pozíció)
	glEnableVertexAttribArray( 0 ); // ez lesz majd a pozíció
	glVertexAttribPointer(
		(GLuint)0,				// a VB-ben található adatok közül a 0. "indexû" attribútumait állítjuk be
		3,				// komponens szam
		GL_FLOAT,		// adatok tipusa
		GL_FALSE,		// normalizalt legyen-e
		sizeof( Vertex ),	// stride (0=egymas utan)
		0				// a 0. indexû attribútum hol kezdõdik a sizeof(Vertex)-nyi területen belül
	);

	// a második attribútumhoz pedig a VBO-ban sizeof(Vertex) ugrás után sizeof(glm::vec3)-nyit menve újabb 3 float adatot találunk (szín)
	glEnableVertexAttribArray( 1 ); // ez lesz majd a szín
	glVertexAttribPointer(
		(GLuint)1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof( Vertex ),
		(void*)( sizeof( glm::vec3 ) ) );

	glBindVertexArray( 0 ); // feltöltüttük a VAO-t, kapcsoljuk le
	glBindBuffer( GL_ARRAY_BUFFER, 0 ); // feltöltöttük a VBO-t is, ezt is vegyük le

										//
										// shaderek betöltése
										//
	
	GLuint vs_ID = loadShader( GL_VERTEX_SHADER, "../GameView/resources/myVert.vert" );
	GLuint fs_ID = loadShader( GL_FRAGMENT_SHADER, "../GameView/resources/myFrag.frag" );

	// a shadereket tároló program létrehozása
	m_programID = glCreateProgram();

	// adjuk hozzá a programhoz a shadereket
	glAttachShader( m_programID, vs_ID );
	glAttachShader( m_programID, fs_ID );

	// attributomok osszerendelese a VAO es shader kozt
	glBindAttribLocation( m_programID, 0, "vs_in_pos" );
	glBindAttribLocation( m_programID, 1, "vs_in_col" );

	// illesszük össze a shadereket (kimenõ-bemenõ változók összerendelése stb.)
	glLinkProgram( m_programID );

	// linkeles ellenorzese
	GLint infoLogLength = 0, result = 0;

	glGetProgramiv( m_programID, GL_LINK_STATUS, &result );
	glGetProgramiv( m_programID, GL_INFO_LOG_LENGTH, &infoLogLength );
	if ( GL_FALSE == result )
	{
		char* error = new char[ infoLogLength ];
		glGetProgramInfoLog( m_programID, infoLogLength, NULL, error );
		std::string errorMessage =  std::string( "[ app.Init() ] Problems at creating shaders: " ) + std::string( error );
		m_Logger->logError( errorMessage.c_str() );
		delete[] error;
		return false;
	}

	// mar nincs ezekre szukseg
	glDeleteShader( vs_ID );
	glDeleteShader( fs_ID );

	m_matProj = glm::perspective( 45.0f, 640/480.0f, 1.0f, 1000.0f );
	m_loc_world = glGetUniformLocation( m_programID, "world" );
	m_loc_view = glGetUniformLocation( m_programID, "view" );
	m_loc_proj = glGetUniformLocation( m_programID, "proj" );

	return true;
}

void CMyApp::Clean()
{
	glDeleteBuffers( 1, &m_vboID );
	glDeleteVertexArrays( 1, &m_vaoID );

	glDeleteProgram( m_programID );
}

void CMyApp::Update()
{
	m_matView = glm::lookAt( glm::vec3( 0, 5, 5 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
}


void CMyApp::Render()
{
	// töröljük a frampuffert (GL_COLOR_BUFFER_BIT) és a mélységi Z puffert (GL_DEPTH_BUFFER_BIT)
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// shader bekapcsolasa
	glUseProgram( m_programID );

	glUniformMatrix4fv( m_loc_view, 1, GL_FALSE, &( m_matView[ 0 ][ 0 ] ) );
	glUniformMatrix4fv( m_loc_proj, 1, GL_FALSE, &(  m_matProj[ 0 ][ 0 ] ) );

	// kapcsoljuk be a VAO-t (a VBO jön vele együtt)
	glBindVertexArray( m_vaoID );

	for ( int i = 0; i < 10; ++i )
	{
		m_matWorld = 
			glm::rotate<float>( 360.0f / 10 * i, glm::vec3( 0, 1, 0 ) ) *
			glm::rotate<float>( SDL_GetTicks() / 1000.0f / 10, glm::vec3( 0, 1, 0 ) ) *
			glm::translate<float>( glm::vec3( 3, 0, 0 ) ) *
			glm::rotate<float>( SDL_GetTicks() / 1000.0f, glm::vec3( -1, 0, 0 ) ) *
			glm::rotate <float>( 90, glm::vec3( 0, 0, 1 ) ) *
			glm::translate<float>( glm::vec3( 0, -1, 0 ) );

		glUniformMatrix4fv( m_loc_world, 1, GL_FALSE, &( m_matWorld[ 0 ][ 0 ] ) );
		glDrawArrays( GL_TRIANGLES, 0, 18 );
	}

	m_matWorld =
		glm::rotate <float>( SDL_GetTicks() / 10000.0f, glm::vec3( 0, 1, 0 ) ) *
		glm::scale<float>( glm::vec3( 1, abs( sin( SDL_GetTicks() / 10000.0 * 2 * M_PI ) * 2 ), 1 ) );

	glUniformMatrix4fv( m_loc_world, 1, GL_FALSE, &( m_matWorld[ 0 ][ 0 ] ) );
	glDrawArrays( GL_TRIANGLES, 0, 18 );

	// VAO kikapcsolasa
	glBindVertexArray( 0 );

	// shader kikapcsolasa
	glUseProgram( 0 );
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

// a két paraméterbe az új ablakméret szélessége (_w) és magassága (_h) található
void CMyApp::Resize( int _w, int _h )
{
	glViewport( 0, 0, _w, _h );

	m_matProj = glm::perspective( 45.0f, (float) _w/ _h, 1.0f, 1000.0f );
}
