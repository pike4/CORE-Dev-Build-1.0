#include "StateManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "EventManager.h"
#include "SystemManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Commands.h"


void StateManager::start()
{
	quit = false;

	changeState(CORE_RUNNING);

	if (!VideoManager::start())
		printf("Video manager failed to start");

	if (!AudioManager::start())
		printf("Sound manager failed to start");

	SystemManager::start();

	ObjectManager::start();

	EventManager::start();

	frameTimer = Timer();
	lag = 0;
	msPerFrame = 1000;
}

void StateManager::update()
{
	updateQueue();
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

void StateManager::changeState(int state)
{
	ObjectManager::state = state;
	VideoManager::state = state;
	AudioManager::state = state;
	EventManager::state = state;
	SystemManager::state = state;
}

void StateManager::stop()
{
	
}

int StateManager::lag;
int StateManager::msPerFrame;

Timer StateManager::frameTimer;

void ChangeStateCommand::execute()
{
	StateManager::changeState(state);
}