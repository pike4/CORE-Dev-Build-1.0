#include "EventHandler.h"
#include "Entity.h"

#include "CORE_SystemIO.h"

void EventHandler::handleEvent(std::vector<EventArg> arguments)
{
   if (format.size() != arguments.size())
   {
      CORE_SystemIO::error("Event handler " + name + " was called with " 
         + std::to_string(arguments.size()) + " arguments but is meant to be called with " 
         + std::to_string(format.size()));
      return;
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

void EventHandler::registerOwner(Entity* owner)
{
   return;
}