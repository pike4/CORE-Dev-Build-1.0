#pragma once
#include "Node.h"

#include "CORE_TypeTraits.h"
#include "CORE_SystemIO.h"

#include <string>
#include <vector>

using CORE_TypeTraits::PrimitiveType;

//Defines the argument format of a single event type
struct EventDef
{
   std::string name;
   std::vector<PrimitiveType> format;

   EventDef() {};

   EventDef(Node* def)
   {
       if (!def)
       {
           CORE_SystemIO::error("Could not construct EventDef from null Node*");
           return;
       }

       name = def->getName();

       std::vector<Node*>* newFormat = def->getChildren();

       for (int i = 0; i < newFormat->size(); i++)
       {
           Node* cur = (*newFormat)[i];

           PrimitiveType newType = CORE_TypeTraits::getPrimitiveType(cur->getName());

           if (newType != CORE_TypeTraits::_errorType)
               format.push_back(newType);
           else
               CORE_SystemIO::error("Event " + name + " format contains error type");
       }
   }
};