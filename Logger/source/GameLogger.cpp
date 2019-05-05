#include "Logger/include/GameLogger.h"
#include <windows.h>

CGameLoggerPrivate* CGameLogger::m_Private = new CGameLoggerPrivate();

static const int LOG_TYPE_START_POS = 0;
static const int THREAD_ID_START_POS = 10;
static const int CLASS_NAME_START_POS = 20;
static const int MESSAGE_START_POS = 50;
 
CGameLogger::CGameLogger( const std::string& aClassName )
	: m_ClassName( aClassName )
{
	m_Private->run();
}

CGameLogger::~CGameLogger()
{
	m_Private->stop();
	if ( m_Private->instanceNumber() <= 0 )
	{
		delete m_Private;
		m_Private = nullptr;
	}
}

void CGameLogger::setFileName( const std::string& aFileName )
{
	m_Private->setFileName( std::string( aFileName ) );
}

void CGameLogger::logError( const std::string& aError )
{
	log( "ERROR", aError );
}

void CGameLogger::logInfo( const std::string& aInfo )
{
	log( "INFO", aInfo );
}

void CGameLogger::log( const std::string& aType, const std::string& aMessage )
{
	std::string tId = std::to_string( GetCurrentThreadId() );
	std::string message( aMessage );

	m_Private->log( aType
				   + std::string( THREAD_ID_START_POS - aType.length(), ' ' )
				   + tId
				   + std::string( CLASS_NAME_START_POS - ( THREAD_ID_START_POS + tId.length() ), ' ' )
				   + m_ClassName
				   + std::string( MESSAGE_START_POS - ( CLASS_NAME_START_POS + m_ClassName.length() ), ' ' )
				   + message
				   + "\n" );
}
