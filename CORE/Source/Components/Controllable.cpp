#include "Controllable.h"

void Controllable::receive(Event e)
{
	eventQueue.push_back(e);
}

void Controllable::condReceive(Event e, Entity* ancestor) {}

void Controllable::update()
{
	for each (Event ev in eventQueue)
	{
		handle(ev);
	}

	eventQueue.clear();
}