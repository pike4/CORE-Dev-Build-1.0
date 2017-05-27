#include "CORE_SystemIO.h"
#include "LogFileStream.h"
#include "LogWindowStream.h"

#include <string>

namespace CORE_SystemIO
{
#pragma region Private Helper Functions
   void start()
   {
      //TODO figure out how to do startup parameters
      //if ( theUserWantsASpecificFileStreamForErrorsOrSomething)
      //errorStream = new LogFileStream(filename)
      //else
      errorStream = new LogWindowStream();
   }

   bool peekStream(std::string name)
   {
      return (streams.find(name) != streams.end());
   }
#pragma endregion

#pragma region Stream Management
   //TODO: not fully implemented
   void openLogFile(std::string name, std::string path)
   {
      if (!name.empty() && !path.empty() && !peekStream(name))
      {
         streams[name] = new LogFileStream(path);
         
         if(!streams[name]->open())
         {
            error("The path " + path + " not accessible. Output stream: " + name + " will default to stdout");
            delete streams[name];

            streams[name] = new LogWindowStream();
         }
      }
   }

   //TODO: Open a new output screen for printing output to the screen
   void openOutputConsole(std::string name)
   {
      if (!name.empty() && !peekStream(name))
      {
         streams[name] = new LogWindowStream();
      }
   }

   //TODO: open developer console for receiving and printing results from developer commands
   void openDeveloperConsole()
   {

   }

   //Open a file or window stream of the given type
   void openLoggingStream(std::string name, StreamType type)
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
         error("stream " + name + " already open");
      }
   }

    //Close the stream of the given name
   void closeStream(std::string name)
   {
      if (peekStream(name))
      {
         streams[name]->close();
         streams.erase(name);
      }
      
      else
      {
         error("stream " + name + " does not exist");
      }
   }
#pragma endregion

#pragma region Stream Output

   void print(std::string message)
	{
		defaultStream.log(message);
		defaultStream.flush();
	}
    
   void print(std::string message, std::string stream)
	{
		if (peekStream(stream))
		{
			streams[stream]->log(message);
		}

		else
		{
			//error: stream does not exist
			print(message);
			error("stream " + stream + " does not exist");
		}
	}

   void error(std::string errorMessage)
   {
      if (errorStream)
      {
         errorStream->log(errorMessage);
         
         //TODO: need another thread for flushing output streams
         errorStream->flush();
      }
      
      else
      {
         defaultStream.log(errorMessage);
      }
   }
#pragma endregion

#pragma region Resources
   std::map<std::string, LoggingStream*> streams;

   LogWindowStream defaultStream;

   //The output stream on which to output warnings and errors
   LoggingStream*  errorStream;
#pragma endregion
}