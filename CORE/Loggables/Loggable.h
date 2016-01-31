#include "Timer.h"
#include <string>

class Loggable
{
public:
	void speak();

	void addToBuffer();

	static bool loggerOn;



private:

	//Whether or not the information will be logged or printed to the console
	bool isLogging;
	bool isPrinting;
	Uint32 outputInterval;
	Timer loggingTimer;
	std::string tag;
};