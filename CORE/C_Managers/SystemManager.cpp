#include "SDL.h"
#include "SystemManager.h"
#include "ObjectManager.h"
#include "StateManager.h"

void SystemManager::start()
{
	curTime = 0;
	prevTime = 0;
	totalTime = 0;
	totalFrames = 0;
	outputInterval = 2000;
	FPSTimer = *new Timer();
}

void SystemManager::update()
{
	switch (state)
	{
	case StateManager::StateList::CORE_RUNNING:
		curTime = SDL_GetTicks();
		//updateTime();
		updateQueue();
		updateFPS();
		printFPS();
		break;

	case StateManager::StateList::CORE_IN_MENU:
		break;

	case StateManager::StateList::CORE_BLOCKING:
		break;

	case StateManager::StateList::CORE_PAUSED:
		break;
	}
	
}

void SystemManager::changeState(int state)
{
	SystemManager::state = state;
}

void SystemManager::setoutputInterval(Uint32 ms)
{
	outputInterval = ms;
}

void SystemManager::updateTime()
{
	FPSTimer.updateTime();
}

//To check if the specified time has passed since previous update
bool SystemManager::hasElapsed(Uint32 ms)
{
	return ms >= (curTime - prevTime);
}

//Increments the total number of frames since the FPS was last calculated
void SystemManager::updateFPS()
{
	totalFrames++;
}

//Calculates and prints the average FPS over the time interval specified in outputInterval
void SystemManager::printFPS()
{
	if (FPSTimer.hasElapsed(outputInterval))
	{
		int y = FPSTimer.elapsed();
		printf("FPS: %f \t", 1000 * (float) totalFrames/FPSTimer.elapsed());

		printObjectCount();

		FPSTimer.updateTime();
		totalFrames = 0;

		printFPS();
	}
}

void SystemManager::printObjectCount()
{
	if (FPSTimer.hasElapsed(outputInterval))
	{
		std::vector <BaseObject*>* HH = ObjectManager::getObjectVector();
		printf("Object Count: \t %i\n", HH->size());
	}
}

void SystemManager::flush()
{
	
}

Uint32 SystemManager::curTime;
Uint32 SystemManager::prevTime;
Uint32 SystemManager::outputInterval;
Uint32 SystemManager::totalTime;
Uint32 SystemManager::totalFrames;
Timer SystemManager::FPSTimer;
string SystemManager::buffer;
int SystemManager::state;