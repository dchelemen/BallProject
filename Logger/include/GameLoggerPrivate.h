#pragma once

#include "Logger/include/Export.h"

#include <string>
#include <queue>
#include <functional>
#include <thread>

namespace std
{
	class thread;
}

class CGameLoggerPrivate
{
public:
	enum CLogType
	{
		LOGTYPE_ERROR,
		LOGTYPE_INFO
	};

public:
	CGameLoggerPrivate();
	~CGameLoggerPrivate();

	void setFileName( const std::string& aFileName );

	void run();
	void stop();
	void log( const std::string& aMessage );

	int instanceNumber() const;

private:
	void saveMessage();

private:
	std::string						m_FileName;

	int								m_InstanceNumber;
	std::queue< std::string >		m_Messages;
	std::thread						m_Thread;
	bool							m_IsRunning;
};
