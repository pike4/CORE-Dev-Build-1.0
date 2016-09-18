#include "Updatable.h"
#include "ObjectManager.h"
#include "Room.h"

Updatable::Updatable()
{
	ObjectManager::addUpdatable(this);
}

Updatable::Updatable(std::vector<Updatable*>* updateVector)
{
	updateVector->push_back(this);
}

Updatable::Updatable(Room* room)
{
	add(room);
}

void Updatable::add(Room* room)
{
	if (room != NULL)
	{
		room->updateVector->push_back(this);
	}
}

Updatable::~Updatable()
{
	ObjectManager::removeUpdatable(this);
}