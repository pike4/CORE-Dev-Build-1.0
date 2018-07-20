#pragma once
#include "ScriptEventHandler.h"
class EntityScriptEventHandler : public ScriptEventHandler
{
public:
   virtual void handleEvent(std::vector<EventArg>);
   EntityScriptEventHandler(DefaultNode* def);
   virtual void registerOwner(Entity* owner);
   virtual EventHandler* spawnCopy();

protected:
   Entity* owner;
};