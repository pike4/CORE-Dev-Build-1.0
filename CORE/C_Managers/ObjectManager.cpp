#include "ObjectManager.h"
#include "Commands.h"
#include "StateManager.h"
#include <vector>


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
	quadTree.update();

	for (int x = 0; x < UpdateVector.size(); x++)
	{
		UpdateVector[x]->update();
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



void ObjectManager::start()
{
	
}

#pragma endregion

#pragma region Object Management

void ObjectManager::add(BaseObject* E)
{
	BaseObjectVector.push_back(E);
}

void ObjectManager::addUpdatable(Updatable* E)
{
	UpdateVector.push_back(E);
}

void ObjectManager::removeUpdatable(Updatable* E)
{
	for (int x = 0; x < UpdateVector.size(); x++)
	{
		if (UpdateVector[x] == E)
		{
			UpdateVector.erase(UpdateVector.begin() + x);
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
	return BaseObjectVector.size();
}

std::vector <BaseObject*>* ObjectManager::getObjectVector()
{
	return &BaseObjectVector;
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

std::vector <Updatable*> ObjectManager::UpdateVector;
std::vector <BaseObject*> ObjectManager::BaseObjectVector;
QuadTree ObjectManager::quadTree = QuadTree(0, 0, 0, 640, 480, NULL);
SDL_Renderer* ObjectManager::testRenderer;
int ObjectManager::state;
Player* ObjectManager::player;

//Redefine to change what the ObjectManager does in response to key presses
#pragma region ObjectManagerCommands
void walkForwardCommand::execute()
{
	//ObjectManager::player->walkUp(type);
}

void walkBackwardCommand::execute()
{
	//ObjectManager::player->walkDown(type);
}

void walkLeftCommand::execute()
{
	//ObjectManager::player->walkLeft(type);
}

void walkRightCommand::execute()
{
	//ObjectManager::player->walkRight(type);
}

void HandleMouseClickCommand::execute()
{
	
}
#pragma endregion
