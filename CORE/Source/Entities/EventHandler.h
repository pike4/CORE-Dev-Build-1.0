#pragma once

#include "EventDef.h"

#include "CORE_TypeTraits.h"

#include <vector>
#include <string>

using CORE_TypeTraits::PrimitiveType;
class Entity;

class EventHandler
{
public:
   void handleEvent(std::vector<Data*>);

   bool matches(EventDef e);

   std::vector<PrimitiveType> format;
   std::string name;
};