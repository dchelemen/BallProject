#pragma once

#include "GameCommon/include/Object.h"
#include "GameView/include/Export.h"

class CGameLogger;
class CGameViewPrivate;
class CGameWindow;

class GAMEVIEW_API CGameView : public CObject
{
public:
	CGameView( CObject* aParent = nullptr );
	~CGameView();

	bool run();
	void stop();

private:
	bool initialize();

private:
	CGameWindow*		m_Window;
	CGameLogger*		m_Logger;

	CGameViewPrivate*	m_GameViewPrivate;
};