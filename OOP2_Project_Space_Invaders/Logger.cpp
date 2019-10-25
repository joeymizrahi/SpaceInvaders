#include "Logger.h"
#include <time.h>

//function returns a string of current time
const std::string CurrentDateTime()
{
	time_t     now = time(NULL);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}
//-------------------------------------------------------------------------
Logger::Logger()
{
	m_logFile.open("log.txt", std::ofstream::out | std::ios::trunc);
	m_logFile.clear();
}
//-------------------------------------------------------------------------
Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}
//-------------------------------------------------------------------------
void Logger::addLog(const std::string &str)
{
	m_logFile << CurrentDateTime() << "\t";
	m_logFile << str + "\n";
}
//-------------------------------------------------------------------------
Logger::~Logger()
{
	m_logFile.close();
}
