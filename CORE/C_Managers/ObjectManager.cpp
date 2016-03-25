#include "ObjectManager.h"
#include "Commands.h"
#include "StateManager.h"
#include <vector>


#pragma region Manager Implementation Methods
void ObjectManager::update()
{
	switch (state)
	{
	case StateManager::CORE_RUNNING:
		quadTree.update();

		for (int x = 0; x < UpdateVector.size(); x++)
		{
			UpdateVector[x]->update();
		}
		break;
	case StateManager::CORE_IN_MENU:
		break;

	case StateManager::CORE_PAUSED:
		break;

	case StateManager::CORE_BLOCKING:
		break;
	}
}

void ObjectManager::start()
{
}

#pragma endregion

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

std::vector <Updatable*> ObjectManager::UpdateVector;
std::vector <BaseObject*> ObjectManager::BaseObjectVector;
QuadTree ObjectManager::quadTree = QuadTree(0, 0, 0, 640, 320, NULL);
int ObjectManager::state;

Player* ObjectManager::player;


//Redefine to change what the ObjectManager does in response to key presses
#pragma region ObjectManagerCommands
void walkForwardCommand::execute()
{
	ObjectManager::player->walkUp(type);
}

void walkBackwardCommand::execute()
{
	ObjectManager::player->walkDown(type);
}

void walkLeftCommand::execute()
{
	//ObjectManager::player->walkLeft(type);
}

void walkRightCommand::execute()
{
	//ObjectManager::player->walkRight(type);
}
#pragma endregion