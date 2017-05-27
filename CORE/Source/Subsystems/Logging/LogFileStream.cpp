#include "LogFileStream.h"

LogFileStream::LogFileStream(std::string fileName)
{
   path = fileName;
}

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
	outputFile.open(path, std::ofstream::out);

   if (outputFile.good() && outputFile.is_open())
      return 1;

   else
      return 0;
}

void LogFileStream::close()
{
	outputFile.close();
}