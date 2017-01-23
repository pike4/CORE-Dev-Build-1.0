#pragma once
#include "LoggingStream.h"

#include <iostream>
#include <sstream>

class LogWindowStream : public LoggingStream
{
public:
	virtual void log(std::string output);
	virtual void flush();
	virtual int open();
	virtual void close();

protected:
	std::stringstream windowStream;

	bool buffered = false;
	int bufferSize = 256;
};