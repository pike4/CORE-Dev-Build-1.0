#include "Timer.h"
#include "SDL.h"

void Timer::updateTime()
{
	prev = SDL_GetTicks();
}

//Returns time since Timer last updated in milliseconds
bool Timer::hasElapsed(Uint32 ms)
{
	return ms < elapsed();
}

Uint32 Timer::elapsed()
{
	int y = SDL_GetTicks();
	return (SDL_GetTicks() - prev);
}

Timer::Timer()
{
	prev = SDL_GetTicks();
}