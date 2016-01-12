#include "StateManager.h"
#include "VideoManager.h"
#include "SoundManager.h"
#include "EventManager.h"

void StateManager::start()
{
	quit = false;

	if (!VideoManager::start())
		printf("Video manager failed to start");

	if (!SoundManager::start())
		printf("Sound manager failed to start");
}

void StateManager::update()
{
	EventManager::update();
	ObjectManager::update();
	VideoManager::update();
}

void StateManager::stop()
{
	
}