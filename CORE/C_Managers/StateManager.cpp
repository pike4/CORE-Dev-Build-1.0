#include "StateManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "EventManager.h"
#include "SystemManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Commands.h"

#include "GameObject.h"


void StateManager::start()
{
	quit = false;

	changeState(CORE_RUNNING);

	if (!VideoManager::start())
		printf("Video manager failed to start");

	if (!AudioManager::start())
		printf("Sound manager failed to start");

	SystemManager::start();

	ObjectManager::start();

	EventManager::start();

	frameTimer = Timer();
	lag = 0;
	msPerFrame = 14;
}

void StateManager::update()
{
	updateQueue();
	lag += frameTimer.elapsed();
	EventManager::update();

	while (lag > msPerFrame)
	{
		SystemManager::update();
		ObjectManager::update();

		lag -= msPerFrame;
	}

	frameTimer.updateTime();
	VideoManager::update();
}

void StateManager::stop()
{

}

void StateManager::handleEvent(int eventCode, int posOrNeg, int x, int y)
{
	VideoManager::handleEvent(eventCode, posOrNeg, x, y);
	AudioManager::handleEvent(eventCode, posOrNeg, x, y);
	ObjectManager::handleEvent(eventCode, posOrNeg, x, y);
	SystemManager::handleEvent(eventCode, posOrNeg, x, y);
	//EventManager::handleEvent(eventCode, posOrNeg, x, y);


	if (currentRoom != NULL)
	{
		currentRoom->handleInput(eventCode, posOrNeg, x, y);
	}

	if (!currentMenuScreens.empty() && currentMenuScreens.back() != NULL)
	{
		currentMenuScreens.back()->handleInput(eventCode, posOrNeg, x, y);
	}
}

#pragma region State Transitions
void StateManager::changeState(int state)
{
	switch (state)
	{
	case CORE_RUNNING:
		goToRunning();
		break;
	case CORE_IN_MENU:
		goToInMenu();
		break;
	case CORE_PAUSED:
		goToPaused();
		break;
	case CORE_BLOCKING:
		goToBlocking();
		break;
	}
}

void StateManager::goToRunning()
{
	VideoManager::goToRunning();
	AudioManager::goToRunning();
	ObjectManager::goToRunning();
	SystemManager::goToRunning();
}

void StateManager::goToInMenu()
{
	VideoManager::goToInMenu();
	AudioManager::goToInMenu();
	ObjectManager::goToInMenu();
	SystemManager::goToInMenu();
}

void StateManager::goToPaused()
{
	VideoManager::goToPaused();
	AudioManager::goToPaused();
	ObjectManager::goToPaused();
	SystemManager::goToPaused();
}

void StateManager::goToBlocking()
{
	VideoManager::goToBlocking();
	AudioManager::goToBlocking();
	ObjectManager::goToBlocking();
	SystemManager::goToBlocking();
}
#pragma endregion

#pragma region Room and Environment transitions
void StateManager::goToRoom(Room* room)
{
	if (room == NULL)
	{
		return;
	}
	currentRoom = room;
	ObjectManager::currentRoom = room;
	VideoManager::currentRoom = room;


	ObjectManager::setObjectVector(room->objectVector);
	ObjectManager::setUpdateVector(room->updateVector);
}

void StateManager::goToRoomInCurrentEnvironment(std::string roomName)
{
	if (currentEnvironment != NULL && !roomName.empty())
	{
		goToRoom(currentEnvironment->rooms[roomName]);
	}
}

void StateManager::goToEnvironment(std::string environmentName)
{
	if (environments.find(environmentName) != environments.end())
	{
		currentEnvironment = environments[environmentName];
	}

	else
	{
		printf("State Manager could not find requested Environment: %s\n", environmentName.c_str());
	}
}
#pragma endregion

#pragma region GUI transitions
void StateManager::goToGUI(MenuScreen* gui)
{
	currentMenuScreens.push_back(gui);
}

void StateManager::goToGUIInCurrentMenuSystem(std::string guiName)
{
	if (currentMenuSystem != NULL && !guiName.empty())
	{
		goToGUI(currentMenuSystem->menus[guiName]);
	}
}

void StateManager::addMenuScreenLayer(MenuScreen* gui)
{
	currentMenuScreens.push_back(gui);
}

void StateManager::removeMenuScreenLayer(MenuScreen* gui)
{
	if (!currentMenuScreens.empty())
	{
		currentMenuScreens.pop_back();
	}
}

void StateManager::goToMenuSystem(std::string menuSystemName)
{
	if (menuSystems.find(menuSystemName) != menuSystems.end())
	{
		currentMenuSystem = menuSystems[menuSystemName];
	}

	else
	{
		printf("State Manager could not find requested Menu System: %s\n", menuSystemName.c_str());
	}
}

void StateManager::togglePauseMenu(std::string guiName)
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
int StateManager::lag;
int StateManager::msPerFrame;

Timer StateManager::frameTimer;

std::map<std::string, Environment*> StateManager::environments;
std::map<std::string, MenuSystem*> StateManager::menuSystems;

std::map<std::string, GameObject*> StateManager::prototypes;

Environment* StateManager::currentEnvironment;
Room* StateManager::currentRoom;
std::vector<MenuScreen*> StateManager::currentMenuScreens;
MenuSystem* StateManager::currentMenuSystem;
MenuScreen* StateManager::currentMenuScreen;
#pragma endregion

void ChangeStateCommand::execute()
{
	StateManager::changeState(state);
}