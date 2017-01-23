#include "LogFileStream.h"

void LogFileStream::log(std::string output)
{
	outputFile << output;
}

void LogFileStream::flush()
{
	outputFile.flush();
}

int LogFileStream::open()
{
	outputFile.open(path);

	if (outputFile.good() && outputFile.is_open())
	{
		return 1;
	}

	else
	{
		//TODO: global failsafe output
	}
}

void LogFileStream::close()
{
	outputFile.close();
}