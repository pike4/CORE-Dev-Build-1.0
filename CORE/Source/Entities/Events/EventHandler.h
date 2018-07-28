#pragma once

#include "EventDef.h"
#include "Event.h"
#include "Controllable.h"


#include "CORE_TypeTraits.h"

#include <vector>
#include <string>

using CORE_TypeTraits::PrimitiveType;
class Entity;

class EventHandler : public Controllable
{
public:
   virtual void handle(Event e);

   virtual void registerOwner(Entity* owner);

   virtual EventHandler* spawnCopy();

   bool matches(EventDef e);

   std::vector<PrimitiveType> format;
   std::string name;
};