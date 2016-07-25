#include "Controllable.h"
#include "Room.h"
#include <vector>

Controllable::Controllable(std::vector<Controllable*>* controllableVector)
{
	controllableVector->push_back(this);
}

Controllable::Controllable(Room* room)
{
	room->controllableVector->push_back(this);
}

Controllable::Controllable() 
{}