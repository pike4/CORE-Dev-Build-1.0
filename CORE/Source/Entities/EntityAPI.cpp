#include "EntityAPI.h"
#include "CORE_LuaInterface.h"
#include "CORE_Resources.h"
#include "CORE.h"

/**
Send the given event to the given entity

Lua Parameters:
\param E1		- The ID of the target entity
\param name		- The name of the event to generate
\param arg1-argn- The arguments list
*/
int luaSendEventToEntity(lua_State* L)
{
	int n = lua_gettop(L);

	if (n < 2) 
	{
		CORE_SystemIO::error("Function sendToOther requires at least 2 arguments");
	}

	int ID = lua_tointeger(L, 1);
	
	Event e = CORE_LuaInterface::getEventFromStack(n-1, 1, L);

	Entity* entity = CORE::getObjectByID(ID);

	if (entity)
	{
		entity->handle(e);
	}

	return 0;
}

/**
Send the given event to the children of entity "self" in current script

Lua Parameters:
\param name		  - The name of the event to generate
\param arg1-argn  - The arguments list
*/
int luaSendEventOwnChildren(lua_State* L)
{
	int n = lua_gettop(L);

	if (n < 1) {
		CORE_SystemIO::error("Function sendToChildren requires at least 1 argument");
	}



	return 0;
}

/**
Send the given event to the children of entity "self" in current script

Lua Parameters:
\param name		 - The name of the event to generate
\param arg1-argn - The arguments list
*/
int luaSendEventToSelf(lua_State* L)
{
	int n = lua_gettop(L);

	if (n < 1) {
		CORE_SystemIO::error("Function sendToSelf requires at least 1 argument1");
	}

	return 0;
}

/**
Set the given member of the given entity to the given value

Lua Parameters:
\param entity	- The name of the entity
\param member	- The name of the member to set
\param value	- The value to set
*/
int luaSetEntityData(lua_State* L)
{
	return 0;
}

/**
Set the given member of the current entity to the given value

Lua Parameters:
\param name		 - The name of the member to set
\param arg1-argn - The arguments list
*/
int luaSetOwnData(lua_State* L)
{
	return 0;
}