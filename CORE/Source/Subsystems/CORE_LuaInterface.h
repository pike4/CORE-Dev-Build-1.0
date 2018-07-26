#pragma once
#include "CORE.h"

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

namespace CORE_LuaInterface
{
	
	void initialize();

	static int goToRoom(lua_State* L);
}