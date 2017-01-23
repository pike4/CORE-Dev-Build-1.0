#pragma warning(disable : 4018)
#pragma warning(disable : 4244)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>

#include "SDL.h"
#include "SDL_Mixer.h"
#include "SDL_TTF.h"
#include "SDL_Image.h"

#include "Room.h"
#include "MenuSystem.h"
#include "Environment.h"
#include "DragArea.h"
#include "CORE_Factory.h"
#include "CORE_Graphics.h"
#include "CORE.h"
#include "CORE_Audio.h"
#include "CORE_Resources.h"
#include "pugixml.hpp"
#include "SpeechBox.h"
#include "DynamicTextElement.h"
#include "ImageElement.h"
#include "GUI_Area.h"
#include "Entity.h"

#include "Data.h"

#undef main

int main()
{
	CORE::start();
	SDL_Texture* guy = CORE_Resources::loadTexture("Assets/Sprites/guy.png");
	SDL_Texture* real = CORE_Resources::loadTexture("Assets/Sprites/real.png");
	SDL_Texture* greg = CORE_Resources::loadTexture("Assets/Sprites/cat.png");
	SDL_Texture* cage = CORE_Resources::loadTexture("Assets/Sprites/cage.png");
	SDL_Texture* ball = CORE_Resources::loadTexture("Assets/Sprites/IMG_BouncingBall.png");

	SDL_Texture* hover = CORE_Resources::loadTexture("Assets/Sprites/BlankHover.png");
	SDL_Texture* held = CORE_Resources::loadTexture("Assets/Sprites/BlankHeld.png");
	SDL_Texture* def = CORE_Resources::loadTexture("Assets/Sprites/BlankDefault.png");
	
	TTF_Font* sans = TTF_OpenFont("Assets/Fonts/comic.ttf", 12);
	TTF_Font* bigSans = TTF_OpenFont("Assets/Fonts/comic.ttf", 50);
	Mix_Chunk* pew = CORE_Audio::loadChunk("Assets/Music/sans.wav");
	
	Environment* environment2 = new Environment("Assets/XML/room.xml");
	SDL_Color red;
	red.r = 100;
	red.g = 100;

	CORE_Resources::loadTemplates("Assets/XML/templates.xml");

	Timer genTimer;

	CORE_Resources::loadPrototypes("Assets/XML/prototypes.xml");
	Entity* chuck = NULL;

	CORE_Resources::loadResourceFile("Assets/XML/g.xml");

	MenuSystem* newMen = CORE_Resources::getMenuSystem("main");
	CORE::currentMenuSystem = newMen;

	MenuScreen* newMenu = newMen->getMenuScreen("fourth");

	CORE::addMenuScreenLayer(newMenu);
	
	Entity* chucksFriend = CORE_Resources::getPrototype("Charlie");

	RenderableCharSet chars = RenderableCharSet(12, sans, red, CORE_Graphics::mRenderer);

	CORE::goToEnvironment("first");
	CORE::goToRoomInCurrentEnvironment("living room");

	SpeechBox* textSpeechBox = new SpeechBox(500, 100, "The FitnessGram Pacer Test is a multistage aerobic capacity test that progressively", NULL, &chars);

	textSpeechBox->setValue<int>("x", 200);
	textSpeechBox->setValue<int>("y", 200);

	CORE_Resources::loadResourceFile("assets/xml/test.xml");

	CORE::currentRoom->add(textSpeechBox);
	textSpeechBox->clear();
	for (unsigned int i = 0; i < 1; i++)
	{
		chuck = CORE_Factory::generate("Charlie");
		CORE::currentRoom->add(chuck);
		//CORE_Graphics::xOffsetInitial = 540;
		//CORE_Graphics::yOffsetInitial = 360;
		//CORE_Graphics::xOffset = (int*)chuck->getPointer("x", 4);
		//CORE_Graphics::yOffset = (int*)chuck->getPointer("y", 4);
	}

	//chuck = CORE_Factory::generate("Fire");
	//CORE::currentRoom->add(chuck);

	//chuck = CORE_Factory::generate("Fire");
	//CORE::currentRoom->add(chuck);
	//chuck = CORE_Factory::generate("Fire");
	//CORE::currentRoom->add(chuck);
	//chuck = CORE_Factory::generate("Fire");
	//CORE::currentRoom->add(chuck);
	//chuck = CORE_Factory::generate("Fire");
	//CORE::currentRoom->add(chuck);

	while (!CORE::quit)
	{
		CORE::update();
	}

	return 0;
}