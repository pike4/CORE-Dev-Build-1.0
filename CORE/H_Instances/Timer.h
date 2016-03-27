#pragma once
#include "SDL.h"

class Timer
{
public:                                                                                                                                                                                                                                                              
	void updateTime();

	void resume();

	void pause();

	bool hasElapsed(Uint32 ms);

	Uint32 elapsed();
	
	Timer();

private:
	Uint32 prev;
	Uint32 blockedAt;
};