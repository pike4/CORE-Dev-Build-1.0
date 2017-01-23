#pragma once
#include "LoggingStream.h"

#include <fstream>

class LogFileStream : public LoggingStream
{
public:
	virtual void log(std::string output);
	virtual void flush();
	virtual int open();
	virtual void close();

private:
	std::string path;
	std::ofstream outputFile;
};