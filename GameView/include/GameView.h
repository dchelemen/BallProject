#pragma once

#include "GameCommon/include/Object.h"
#include "GameView/include/Export.h"

class CGameLogger;
class CMyApp;
class CGameWindow;

class GAMEVIEW_API CGameView : public CObject
{
public:
	CGameView( CObject* aParent );
	~CGameView();

	bool run();
	void stop();

private:
	bool initialize();

private:
	CGameWindow*	m_Window;
	CGameLogger*	m_Logger;

	CMyApp*			m_MyApp;
};