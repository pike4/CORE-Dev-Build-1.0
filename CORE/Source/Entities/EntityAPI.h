#pragma once
#include "Entity.h"
#include "lua.h"

/*
   Entity API to make available to the lua scripting environment
*/
int luaSetEntityData(lua_State* L);
int luaSetOwnData(lua_State* L);
int luaSendEventToSelf(lua_State* L);
int luaSendEventToEntity(lua_State* L);
int luaSendEventOwnChildren(lua_State* L);
int sendGlobalEvent(lua_State* L);