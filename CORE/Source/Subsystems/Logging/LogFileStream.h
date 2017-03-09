#pragma once
#include "LoggingStream.h"

#include <fstream>

//Stream for logging output to a file
class LogFileStream : public LoggingStream
{
public:
   LogFileStream(std::string fileName);
	virtual void log(std::string output);
	virtual void flush();
	virtual int open();
	virtual void close();

private:
	std::string path;
	std::ofstream outputFile;
};