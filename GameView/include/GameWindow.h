#pragma once

#include "GameCommon\include\Object.h"

class CGameLogger;
struct SDL_Window;

class CGameWindow : public CObject
{
public:
	CGameWindow( CObject* aParent = nullptr );
	~CGameWindow();

	void setProperties( const std::string& aTitle, int aX, int aY, int aWidth, int aHeight, unsigned int aSDLFlags );

	bool buildWindow();
	void destroyWindow();

	SDL_Window* getWindow();

private:
	std::string			m_Title;
	int					m_X;
	int					m_Y;
	int					m_Width;
	int					m_Height;
	unsigned int		m_SDLFlags;

	void*				m_Context;
	SDL_Window*			m_Window;

	CGameLogger*		m_Logger;
};