#include "Globals.h"
#include "Timer.h"
#include "_Manager.h"

#pragma once

class StateManager :  public Manager
{
public:

	enum StateList: int
	{
		CORE_RUNNING,
		CORE_IN_MENU,
		CORE_PAUSED,
		CORE_BLOCKING
	};

	static void start();

	static void update();

	static void stop();

	static void changeState(int state);

	static Timer frameTimer;

	static int lag;
	static int msPerFrame;

private:
	
};