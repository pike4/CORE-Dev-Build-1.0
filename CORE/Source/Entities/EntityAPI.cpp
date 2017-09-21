#include "EntityAPI.h"

/**
Send the given event to the given entity

Lua Parameters:
\param E1         - A table containing a pointer to the entity in question
\param name       - The name of the event to generate
\param arg1-argn  - The arguments list
*/
int luaSendEventToEntity(lua_State* L)
{
   return 0;
}

/**
Send the given event to the children of entity "self" in current script

Lua Parameters:
\param name       - The name of the event to generate
\param arg1-argn  - The arguments list
*/
int luaSendEventOwnChildren(lua_State* L)
{
   return 0;
}

/**
Send the given event to the children of entity "self" in current script

Lua Parameters:
\param name       - The name of the event to generate
\param arg1-argn  - The arguments list
*/
int luaSendEventToSelf(lua_State* L)
{
   return 0;
}

/**
Set the given member of the given entity to the given value

Lua Parameters:
\param entity  - The name of the entity
\param member  - The name of the member to set
\param value   - The value to set
*/
int luaSetEntityData(lua_State* L)
{
   return 0;
}

/**
Set the given member of the current entity to the given value

Lua Parameters:
\param name       - The name of the member to set
\param arg1-argn  - The arguments list
*/
int luaSetOwnData(lua_State* L)
{
   return 0;
}