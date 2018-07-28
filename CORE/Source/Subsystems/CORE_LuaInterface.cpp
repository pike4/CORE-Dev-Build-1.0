#include "CORE_LuaInterface.h"
#include "CORE_Resources.h"
#include "CORE_Audio.h"



namespace CORE_LuaInterface
{
	void initialize()
	{
		// Bind CORE API functions to lua state
		lua_register(CORE_Resources::L, "goToRoom", goToRoom);
		lua_register(CORE_Resources::L, "playMusic", playMusic);
		lua_register(CORE_Resources::L, "pauseMusic", pauseMusic);
		lua_register(CORE_Resources::L, "playSound", playSound);
		lua_register(CORE_Resources::L, "notifyOther", luaSendEventToEntity);
		lua_register(CORE_Resources::L, "notifySelf", luaSendEventToSelf);
		lua_register(CORE_Resources::L, "notifyChildren", luaSendEventOwnChildren);
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

	static int playMusic(lua_State* L)
	{
		int n = lua_gettop(L);

		if (n != 1) {
			CORE_SystemIO::error("Bad number of arguments in call to playMusic");
		}

		else {
			std::string trackName = lua_tostring(L, 1);
			CORE_Audio::startMusicLoop(trackName);
		}

		return 0;
	}

	static int playSound(lua_State* L)
	{
		printf("play sound\n");
		int n = lua_gettop(L);

		if (n != 1) {
			CORE_SystemIO::error("Bad number of arguments in call to playSound");
		}

		else {
			std::string soundName= lua_tostring(L, 1);
			CORE_Audio::playSound(soundName);
		}

		return 0;
	}

	static int pauseMusic(lua_State* L)
	{
		CORE_Audio::pauseMusic();
		return 0;
	}
}