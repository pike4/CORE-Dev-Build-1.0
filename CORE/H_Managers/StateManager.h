#include "Globals.h"
#include "Timer.h"

#pragma once

class StateManager
{
public:

	enum StateList: int
	{
		CORE_LOADING,
		CORE_MAIN_MENU,
		CORE_IN_GAME,
		CORE_PAUSED
	};

	static void start();

	static void update();

	static void stop();

	static Timer frameTimer;

	static int lag;
	static int msPerFrame;


private:
	
};