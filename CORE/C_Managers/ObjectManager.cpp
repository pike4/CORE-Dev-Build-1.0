#include "ObjectManager.h"
#include "Commands.h"
#include <vector>


#pragma region Manager Implementation Methods
void ObjectManager::update()
{
	quadTree.update();
	
	for (int x = 0; x < UpdateVector.size(); x++)
	{
		UpdateVector[x]->update();
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
	ObjectManager::player->walkLeft(type);
}

void walkRightCommand::execute()
{
	ObjectManager::player->walkRight(type);
}
#pragma endregion