#include "CORE.h"
#include "CORE_Graphics.h"
#include "CORE_Audio.h"
#include "CORE_Devices.h"
#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "CORE_LuaInterface.h"
#include "Entity.h"

namespace CORE
{
	int globalID;
	std::map<int, Entity*> objects;

	void start()
	{
		quit = false;

		CORE_LuaInterface::initialize();

		if (!CORE_Graphics::start())
			printf("Video manager failed to start");

		if (!CORE_Audio::start())
			printf("Sound manager failed to start");

		CORE_Devices::start();
		CORE_Resources::start();

		lag = 0;
		msPerFrame = 17;
		globalID = 0;
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

	void handle(Event e)
	{
		CORE_Graphics::handle(e);
		CORE_Audio::handle(e);
		CORE_Resources::handle(e);

		if (currentRoom != NULL)
		{
			currentRoom->handle(e);
		}

		if (!currentMenuScreens.empty() && currentMenuScreens.back() != NULL)
		{
			currentMenuScreens.back()->handle(e);
		}
	}

	void receive(Event e)
	{
		if (currentRoom != NULL)
		{
			currentRoom->receive(e);
		}

		if (!currentMenuScreens.empty() && currentMenuScreens.back() != NULL)
		{
			currentMenuScreens.back()->receive(e);
		}
	}

	void direct(Event e, Entity* ancestor)
	{
		if (currentRoom)
		{
			currentRoom->direct(e, ancestor);
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

		else 
		{
			CORE_SystemIO::error("Room " + roomName + " not found");
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

	Entity* getObjectByID(int ID)
	{
		Entity* ret = NULL;

		if (objects.find(ID) != objects.end()) {
			ret = objects[ID];
		}
		else {
			CORE_SystemIO::error("Object " + std::to_string(ID) + " could not be found");
		}

		return ret;
	}

	void removeObject(int ID)
	{
		if (objects.find(ID) != objects.end()) {
			objects.erase(ID);
		}
		else {
			CORE_SystemIO::error("Object " + std::to_string(ID) + " does not be deleted");
		}
	}

	int storeObject(Entity* object)
	{
		int newID = globalID++;

		objects[newID] = object;

		return newID;
	}

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