#pragma once
#include "ScriptEventHandler.h"
class EntityScriptEventHandler : public ScriptEventHandler
{
public:
   virtual void handleEvent(std::vector<EventArg>);
   EntityScriptEventHandler(Node def);
   virtual void registerOwner(Entity* owner);
   virtual EventHandler* spawnCopy();

protected:
   Entity* owner;
};