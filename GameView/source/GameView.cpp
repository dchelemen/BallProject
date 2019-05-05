
#include "GameView/include/GameView.h"
#include "GameView/include/MyApp.h"
#include "Logger/include/GameLogger.h"

#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <SDL_opengl.h>

CGameView::CGameView()
	: m_Window( nullptr )
	, m_Context( nullptr )
	, m_Logger( nullptr )
{
	m_Logger = new CGameLogger( "CGameView" );

}


CGameView::~CGameView()
{
	SDL_Quit();
	delete m_MyApp;
	delete m_Logger;
}

void CGameView::initialize()
{
	m_Logger->logInfo( "Initializing" );
	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 )
	{
		std::string msg = "[Initialize] Error SDL_Init: " + std::string( SDL_GetError() );
		m_Logger->logError( msg.c_str() );
		return;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

	m_Window = SDL_CreateWindow( "Hello SDL&OpenGL!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if ( !m_Window )
	{
		std::string msg = "[Initialize] Error SDL_CreateWindow: " + std::string( SDL_GetError() );
		m_Logger->logError( msg.c_str() );
		return;
	}

	m_Context = SDL_GL_CreateContext( m_Window );
	if ( !m_Context )
	{
		std::string msg = "[Initialize] Error SDL_CreateContext: " + std::string( SDL_GetError() );
		m_Logger->logError( msg.c_str() );
		return;
	}

	SDL_GL_SetSwapInterval( 1 );

	// ind�tsuk el a GLEW-t
	GLenum error = glewInit();
	if ( error != GLEW_OK )
	{
		SDL_GL_DeleteContext( m_Context );
		SDL_DestroyWindow( m_Window );

		m_Logger->logError( "[Initialize] Error at glewInit" );
		return;
	}

	// k�rdezz�k le az OpenGL verzi�t
	int glVersion[ 2 ] = { -1, -1 };
	glGetIntegerv( GL_MAJOR_VERSION, &glVersion[ 0 ] );
	glGetIntegerv( GL_MINOR_VERSION, &glVersion[ 1 ] );

	std::string str( "Running OpenGL " + std::to_string( glVersion[ 0 ] ) + '.' + std::to_string( glVersion[ 1 ] ) );
	m_Logger->logInfo( str.c_str() );

	if ( glVersion[ 0 ] == -1 || glVersion[ 1 ] == -1 )
	{
		SDL_GL_DeleteContext( m_Context );
		SDL_DestroyWindow( m_Window );

		m_Logger->logError( "[Initialize] Error at creating OGL context. Probably wrong SDL_GL_SetAttribute(...)" );
		return;
	}

	std::stringstream window_title;
	window_title << "OpenGL " << glVersion[ 0 ] << "." << glVersion[ 1 ];
	SDL_SetWindowTitle( m_Window, window_title.str().c_str() );

	m_MyApp = new CMyApp();
	if ( !m_MyApp->Init() )
	{
		SDL_GL_DeleteContext( m_Context );
		SDL_DestroyWindow( m_Window );
		return;
	}
}

bool CGameView::run()
{
	m_Logger->logInfo( "Run started" );
	initialize();

	SDL_Event sdlEvent;
	bool quit = false;
	while ( !quit )
	{
		// am�g van feldolgozand� �zenet dolgozzuk fel mindet:
		while ( SDL_PollEvent( &sdlEvent ) )
		{
			switch ( sdlEvent.type )
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if ( sdlEvent.key.keysym.sym == SDLK_ESCAPE )
					quit = true;
				m_MyApp->KeyboardDown( sdlEvent.key );
				break;
			case SDL_KEYUP:
				m_MyApp->KeyboardUp( sdlEvent.key );
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_MyApp->MouseDown( sdlEvent.button );
				break;
			case SDL_MOUSEBUTTONUP:
				m_MyApp->MouseUp( sdlEvent.button );
				break;
			case SDL_MOUSEWHEEL:
				m_MyApp->MouseWheel( sdlEvent.wheel );
				break;
			case SDL_MOUSEMOTION:
				m_MyApp->MouseMove( sdlEvent.motion );
				break;
			case SDL_WINDOWEVENT:
				if ( sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
				{
					m_MyApp->Resize( sdlEvent.window.data1, sdlEvent.window.data2 );
				}
				break;
			}
		}

		m_MyApp->Update();
		m_MyApp->Render();

		SDL_GL_SwapWindow( m_Window );
	}

	m_Logger->logInfo( "Run Finished" );
	return true;
}

void CGameView::stop()
{
	SDL_GL_DeleteContext( m_Context );
	SDL_DestroyWindow( m_Window );
}

