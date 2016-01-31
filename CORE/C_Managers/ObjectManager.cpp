#include "ObjectManager.h"
#include "Commands.h"
#include <vector>


#pragma region Manager Implementation Methods
void ObjectManager::update()
{
	for (int x = 0; x < UpdateVector.size(); x++)
	{
		UpdateVector[x]->update();
	}
}


#pragma endregion

void ObjectManager::add(Thing* E)
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

Mobile* ObjectManager::player;


//Redefine to change what the ObjectManager does in response to key presses
#pragma region ObjectManagerCommands
void walkForwardCommand::execute()
{
	printf("up");
	ObjectManager::player->setYVel(-1);
}

void walkBackwardCommand::execute()
{
	printf("Down");
	ObjectManager::player->setYVel(1);
}

void walkLeftCommand::execute()
{
	printf("left");
	ObjectManager::player->setXVel(1);
}

void walkRightCommand::execute()
{
	printf("right");
	ObjectManager::player->setXVel(1);
}
#pragma endregion