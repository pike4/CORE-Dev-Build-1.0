#include "Controllable.h"
#include "Room.h"
#include <vector>

Controllable::Controllable(std::vector<Controllable*>* controllableVector)
{
	controllableVector->push_back(this);
}

Controllable::Controllable(Room* room)
{
	addTo(room);
}

void Controllable::addTo(Room* room)
{
	if (room != NULL)
	{
		room->controllableVector->push_back(this);
	}
}

Controllable::Controllable() {}
Controllable::Controllable(Controllable&) {}