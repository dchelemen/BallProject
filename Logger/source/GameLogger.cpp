#include "Logger/include/GameLogger.h"
#include <windows.h>

CGameLoggerPrivate* CGameLogger::m_Private = new CGameLoggerPrivate();

static const int LOG_TYPE_START_POS = 0;
static const int THREAD_ID_START_POS = 10;
static const int CLASS_NAME_START_POS = 20;
static const int MESSAGE_START_POS = 50;

CGameLogger::CGameLogger( const char* aClassName, size_t aSize )
{
	m_ClassName = new char[ aSize + 1 ];
	memcpy( m_ClassName, aClassName, aSize + 1 );
	m_ClassNameSize = aSize;
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

void CGameLogger::setFileName( const char* aFileName )
{
	m_Private->setFileName( std::string( aFileName ) );
}

void CGameLogger::logError( const char* aError )
{
	log( "ERROR", aError );
}

void CGameLogger::logInfo( const char* aInfo )
{
	log( "INFO", aInfo );
}

void CGameLogger::log( const char* aType, const char* aMessage )
{
	std::string type( aType );
	std::string tId = std::to_string( GetCurrentThreadId() );
	std::string className( m_ClassName, m_ClassNameSize );
	std::string message( aMessage );

	m_Private->log( type
				   + std::string( THREAD_ID_START_POS - type.length(), ' ' )
				   + tId
				   + std::string( CLASS_NAME_START_POS - ( THREAD_ID_START_POS + tId.length() ), ' ' )
				   + className
				   + std::string( MESSAGE_START_POS - ( CLASS_NAME_START_POS + className.length() ), ' ' )
				   + message
				   + "\n" );
}
