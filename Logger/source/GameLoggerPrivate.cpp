#include "Logger/include/GameLoggerPrivate.h"

#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>

CGameLoggerPrivate::CGameLoggerPrivate()
	: m_IsRunning( false )
	, m_FileName( "C:/Users/chele/Desktop/Work/GameLog.log" )
	, m_Thread()
	, m_InstanceNumber( 0 )
{

}

CGameLoggerPrivate::~CGameLoggerPrivate()
{
	m_IsRunning = false;
	if ( m_Thread.joinable() )
		m_Thread.join();
}

void CGameLoggerPrivate::setFileName( const std::string& aFileName )
{
	m_FileName = aFileName;
}

void CGameLoggerPrivate::run()
{
	m_InstanceNumber++;

	if ( m_IsRunning )
		return;

	std::ofstream f;
	f.open( m_FileName.c_str(), std::ofstream::app );
	if ( !f.is_open() )
	{
		return;
	}
	f.close();

	m_IsRunning = true;
	m_Thread = std::thread( &CGameLoggerPrivate::saveMessage, this );
}

void CGameLoggerPrivate::stop()
{
	m_InstanceNumber--;
	if ( m_InstanceNumber <= 0 )
		m_IsRunning = false;
}

void CGameLoggerPrivate::log( const std::string& aMessage )
{
	m_Messages.push( aMessage );
}

int CGameLoggerPrivate::instanceNumber() const
{
	return m_InstanceNumber;
}

void CGameLoggerPrivate::saveMessage( )
{
	while ( m_IsRunning )
	{
		bool empty = m_Messages.empty();
		if ( !empty )
		{
			std::ofstream f( m_FileName.c_str(), std::ofstream::app );
			while ( !m_Messages.empty() )
			{
				std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
				std::time_t now_c = std::chrono::system_clock::to_time_t( now - std::chrono::hours( 24 ) );
				std::tm bt;
				localtime_s( &bt, &now_c );
				f << std::put_time( &bt, "%F %T" ) << "\t\t" << m_Messages.front();
				m_Messages.pop();
			}
			f.close();
		}
	}
}

