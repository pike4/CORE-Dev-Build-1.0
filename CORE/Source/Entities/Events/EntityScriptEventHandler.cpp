#include "EntityScriptEventHandler.h"
#include "Component.h"
EventHandler* EntityScriptEventHandler::spawnCopy()
{
   return new EntityScriptEventHandler(*this);
}


void EntityScriptEventHandler::handle(Event e)
{
	e.arguments.push_back(owner);
	ScriptEventHandler::handle(e);
	popEntity("me", owner);
}

EntityScriptEventHandler::EntityScriptEventHandler(XMLNode def)
   : ScriptEventHandler(def)
{
   argNames.push_back("me");
}

void EntityScriptEventHandler::registerOwner(Entity* o)
{
   owner = o;
}