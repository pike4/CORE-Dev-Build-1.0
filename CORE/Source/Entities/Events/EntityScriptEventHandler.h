#pragma once
#include "ScriptEventHandler.h"
class EntityScriptEventHandler : public ScriptEventHandler
{
public:
   virtual void handle(Event e);
   EntityScriptEventHandler(XMLNode def);
   virtual void registerOwner(Entity* owner);
   virtual EventHandler* spawnCopy();

protected:
   Entity* owner;
};