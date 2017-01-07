#include "Globals.h"
#include "Timer.h"
#include "_Manager.h"
#include "Room.h"
#include <vector>
#include "Environment.h"
#include "MenuSystem.h"
#include "Definer.h"
#pragma once

class StateManager :  public Manager
{
public:

	static void start();
	static void update();
	static void stop();


#pragma region Global State Transitions
	static void changeState(int state);
	static void goToBlocking();
	static void goToPaused();
	static void goToRunning();
	static void goToInMenu();
#pragma endregion

#pragma region Room Transitions

	static void goToRoom(Room* room);
	static void goToRoomInCurrentEnvironment(std::string roomName);

	static void goToEnvironment(std::string environmentName);

#pragma endregion

#pragma region GUI Transtions

	static void goToGUI(MenuScreen* gui);
	static void goToGUIInCurrentMenuSystem(std::string guiName);
	static void addGUILayerFromCurrentMenuSystem(std::string guiName);

	static void addMenuScreenLayer(MenuScreen* gui);
	static void removeMenuScreenLayer(MenuScreen* gui);

	static void togglePauseMenu(std::string guiName);

	static void goToMenuSystem(std::string systemName);
#pragma endregion

	static void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

	static std::map<std::string, Environment*> environments;
	static std::map<std::string, MenuSystem*> menuSystems;
	static std::map<std::string, Entity*> prototypes;
	static std::map<std::string, Template*> templates;

	static Environment* currentEnvironment;
	static Room* currentRoom;
	static std::vector<MenuScreen*> currentMenuScreens;
	static MenuSystem* currentMenuSystem;
	static MenuScreen* currentMenuScreen;

	static Timer frameTimer;

	static int lag;
	static int msPerFrame;

private:
	
};