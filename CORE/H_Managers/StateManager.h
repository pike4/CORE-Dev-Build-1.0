#include "Globals.h"
#include "Timer.h"
#include "_Manager.h"
#include "Room.h"

#include "Environment.h"
#include "MenuSystem.h"

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

	static void goToRoom(Room* room);
	static void goToRoomInCurrentEnvironment(std::string roomName);

	static void goToEnvironment(std::string environmentName);

	static void goToGUI(MenuScreen* gui);
	static void goToGUIInCurrentMenuSystem(std::string guiName);

	static void togglePauseMenu(std::string guiName);

	static void goToMenuSystem(std::string systemName);

	static std::map<std::string, Environment*> environments;
	static std::map<std::string, MenuSystem*> menuSystems;

	static Environment* currentEnvironment;
	static Room* currentRoom;
	static MenuSystem* currentMenuSystem;
	static MenuScreen* currentMenuScreen;

	static Timer frameTimer;

	static int lag;
	static int msPerFrame;

private:
	
};