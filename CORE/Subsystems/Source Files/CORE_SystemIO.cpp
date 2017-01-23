#include "CORE_SystemIO.h"
#include "LogFileStream.h"

#include <string>

namespace CORE_SystemIO
{
#pragma region Private Helper Functions
	bool peekStream(std::string name)
	{
		return (streams.find(name) != streams.end());
	}
#pragma endregion

	std::map<std::string, LoggingStream*> streams;

	void print(std::string message, std::string stream)
	{
		if (peekStream(stream))
		{
			streams[stream]->log(message);
		}

		else
		{
			//error: stream does not exist
		}
	}

	//TODO: not fully implemented
	void openLogFile(std::string name, std::string path)
	{
		if (!name.empty() && !path.empty() && !peekStream(name))
		{
			streams[name] = new LogFileStream();
		}
	}

	//TODO: Open a new output screen for printing output to the screen
	void openOutputConsole(std::string name)
	{

	}

	//TODO: open developer console for receiving and printing results from developer commands
	void openDeveloperConsole()
	{

	}

	void openLoggingStream(std::string name, int type)
	{
		if (streams.find(name) == streams.end())
		{
			switch (type)
			{
			case file:
				//Need path
				break;

			case console:
				//Need nothing
				break;

			case socket:
				//Need address
				break;
			}
		}

		else
		{
			//error: stream already open
		}
	}

	void closeStream(std::string name)
	{
		if (peekStream(name))
		{
			streams[name]->close();
			streams.erase(name);
		}

		else
		{
			//error: stream does not exist
		}
	}
}