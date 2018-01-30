#pragma once

#include "EventHandler.h"

struct lua_State;

class ScriptEventHandler : public EventHandler
{
public:
   ScriptEventHandler(Node* def);
   virtual EventHandler* spawnCopy();
   virtual void handleEvent(std::vector<EventArg>);

protected:
    lua_State* L;

   std::string scriptName;
   std::vector<std::string> argNames;

   void pushEntity(std::string name,  Entity* entity);
   void popEntity(std::string name, Entity* E1);
   void pushPrimitive(lua_State* L, Data* data);
   void popPrimitive(std::string name, Data* dat);
   void topToPrimitive(Data* dat);
};