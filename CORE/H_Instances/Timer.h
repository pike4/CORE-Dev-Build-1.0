#include "SDL.h"

class Timer
{
public:
	void updateTime();

	bool hasElapsed(Uint32 ms);

	Uint32 elapsed();
	
	Timer();

private:
	Uint32 prev;
};