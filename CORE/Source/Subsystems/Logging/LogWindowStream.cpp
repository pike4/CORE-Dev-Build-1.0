#include "LogWindowStream.h"

void LogWindowStream::log(std::string output)
{
	windowStream << output <<std::endl;

	if (!buffered || windowStream.tellp() > bufferSize)
	{
		flush();
	}
}

void LogWindowStream::flush()
{
	std::cout << windowStream.rdbuf();
}

int LogWindowStream::open() { return 1; }

void LogWindowStream::close() 
{
	flush();
}