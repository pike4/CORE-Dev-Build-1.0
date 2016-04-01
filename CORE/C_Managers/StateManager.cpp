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
	msPerFrame = 14;
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
	switch (state)
	{
	case CORE_RUNNING:
		goToRunning();
		break;
	case CORE_IN_MENU:
		goToInMenu();
		break;
	case CORE_PAUSED:
		goToPaused();
		break;
	case CORE_BLOCKING:
		goToBlocking();
		break;
	}
}

void StateManager::goToRunning()
{
	VideoManager::goToRunning();
	AudioManager::goToRunning();
	ObjectManager::goToRunning();
	SystemManager::goToRunning();
}

void StateManager::goToInMenu()
{
	VideoManager::goToInMenu();
	AudioManager::goToInMenu();
	ObjectManager::goToInMenu();
	SystemManager::goToInMenu();
}

void StateManager::goToPaused()
{
	VideoManager::goToPaused();
	AudioManager::goToPaused();
	ObjectManager::goToPaused();
	SystemManager::goToPaused();
}

void StateManager::goToBlocking()
{
	VideoManager::goToBlocking();
	AudioManager::goToBlocking();
	ObjectManager::goToBlocking();
	SystemManager::goToBlocking();
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