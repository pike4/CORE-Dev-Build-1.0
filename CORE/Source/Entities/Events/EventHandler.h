#pragma once

#include "EventDef.h"
#include "Event.h"


#include "CORE_TypeTraits.h"

#include <vector>
#include <string>

using CORE_TypeTraits::PrimitiveType;
class Entity;

class EventHandler
{
public:
   virtual void handleEvent(std::vector<EventArg> args);

   virtual void registerOwner(Entity* owner);

   virtual EventHandler* spawnCopy();

   bool matches(EventDef e);

   std::vector<PrimitiveType> format;
   std::string name;
};