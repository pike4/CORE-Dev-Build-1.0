#pragma once
#include <string>

class LoggingStream
{
public:
	virtual void log(std::string output) = 0;
	virtual void flush() = 0;
	virtual int open() = 0;
	virtual void close() = 0;
};