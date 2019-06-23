
#include "GameView/include/GameView.h"
#include "Logger/include/GameLogger.h"

#include <filesystem>
#include <string>

int main( int argc, char* args[] )
{
	CGameLogger logger( "Main" );

	std::string folderName = "C:/OpenglExperimentProject/";
	std::string fileName = "GameLog.txt";

	{
		namespace fs = std::experimental::filesystem;
		if ( !fs::is_directory( folderName ) || !fs::exists( folderName ) )
		{
			fs::create_directory( folderName );
		}
	}

	logger.setFileName( folderName + fileName );

	logger.logInfo( "//----------" );
	logger.logInfo( "//----------" );
	logger.logInfo( "//----------" );
	logger.logInfo( "Main Started" );

	

	CGameView view;
	view.run();

	return 0;
}