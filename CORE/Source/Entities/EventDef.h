#pragma once
#include "CORE_TypeTraits.h"

#include <string>
#include <vector>

//Defines the argument format of a single event type
struct EventDef
{
   std::string name;
   std::vector<CORE_TypeTraits::PrimitiveType> format;
};