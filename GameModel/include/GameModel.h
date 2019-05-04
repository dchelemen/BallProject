#pragma once

#include "GameModel/include/Export.h"

class CGameLogger;

class GAMEMODEL_API CGameModel
{
public:
	CGameModel();
	~CGameModel();

private:
	CGameLogger* logger;
};


