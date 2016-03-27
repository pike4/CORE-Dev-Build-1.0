#include "Globals.h"
#include "Timer.h"
#include "_Manager.h"

#pragma once

class StateManager :  public Manager
{
public:



	static void start();

	static void update();

	static void stop();

	static void changeState(int state);
	static void goToBlocking();
	static void goToPaused();
	static void goToRunning();
	static void goToInMenu();

	static Timer frameTimer;

	static int lag;
	static int msPerFrame;

private:
	
};