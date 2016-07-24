#include "ObjectManager.h"
#include "Commands.h"
#include "StateManager.h"
#include "MenuScreen.h"
#include "ControlTypes.h"
#include "ElementTypes.h"
#include <vector>
#include <map>


#pragma region Manager Implementation Methods

#pragma region Update Methods
void ObjectManager::update()
{
	updateQueue();

	switch (state)
	{
	case CORE_RUNNING:
		updateRunning();
		break;
	case CORE_IN_MENU:
		updateInMenu();
		break;

	case CORE_PAUSED:
		updatePaused();
		break;

	case CORE_BLOCKING:
		updateBlocking();
		break;
	}
}

void ObjectManager::updateRunning()
{
	if (currentRoom == NULL)
	{
		return;
	}

	if (currentRoom->quadTree != NULL)
	{
		currentRoom->quadTree->update();
	}

	currentRoom->update();

	for each(MenuScreen* menuScreen in StateManager::currentMenuScreens)
	{
		menuScreen->update();
	}
}

void ObjectManager::updateInMenu()
{

}

void ObjectManager::updatePaused()
{

}

void ObjectManager::updateBlocking()
{

}

#pragma endregion

void ObjectManager::handleEvent(int eventCode, int posOrNeg, int x, int y)
{

}


void ObjectManager::start()
{
	BaseObjectVector = new std::vector<BaseObject*>;
	UpdateVector = new std::vector<Updatable*>;

	gui = MenuScreen();
	currentGUI = &gui;
}

#pragma endregion

#pragma region Object Management

void ObjectManager::add(BaseObject* E)
{
	BaseObjectVector->push_back(E);
}

void ObjectManager::addUpdatable(Updatable* E)
{
	if (currentRoom == NULL || currentRoom->updateVector == NULL)
	{
		return;
	}
	currentRoom->updateVector->push_back(E);
}

void ObjectManager::removeUpdatable(Updatable* E)
{
	if (currentRoom == NULL || currentRoom->updateVector == NULL)
	{
		return;
	}

	for (int x = 0; x < currentRoom->updateVector->size(); x++)
	{
		if ((*currentRoom->updateVector)[x] == E)
		{
			currentRoom->updateVector->erase(currentRoom->updateVector->begin() + x);
			return;
		}
	}
}

void ObjectManager::addCollidable(Collidable* C)
{
	quadTree.insert(C);
}

int ObjectManager::getObjectCount()
{
	return BaseObjectVector->size();
}

std::vector <BaseObject*>* ObjectManager::getObjectVector()
{
	return BaseObjectVector;
}

std::vector<Updatable*>* ObjectManager::getUpdateVector()
{
	return UpdateVector;
}

void ObjectManager::setObjectVector(std::vector<BaseObject*>* newVector)
{
	BaseObjectVector = newVector;
}

void ObjectManager::setUpdateVector(std::vector<Updatable*>* newVector)
{
	UpdateVector = newVector;
}

#pragma endregion

#pragma region Object Management
Control* ObjectManager::generateControl(std::string controlType, pugi::xml_node node)
{
	const char* name = controlType.c_str();
	if (!strcmp(name, "Checkbox"))
	{
		return new CheckBoxButton(node);
	}

	else if (!strcmp(name, "DragArea.h"))
	{
		return new DragArea(node);
	}

	else if (!strcmp(name, "GUI_Area.h"))
	{
		return new GUI_Area(node);
	}

	else if (!strcmp(name, ""))
	{
		return NULL;
	}
}

VisibleElement* ObjectManager::generateVisibleElement(std::string controlType, pugi::xml_node node)
{
	const char* name = controlType.c_str();

	if (!strcmp(name, "TextElement"))
	{
		return new TextElement(node);
	}

	else if (!strcmp(name, "UpdatableTextElement.h"))
	{
		return new UpdatableTextElement(node);
	}

	else if (!strcmp(name, "ImageElement.h"))
	{
		return new ImageElement(node);
	}

	else
	{
		//TODO log error: unsupported type
		return NULL;
	}
}

BaseObject* ObjectManager::generateGameObject(std::string objectType, pugi::xml_node node, Room* room)
{
	if (!objectType.compare("Player"))
	{
		return new Player(node, room->objectVector, room->drawVector, room->updateVector, room->collidableVector, room->controllableVector);
	}

	else if (!objectType.compare(""))
	{

	}

	else
	{
		//TODO log error undefined type in xml file
	}
}

#pragma endregion

#pragma region State Transitions

void ObjectManager::goToRunning()
{
	state = CORE_RUNNING;
}

void ObjectManager::goToBlocking()
{
	state = CORE_BLOCKING;
}

void ObjectManager::goToInMenu()
{
	state = CORE_IN_MENU;
}

void ObjectManager::goToPaused()
{
	state = CORE_PAUSED;
}

#pragma endregion

#pragma region 
void ObjectManager::handleMouseClick()
{

}
#pragma endregion

std::vector <Updatable*>* ObjectManager::UpdateVector;
std::vector <BaseObject*>* ObjectManager::BaseObjectVector;

//std::map <MenuScreen*, char*> ObjectManager::guis;

QuadTree ObjectManager::quadTree = QuadTree(0, 0, 0, 640, 480, NULL);
SDL_Renderer* ObjectManager::testRenderer;
int ObjectManager::state;
Player* ObjectManager::player;
Cursor* ObjectManager::mouse;
MenuScreen ObjectManager::gui;
MenuScreen* ObjectManager::currentGUI;
Room* ObjectManager::currentRoom;
std::map<std::string, MenuSystem*> ObjectManager::menuSystems;

//Redefine to change what the ObjectManager does in response to key presses
#pragma region ObjectManagerCommands
void walkForwardCommand::execute()
{
	if (ObjectManager::player != NULL)
	{
		ObjectManager::player->walkUp(type);
	}
}

void walkBackwardCommand::execute()
{
	if (ObjectManager::player != NULL)
	{
		ObjectManager::player->walkDown(type);
	}
}

void walkLeftCommand::execute()
{
	if (ObjectManager::player != NULL)
	{
		ObjectManager::player->walkLeft(type);
	}
}

void walkRightCommand::execute()
{
	if (ObjectManager::player != NULL)
	{
		//ObjectManager::player->walkRight(type);
	}
}

void HandleMouseClickCommand::execute()
{
	if (ObjectManager::currentGUI != NULL && ObjectManager::mouse != NULL)
	{
		//ObjectManager::currentGUI->checkMouseDown();
	}
}

void HandleMouseMoveCommand::execute()
{
	if (ObjectManager::currentGUI != NULL && ObjectManager::mouse != NULL)
	{
//		ObjectManager::currentGUI->checkMousePos();
	}
}

void HandleMouseUpCommand::execute()
{
	if (ObjectManager::currentGUI != NULL && ObjectManager::mouse != NULL)
	{
	//	ObjectManager::currentGUI->checkMouseUp();
	}
}
#pragma endregion