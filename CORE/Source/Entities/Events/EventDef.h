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

   EventDef(std::string nam, std::vector<PrimitiveType> form)
   {
      name = nam;
      format = form;
   }

   EventDef(XMLNode def)
   {
       if (def.null())
       {
           CORE_SystemIO::error("Could not construct EventDef from null XMLNode*");
           return;
       }

       name = def.getName();

       std::vector<XMLNode> newFormat = def.getChildren();

       for (unsigned int i = 0; i < newFormat.size(); i++)
       {
           XMLNode cur = newFormat[i];

           PrimitiveType newType = CORE_TypeTraits::getPrimitiveType(cur.getName());

           if (newType != CORE_TypeTraits::_errorType)
               format.push_back(newType);
           else
               CORE_SystemIO::error("Event " + name + " format contains error type");
       }
   }
};