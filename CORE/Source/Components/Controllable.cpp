#include "Controllable.h"

void Controllable::receive(Event e)
{
	eventQueue.push_back(e);
}