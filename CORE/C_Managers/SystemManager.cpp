#include "SDL.h"
#include "SystemManager.h"
#include "ObjectManager.h"

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
	curTime = SDL_GetTicks();
	//updateTime();
	updateQueue();
	updateFPS();
	printFPS();
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
		printf("Object Count: \t %i", HH->size());
	}
}

Uint32 SystemManager::curTime;
Uint32 SystemManager::prevTime;
Uint32 SystemManager::outputInterval;
Uint32 SystemManager::totalTime;
Uint32 SystemManager::totalFrames;
Timer SystemManager::FPSTimer;