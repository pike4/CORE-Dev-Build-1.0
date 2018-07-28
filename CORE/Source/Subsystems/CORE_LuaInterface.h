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

	// Game
	static int goToRoom		(lua_State* L);

	// Audio
	static int playMusic	(lua_State* L);
	static int playSound	(lua_State* L);
}