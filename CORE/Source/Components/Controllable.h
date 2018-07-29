#pragma once
#include "Events.h"
#include "Event.h"

#include <list>

class Entity;

class Controllable
{
public:
	virtual void handle(Event e) = 0;
	virtual void receive(Event e);

	virtual void condReceive(Event e, Entity* ancestor);

	virtual void update();

protected:
	std::list<Event> eventQueue;
};