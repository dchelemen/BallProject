#pragma once

#include "Export.h"
#include "functional"
#include "string"
#include "vector"


// SDL
#include <SDL.h>
//

class CGameLogger;
class CMyApp;

struct SDL_Window;

class GAMEVIEW_API CGameView
{
public:
	CGameView();
	~CGameView();

	bool run();
	void stop();

private:
	void initialize();

private:
	SDL_GLContext	m_Context;
	SDL_Window*		m_Window;
	CGameLogger*	m_Logger;

	CMyApp*		m_MyApp;
};