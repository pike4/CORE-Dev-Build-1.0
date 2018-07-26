#include "CORE_LuaInterface.h"
#include "CORE_Resources.h"



namespace CORE_LuaInterface
{
	void initialize()
	{
		// Bind CORE subsystem functions to lua state
		lua_register(CORE_Resources::L, "goToRoom", goToRoom);
	}


	// Function:	goToRoom(string roomName )
	// Destination: CORE::goToRoomInCurrentEnvironment
	static int goToRoom(lua_State* L)
	{
		int n = lua_gettop(L);

		std::string roomName = lua_tostring(L, 1);

		CORE::goToRoomInCurrentEnvironment(roomName);

		return 0;
	}
}