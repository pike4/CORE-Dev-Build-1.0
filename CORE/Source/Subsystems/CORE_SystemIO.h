#pragma once
#include "LoggingStream.h"
#include "LogWindowStream.h"

#include <map>
#include <string>

/*
   Purpose:
   Maintain a set of input and output streams
   
   Expose to the engine an API for:
      1. Initializing 
      2. Writing output to a specified stream such as a file or a socket
      3. Reading input from a specified stream
      4. Verifying reads and writes on streams are valid, redirecting to default 
         streams when necessary
      5. Configuring CORE standard input, standard output, and standard err
*/
namespace CORE_SystemIO
{
    void start();

	//TODO: bool treat all warnings as errors (-Werror)


	//TODO: bool verbose warnings and errors (-v)


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
	void print(std::string message);

	//TODO: Write the given string to a given stream
	void print(std::string message, std::string stream); 

   //Output the given message to the current error stream
   void error(std::string errorMessage);

	//Collection of publically accessible output streams
	extern std::map<std::string, LoggingStream*> streams;

   //Stream to output to when outputting to another stream fails
   extern LogWindowStream defaultStream;

   //The output stream on which to output warnings and errors
   extern LoggingStream* errorStream;

	enum StreamType
	{
		file,
		console,
		socket //add more as needed
	};

   enum ErrorLevel
   {
       CORE_FATAL_ERROR,
       CORE_ERROR,
       CORE_WARNING,
       CORE_NOTE
   };
}