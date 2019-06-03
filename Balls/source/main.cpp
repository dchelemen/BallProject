#include "GameView/include/GameView.h"
#include "Logger/include/GameLogger.h"

int main( int argc, char* args[] )
{
	CGameLogger logger( "Main" );
	logger.logInfo( "//----------" );
	logger.logInfo( "//----------" );
	logger.logInfo( "//----------" );
	logger.logInfo( "Main Started" );

	logger.setFileName( "C:/BallProject/GameLog.txt" );

	CGameView view( nullptr );
	view.run();

	return 0;
}