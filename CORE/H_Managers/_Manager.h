#pragma once
#include "Commands.h"
#include "ManagerArgs.h"
#include <queue>

class Manager
{
public:

	enum StateList : int
	{
		CORE_RUNNING,
		CORE_IN_MENU,
		CORE_PAUSED,
		CORE_BLOCKING
	};

	virtual void update() = 0;

	virtual bool start() = 0;

	virtual bool start(ManagerArgs*) = 0;

	virtual void stop() = 0;

	virtual void updateRunning() = 0;

	virtual void updateInMenu() = 0;

	virtual void updatePaused() = 0;

	virtual void updateBlocking() = 0;

	virtual void goToState(int) = 0;

	virtual void goToRunning() = 0;

	virtual void goToInMenu() = 0;

	virtual void goToPaused() = 0;

	virtual void goToBlocking() = 0;

	virtual void changeState(int state) = 0;

	static void enqueue(Command* command);

	static void updateQueue();

protected:
	static std::queue <Command*> mQueue;
};