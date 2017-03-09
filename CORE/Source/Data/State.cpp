#include "State.h"

void State::addData(std::string name, Data* newData)
{
   if (!variableExists(name))
   {
      publicData[name] = newData;
   }

   else
   {
      CORE_SystemIO::error("Variable " + name + " already exists");
   }
}