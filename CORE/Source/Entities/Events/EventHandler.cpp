#include "EventHandler.h"
#include "Entity.h"

#include "CORE_SystemIO.h"

void EventHandler::handle(Event e)
{
	if (format.size() != e.arguments.size())
	{
		CORE_SystemIO::error("Event handler " + name + " was called with "
			+ std::to_string(e.arguments.size()) + " arguments but is meant to be called with "
			+ std::to_string(format.size()));
		return;
	}
}

void EventHandler::condReceive(Event e, Entity* ancestor)
{
	if (owner && owner->isAncestor(ancestor))
	{
		handle(e);
	}
}

EventHandler* EventHandler::spawnCopy()
{
	return new EventHandler(*this);
}

bool EventHandler::matches(EventDef e)
{
	return (format == e.format);
}

void EventHandler::registerOwner(Entity* o)
{
	owner = o;
}