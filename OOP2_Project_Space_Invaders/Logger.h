#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <istream>
#include <ostream>

class Logger
{
public:
	~Logger();
	static Logger& getInstance();
	void addLog(const std::string&);
	
private:
	Logger();
	Logger(const Logger&) = delete;
	std::ofstream m_logFile;
};