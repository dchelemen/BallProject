
#include "GameView/include/GameView.h"
#include "GameView/include/GameViewPrivate.h"
#include "GameView/include/GameWindow.h"
#include "Logger/include/GameLogger.h"

CGameView::CGameView( CObject* aParent )
	: CObject( aParent )
	, m_Window( new CGameWindow( this ) )
	, m_Logger( new CGameLogger( "CGameView", this ) )
	, m_GameViewPrivate( nullptr )
{
}


CGameView::~CGameView()
{
}

bool CGameView::initialize()
{
	m_Logger->logInfo( "initializing GameView" );

	m_Window->setProperties( "OpenGLProject", 100, 100, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if ( !m_Window->buildWindow() )
		return false;

	m_GameViewPrivate = new CGameViewPrivate( this );
	if ( !m_GameViewPrivate->Init() )
	{
		m_Window->destroyWindow();
		return false;
	}

	return true;
}

bool CGameView::run()
{
	if ( !initialize() )
		return false;


	m_Logger->logInfo( "Run started" );
	

	SDL_Event sdlEvent;
	bool quit = false;
	while ( !quit )
	{
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
				m_GameViewPrivate->KeyboardDown( sdlEvent.key );
				break;
			case SDL_KEYUP:
				m_GameViewPrivate->KeyboardUp( sdlEvent.key );
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_GameViewPrivate->MouseDown( sdlEvent.button );
				break;
			case SDL_MOUSEBUTTONUP:
				m_GameViewPrivate->MouseUp( sdlEvent.button );
				break;
			case SDL_MOUSEWHEEL:
				m_GameViewPrivate->MouseWheel( sdlEvent.wheel );
				break;
			case SDL_MOUSEMOTION:
				m_GameViewPrivate->MouseMove( sdlEvent.motion );
				break;
			case SDL_WINDOWEVENT:
				if ( sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
				{
					m_GameViewPrivate->Resize( sdlEvent.window.data1, sdlEvent.window.data2 );
				}
				break;
			}
		}

		m_GameViewPrivate->Render();

		SDL_GL_SwapWindow( m_Window->getWindow() );
	}

	m_Logger->logInfo( "Run Finished" );
	return true;
}

void CGameView::stop()
{
	m_Window->destroyWindow();
}

