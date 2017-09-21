#include "ScriptEventHandler.h"
#include "EventDef.h"
#include "Core_Resources.h"

ScriptEventHandler::ScriptEventHandler(Node* def)
{
   if (!def)
   {
      CORE_SystemIO::error("Could not construct ScriptEventHandler from null Node*");
      return;
   }

   scriptName = def->getVariable("file");
   std::string defName = def->getVariable("format");
   Node* argNamesNode = def->getChild("argNames");
  
   //Event format is defined elsewhere
   if (defName == "")
   {
      Node* eventDefNode = def->getChild("format");

      std::vector<Node*>* eventDefChildren = eventDefNode->getChildren();

      EventDef newDef = EventDef(eventDefNode);
      format = newDef.format;
   }

   //Event format is defined here
   else
   {
      if (CORE_Resources::events.find(defName) != CORE_Resources::events.end())
      {
         format = CORE_Resources::events[defName].format;
      }

      else
      {
         CORE_SystemIO::error("Script \'" + def->getName() + 
            "\' refers to non existant event definition: \'" + defName);
      }
   }

   if (argNamesNode)
   {
      std::vector<Node*>* argNamesChildren = argNamesNode->getChildren();

      if (argNamesChildren->size() != format.size())
      {
         CORE_SystemIO::error("Number of arg names given differs from length of event format");
      }

      for (int i = 0; i < argNamesChildren->size(); i++)
      {
         argNames.push_back((*argNamesChildren)[i]->getName());
      }
   }

   else if (format.size() > 0)
   {
      CORE_SystemIO::error("ScriptEventHandler \'" + def->getName() + "\' has unnamed arguments");
   }

   if (scriptName == "")
   {
      CORE_SystemIO::error("ScriptEventHandler \'" + def->getName() + "\' was not given a filename");
   }
}

int callfunc(lua_State* L)
{
   std::cout << "aaaaaaa";
   return 1;
}

EventHandler* ScriptEventHandler::spawnCopy()
{
   return new ScriptEventHandler(*this);
}

/**
   Push the arguments onto the lua stack, run the script, and update argument
   values when values change in script
*/
void ScriptEventHandler::handleEvent(std::vector<EventArg> args)
{
   if (args.size() != argNames.size())
   {
      CORE_SystemIO::error("Script called with " + std::to_string(args.size()) +
         "arguments but takes " + std::to_string(argNames.size()));
      return;
   }

   using CORE_Resources::L;
   CORE_Resources::L = lua_open();
   luaL_openlibs(CORE_Resources::L);

   //Push arguments onto the stack and register global names
   for (int i = 0; i < args.size(); i++)
   {
      // The current argument is an entity
      if (args[i].data == NULL)
      {
         pushEntity(argNames[i], args[i].entity);
      }

      // The current argument is a primitive
      else
      {
         pushPrimitive(L, args[i].data);
         lua_setglobal(CORE_Resources::L, argNames[i].c_str());
      }
   }

   luaL_dofile(L, scriptName.c_str());

   //Update the arguments according to the stack values
   for (int i = 0; i < args.size(); i++)
   {
      //Update a global primitive
      if (args[i].entity == NULL)
      {
         popPrimitive(argNames[i], args[i].data);
      }

      //Update an entity
      else
      {
         popEntity(argNames[i], args[i].entity);
      }
   }
}

/**
   Push the value of the given data pointer onto the stack as a primitive of 
   the appropriate type
*/
void ScriptEventHandler::pushPrimitive(lua_State* L, Data* data)
{
   CORE_TypeTraits::PrimitiveType prim = data->getType();
   switch (prim)
   {
   case CORE_TypeTraits::_integer:
      lua_pushinteger(CORE_Resources::L, *((DataImpl<int>*) data));
      break;
   case CORE_TypeTraits::_boolean:
      lua_pushboolean(CORE_Resources::L, *((DataImpl<bool>*) data));
      break;
   case CORE_TypeTraits::_floatingPoint:
      lua_pushnumber(CORE_Resources::L, *((DataImpl<float>*) data));
      break;
   default:
      lua_pushinteger(L, 0);
      CORE_SystemIO::error("Unsupported primitive type pushed to script "
      + scriptName);
      break;
   }
}

/**
   Set the value of the given data pointer to the value of the given global lua value
*/
void ScriptEventHandler::popPrimitive(std::string name, Data* dat)
{
   using CORE_Resources::L;
   lua_getglobal(L, name.c_str());
   topToPrimitive(dat);
}

/**
   Set the value of the given data pointer to the value at the top of the lua stack
*/
void ScriptEventHandler::topToPrimitive(Data* dat)
{
   using CORE_Resources::L;
   switch (dat->getType())
   {
   case _integer:
      *((DataImpl<int>*) dat) = (int)lua_tonumber(L, -1);
      break;
   case _boolean:
      *((DataImpl<bool>*) dat) = lua_toboolean(L, -1);
      break;
   case _floatingPoint:
      *((DataImpl<float>*) dat) = (float)lua_tonumber(L, -1);
      break;
   }
}

/**
   Push the member data of the given entity as a table of the given name
*/
void ScriptEventHandler::pushEntity(std::string name, Entity* E1)
{
   std::vector<std::pair<std::string, Data*>> data =
      E1->getAllData();

   lua_newtable(CORE_Resources::L);
   for (int j = 0; j < data.size(); j++)
   {
      int tI = lua_gettop(CORE_Resources::L);
      lua_pushstring(CORE_Resources::L, data[j].first.c_str());
      pushPrimitive(CORE_Resources::L, data[j].second);

      lua_settable(CORE_Resources::L, tI);
   }
   lua_setglobal(CORE_Resources::L, name.c_str());
}

/**
   Get the entity table from the stack and restore the values to the original entity
*/
void ScriptEventHandler::popEntity(std::string name, Entity* E1)
{
   using CORE_Resources::L;

   lua_getglobal(L, name.c_str());
   lua_pushnil(L);

   while (lua_next(L, -2))
   {
      std::string memberName = lua_tostring(L, -2);
      topToPrimitive(E1->data[memberName]);
      lua_pop(L, 1);
   }
}