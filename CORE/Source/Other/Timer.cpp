#include "Timer.h"
#include "SDL.h"

void Timer::updateTime()
{
	prev = SDL_GetTicks();
}

void Timer::pause()
{
	blockedAt = SDL_GetTicks();
}

void Timer::resume()
{
	prev += SDL_GetTicks() - blockedAt;
}

//Returns whether or not the given time has elapsed since update
bool Timer::hasElapsed(Uint32 ms)
{
	return ms < elapsed();
}

//Returns time since Timer last updated in milliseconds
Uint32 Timer::elapsed()
{
	return (SDL_GetTicks() - prev);
}

Timer::Timer()
{
	prev = SDL_GetTicks();
	blockedAt = 0;
}