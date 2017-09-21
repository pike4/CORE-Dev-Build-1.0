#include "Timer.h"
#include "Room.h"
#include "Environment.h"
#include "MenuSystem.h"
#include "Node.h"

#include <vector>
#pragma once

namespace CORE
{
	void start();
	void update();
	void stop();

#pragma region Room Transitions

	void goToRoom(Room* room);
	void goToRoomInCurrentEnvironment(std::string roomName);

	void goToEnvironment(std::string environmentName);

#pragma endregion

#pragma region GUI Transtions

	void goToGUI(MenuScreen* gui);
	void goToGUIInCurrentMenuSystem(std::string guiName);
	void addGUILayerFromCurrentMenuSystem(std::string guiName);

	void addMenuScreenLayer(MenuScreen* gui);
	void removeMenuScreenLayer(MenuScreen* gui);

	void togglePauseMenu(std::string guiName);

	void goToMenuSystem(std::string systemName);
#pragma endregion

	void handle(Event e);

	extern Environment* currentEnvironment;
	extern Room* currentRoom;
	extern std::vector<MenuScreen*> currentMenuScreens;
	extern MenuSystem* currentMenuSystem;
	extern MenuScreen* currentMenuScreen;
	
	extern Timer frameTimer;
	
	extern int lag;
	extern int msPerFrame;

	extern bool quit;
};