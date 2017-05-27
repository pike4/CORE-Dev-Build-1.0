#include "CORE.h"
#include "CORE_Graphics.h"
#include "CORE_Audio.h"
#include "CORE_Devices.h"
#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "Entity.h"

namespace CORE
{
	void start()
	{
		quit = false;

		if (!CORE_Graphics::start())
			printf("Video manager failed to start");

		if (!CORE_Audio::start())
			printf("Sound manager failed to start");

		CORE_Devices::start();

		lag = 0;
		msPerFrame = 17;
	}

	void update()
	{
		lag += frameTimer.elapsed();
		CORE_Devices::update();

		while (lag > msPerFrame)
		{
			if(currentRoom)
				currentRoom->update();

			lag -= msPerFrame;
		}

		frameTimer.updateTime();
		CORE_Graphics::update();
	}

	void stop()
	{

	}

	void handleEvent(int eventCode, int posOrNeg, int x, int y)
	{
		CORE_Graphics::handleEvent(eventCode, posOrNeg, x, y);
		CORE_Audio::handleEvent(eventCode, posOrNeg, x, y);
		CORE_Resources::handleEvent(eventCode, posOrNeg, x, y);

		if (currentRoom != NULL)
		{
			currentRoom->handleInput(eventCode, posOrNeg, x, y);
		}

		if (!currentMenuScreens.empty() && currentMenuScreens.back() != NULL)
		{
			currentMenuScreens.back()->handleInput(eventCode, posOrNeg, x, y);
		}
	}

#pragma region Room and Environment transitions
	void goToRoom(Room* room)
	{
		if (room)
		{
			currentRoom = room;
			CORE_Graphics::currentRoom = room;
		}
	}

	void goToRoomInCurrentEnvironment(std::string roomName)
	{
		if (currentEnvironment != NULL && !roomName.empty())
		{
			goToRoom(currentEnvironment->rooms[roomName]);
		}
	}

	void goToEnvironment(std::string environmentName)
	{
		Environment* tempEnv = CORE_Resources::getEnvironment(environmentName);

		if (tempEnv)
		{
			currentEnvironment = tempEnv;
		}

		else
		{
			printf("State Manager could not find requested Environment: %s\n", environmentName.c_str());
		}
	}
#pragma endregion

#pragma region GUI transitions
	void goToGUI(MenuScreen* gui)
	{
		currentMenuScreens.clear();
		currentMenuScreens.push_back(gui);
	}

	void goToGUIInCurrentMenuSystem(std::string guiName)
	{
		if (currentMenuSystem != NULL && !guiName.empty())
		{
			goToGUI(currentMenuSystem->menus[guiName]);
		}
	}

	void addGUILayerFromCurrentMenuSystem(std::string guiName)
	{
		if (currentMenuSystem != NULL && !guiName.empty())
		{
			addMenuScreenLayer(currentMenuSystem->menus[guiName]);
		}
	}

	void addMenuScreenLayer(MenuScreen* gui)
	{
		if (gui != NULL)
		{
			currentMenuScreens.push_back(gui);
		}

		else
		{
			//TODO log error
			printf("Attempted to load null menu\n");
		}
	}

	void removeMenuScreenLayer(MenuScreen* gui)
	{
		if (!currentMenuScreens.empty())
		{
			currentMenuScreens.pop_back();
		}
	}

	void goToMenuSystem(std::string menuSystemName)
	{
		MenuSystem* tempMenu = CORE_Resources::getMenuSystem(menuSystemName);

		if (tempMenu)
		{
			currentMenuSystem = tempMenu;
		}

		else
		{
			printf("State Manager could not find requested Menu System: %s\n", menuSystemName.c_str());
		}
	}

	void togglePauseMenu(std::string guiName)
	{
		if (currentMenuScreen != NULL)
		{
			if (!strcmp(currentMenuScreen->name.c_str(), guiName.c_str()))
			{
				goToGUI(NULL);
			}

			else if (!guiName.empty())
			{
				goToGUIInCurrentMenuSystem(guiName);
			}
		}

		else
		{
			if (!guiName.empty())
			{
				goToGUIInCurrentMenuSystem(guiName);
			}
		}

	}
#pragma endregion


#pragma region Static data members
	int lag;
	int msPerFrame;

	Timer frameTimer;

	Environment* currentEnvironment;
	Room* currentRoom;
	std::vector<MenuScreen*> currentMenuScreens;
	MenuSystem* currentMenuSystem;
	MenuScreen* currentMenuScreen;

	bool quit;
#pragma endregion
}