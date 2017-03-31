#pragma warning(disable : 4018)
#pragma warning(disable : 4244)


#include "DragArea.h"
#include "SpeechBox.h"
#include "DynamicTextElement.h"
#include "ImageElement.h"
#include "GUI_Area.h"
#include "Entity.h"
#include "Room.h"
#include "MenuSystem.h"
#include "Environment.h"


#include "Data.h"

#include "CORE_Factory.h"
#include "CORE_SystemIO.h"
#include "CORE_Graphics.h"
#include "CORE.h"
#include "CORE_Audio.h"
#include "CORE_Resources.h"

#include "StateOffsetCalculator.h"

#include "SDL.h"
#include "SDL_Mixer.h"
#include "SDL_TTF.h"
#include "SDL_Image.h"
#include "pugixml.hpp"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

lua_State* L;

#include <fstream>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#undef main

static int printNum(lua_State* L)
{
   int numArg = lua_gettop(L);

   for (int i = 0; i < numArg; i++)
   {
      int a = lua_tonumber(L, i);
      printf("lua sez: %i\n", a);
   }

   return 0;
}

int main()
{
   //Lua!
   L = lua_open();
   luaL_openlibs(L);
   lua_register(L, "printNum", printNum);
   luaL_dofile(L, "test.lua");

   lua_getglobal(L, "add");

   lua_pushinteger(L, 6);
   lua_pushinteger(L, 5);

   
   lua_close(L);

	CORE::start();
   CORE_Resources::loadResourceFile("Assets/XML/eventDefs.xml");
	CORE_Resources::loadResourceFile("Assets/XML/New_MenuSystem_2017.xml");
	MenuSystem* newMenuSystem = CORE_Resources::getMenuSystem("main");
	CORE::currentMenuSystem = newMenuSystem;
	MenuScreen* newMenu = newMenuSystem->getMenuScreen("fourth");
	CORE::addMenuScreenLayer(newMenu);

   CORE_SystemIO::openLogFile("out", "Asets/logs/out.txt");

//	CORE::goToEnvironment("first");
//	CORE::goToRoomInCurrentEnvironment("living room");

	while (!CORE::quit)
	{
		CORE::update();
	}

	return 0;
}