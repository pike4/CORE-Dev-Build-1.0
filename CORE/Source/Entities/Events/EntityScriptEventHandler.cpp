#include "EntityScriptEventHandler.h"
#include "Component.h"
EventHandler* EntityScriptEventHandler::spawnCopy()
{
   return new EntityScriptEventHandler(*this);
}

void EntityScriptEventHandler::handleEvent(std::vector<EventArg> args)
{
   args.push_back(owner);

   ScriptEventHandler::handleEvent(args);

   popEntity("me", owner);
}

EntityScriptEventHandler::EntityScriptEventHandler(DefaultNode* def)
   : ScriptEventHandler(def)
{
   argNames.push_back("me");
}

void EntityScriptEventHandler::registerOwner(Entity* o)
{
   owner = o;
}