#include "ObjectManager.h"
#include "SystemManager.h"
#include "CollisionManager.h"

#include "Globals.h"

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

private:
	
};