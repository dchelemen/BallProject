
#include "GameView/include/GameView.h"
#include "Logger/include/GameLogger.h"

int main( int argc, char* args[] )
{
	CGameLogger logger( "Main" );
	logger.setFileName( "C:/BallProject/GameLog.txt" );

	logger.logInfo( "//----------" );
	logger.logInfo( "//----------" );
	logger.logInfo( "//----------" );
	logger.logInfo( "Main Started" );

	

	CGameView view;
	view.run();

	return 0;
}