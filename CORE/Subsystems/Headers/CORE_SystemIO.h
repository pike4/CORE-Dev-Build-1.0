#pragma once
#include "LoggingStream.h"

#include <map>
#include <string>

//Creates, stores, and writes to stream implementations
namespace CORE_SystemIO
{
	//TODO: Initialize a stream
	void openLoggingStream(std::string name, int type);

	//TODO: Open a new log file
	void openLogFile(std::string name, std::string path);

	//TODO: Open a new output screen for printing output to the screen
	void openOutputConsole(std::string name);

	//TODO: open developer console for receiving and printing results from developer commands
	void openDeveloperConsole();

	//TODO: Close and free a stream
	void closeStream(std::string name);


	//TODO: 


	//TODO: receive console input


	//TODO: Write the given string to the default output stream
	//print(std::string message);

	//TODO: Write the given string to a given stream
	void print(std::string message, std::string stream); 

	//Collection of publically accessible output streams
	extern std::map<std::string, LoggingStream*> streams;

	enum streamTypes
	{
		file,
		console,
		socket //add more as needed
	};
}