#pragma once

#include "Logger/include/Export.h"
#include "Logger/include/GameLoggerPrivate.h"

#include <string>

class LOGGER_API CGameLogger
{
public:
	CGameLogger( const char* aClassName, size_t aSize );
	~CGameLogger();

	void setFileName( const char* aFileName );
	void logError( const char* aError );
	void logInfo( const char* aError );

private:
	void log( const char* aType, const char* aMessage );

private:
	static CGameLoggerPrivate*		m_Private;
	char*							m_ClassName;
	size_t							m_ClassNameSize;
};