#pragma once
#include "Events.h"
#include "Event.h"

#include <list>


class Controllable
{
public:
	virtual void handle(Event e) = 0;
	virtual void receive(Event e);

protected:
	std::list<Event> eventQueue;
};