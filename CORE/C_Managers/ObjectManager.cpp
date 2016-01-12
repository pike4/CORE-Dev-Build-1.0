#include "ObjectManager.h"
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

std::vector <Updatable*> ObjectManager::UpdateVector;
std::vector <BaseObject*> ObjectManager::BaseObjectVector;