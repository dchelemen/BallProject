
#include <iostream>
#include <chrono>
#include <thread>

#include "GameView/include/GameView.h"
#include "Logger/include/GameLogger.h"

int main( int argc, char* args[] )
{
	std::string str = "Main";
	CGameLogger logger( str.c_str(), str.length() );
	logger.logInfo( "//----------" );
	logger.logInfo( "//----------" );
	logger.logInfo( "//----------" );
	logger.logInfo( "Main Started" );

	CGameView view;
	view.run();

	return 0;
}