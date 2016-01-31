#include "StateManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "EventManager.h"
#include "SystemManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

void StateManager::start()
{
	quit = false;

	if (!VideoManager::start())
		printf("Video manager failed to start");

	if (!AudioManager::start())
		printf("Sound manager failed to start");

	SystemManager::start();

	EventManager::start();

	frameTimer = Timer();
	lag = 0;
	msPerFrame = 16;
}

void StateManager::update()
{
	lag += frameTimer.elapsed();
	EventManager::update();

	while (lag > msPerFrame)
	{
		SystemManager::update();
		ObjectManager::update();

		lag -= msPerFrame;
	}

	frameTimer.updateTime();

	VideoManager::update();
}

void StateManager::stop()
{
	
}

int StateManager::lag;
int StateManager::msPerFrame;

Timer StateManager::frameTimer;