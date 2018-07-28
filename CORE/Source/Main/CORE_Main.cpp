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
#include "ScriptEventHandler.h"
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

#include <fstream>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#undef main

int main()
{
	printf("sizeof: %d\n", sizeof(Entity));
	printf("sizeof: %d\n", sizeof(std::vector<Controllable*>));
	printf("sizeof: %d\n", sizeof(std::map<int, int>));


	//Lua!
	CORE_Resources::L = luaL_newstate();
	luaL_openlibs(CORE_Resources::L);

	CORE::start();
	CORE_Resources::loadResourceFile("Assets/XML/eventDefs.xml");
	CORE_Resources::loadResourceFile("Assets/XML/New_MenuSystem_2017.xml");
	CORE_Resources::loadResourceFile("Assets/XML/New_Room_2017.xml");

	CORE_Resources::loadResourceFile("Assets/XML/village_test.xml");

	MenuSystem* newMenuSystem = CORE_Resources::getMenuSystem("main");
	CORE::currentMenuSystem = newMenuSystem;
	MenuScreen* newMenu = newMenuSystem->getMenuScreen("fourth");
	CORE::addMenuScreenLayer(newMenu);

	CORE::goToEnvironment("first");
	CORE::goToRoomInCurrentEnvironment("living room");

	CORE::goToRoomInCurrentEnvironment("garage");

	CORE::goToEnvironment("other");

	CORE::goToRoomInCurrentEnvironment("room1");

	while (!CORE::quit)
	{
		CORE::update();
	}

	return 0;
}