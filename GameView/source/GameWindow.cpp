#include "GameView\include\GameWindow.h"
#include "Logger\include\GameLogger.h"

#include <SDL.h>
#include <GL/glew.h>

CGameWindow::CGameWindow( CObject* aParent )
	: CObject( aParent )
	, m_Title( "OpenGLProject" )
	, m_X( 100 )
	, m_Y( 100 )
	, m_Width( 1280 )
	, m_Height( 720 )
	, m_SDLFlags( SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE )
	, m_Window( nullptr )
	, m_Context( nullptr )
	, m_Logger( new CGameLogger( "GameWindow", this ) )
{

}

CGameWindow::~CGameWindow()
{
	destroyWindow();
}

void CGameWindow::setProperties( const std::string& aTitle, int aX, int aY, int aWidth, int aHeight, unsigned int aSDLFlags )
{
	m_Title = aTitle;
	m_X = aX;
	m_Y = aY;
	m_Width = aWidth;
	m_Height = aHeight;
	m_SDLFlags = aSDLFlags;
}

bool CGameWindow::buildWindow()
{
	if ( m_Window && m_Context )
		destroyWindow(); //destroy if they are already exist

	m_Logger->logInfo( "creating new window" );
	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 )
	{
		m_Logger->logError( "[Initialize] Error SDL_Init: " + std::string( SDL_GetError() ) );
		return false;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	m_Window = SDL_CreateWindow( m_Title.c_str(), m_X, m_Y, m_Width, m_Height, m_SDLFlags );
	if ( !m_Window )
	{
		m_Logger->logError( "[Initialize] Error SDL_CreateWindow: " + std::string( SDL_GetError() ) );
		return false;
	}

	m_Context = SDL_GL_CreateContext( m_Window );
	if ( !m_Context )
	{
		destroyWindow();
		m_Logger->logError( "[Initialize] Error SDL_CreateContext: " + std::string( SDL_GetError() ) );
		return false;
	}

	SDL_GL_SetSwapInterval( 1 );

	GLenum error = glewInit();
	if ( error != GLEW_OK )
	{
		destroyWindow();

		m_Logger->logError( "[Initialize] Error at glewInit" );
		return false;
	}

	// get OpenGL version
	int openGLMajorVersion = -1, openGLMinorVersion = -1;
	glGetIntegerv( GL_MAJOR_VERSION, &openGLMajorVersion );
	glGetIntegerv( GL_MINOR_VERSION, &openGLMinorVersion );

	m_Logger->logInfo( "Running OpenGL " + std::to_string( openGLMajorVersion ) + '.' + std::to_string( openGLMinorVersion ) );

	if ( openGLMajorVersion == -1 || openGLMinorVersion == -1 )
	{
		destroyWindow();

		m_Logger->logError( "[Initialize] Error at creating OGL context. Probably wrong SDL_GL_SetAttribute(...)" );
		return false;
	}

	std::string window_title = "OpenGL " + std::to_string( openGLMajorVersion ) + "." + std::to_string( openGLMinorVersion );
	SDL_SetWindowTitle( m_Window, window_title.c_str() );

	return true;
}

void CGameWindow::destroyWindow()
{
	if ( m_Context )
		SDL_GL_DeleteContext( m_Context );

	if ( m_Window )
		SDL_DestroyWindow( m_Window );

	SDL_Quit();

	m_Context = nullptr;
	m_Window = nullptr;
}

SDL_Window* CGameWindow::getWindow()
{
	return m_Window;
}