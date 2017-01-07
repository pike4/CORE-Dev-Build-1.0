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
#include "Updatable.h"
#include "ObjectManager.h"
#include "VideoManager.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "SystemManager.h"
#include "pugixml.hpp"
#include "SpeechBox.h"
#include "DynamicTextElement.h"
#include "ImageElement.h"
#include "GUI_Area.h"
#include "Entity.h"

#include "Data.h"

#undef main

SDL_Event e;

bool quit;

int main()
{
	StateManager::start();
	SDL_Texture* guy = SystemManager::loadTexture("Assets/Sprites/guy.png");
	SDL_Texture* real = SystemManager::loadTexture("Assets/Sprites/real.png");
	SDL_Texture* greg = SystemManager::loadTexture("Assets/Sprites/cat.png");
	SDL_Texture* cage = SystemManager::loadTexture("Assets/Sprites/cage.png");
	SDL_Texture* ball = SystemManager::loadTexture("Assets/Sprites/IMG_BouncingBall.png");

	SDL_Texture* hover = SystemManager::loadTexture("Assets/Sprites/BlankHover.png");
	SDL_Texture* held = SystemManager::loadTexture("Assets/Sprites/BlankHeld.png");
	SDL_Texture* def = SystemManager::loadTexture("Assets/Sprites/BlankDefault.png");
	
	TTF_Font* sans = TTF_OpenFont("Assets/Fonts/comic.ttf", 12);
	TTF_Font* bigSans = TTF_OpenFont("Assets/Fonts/comic.ttf", 50);
	Mix_Chunk* pew = AudioManager::loadChunk("Assets/Music/sans.wav");
	
	Environment* environment2 = new Environment("Assets/XML/room.xml");
	SDL_Color red;
	red.r = 100;
	red.g = 100;

	Timer genTimer;

	SystemManager::loadPrototypes("Assets/XML/prototypes.xml");
	Entity* chuck = NULL;

	MenuSystem* newMen = new MenuSystem("Assets/XML/g.xml");
	StateManager::currentMenuSystem = newMen;

	StateManager::addMenuScreenLayer(newMen->getMenuScreen("fourth"));
	
	Entity* chucksFriend = StateManager::prototypes["Charlie"];

	RenderableCharSet chars = RenderableCharSet(12, sans, red, VideoManager::mRenderer);

	StateManager::goToEnvironment("first");
	StateManager::goToRoomInCurrentEnvironment("living room");

	SpeechBox* textSpeechBox = new SpeechBox(500, 100, "The FitnessGram Pacer Test is a multistage aerobic capacity test that progressively", NULL, &chars);

	textSpeechBox->setValue<int>("x", 200);
	textSpeechBox->setValue<int>("y", 200);

	StateManager::currentRoom->add(textSpeechBox);
	textSpeechBox->clear();
	for (unsigned int i = 0; i < 1; i++)
	{
		chuck = ObjectManager::generate("Charlie");
		StateManager::currentRoom->add(chuck);
		VideoManager::player = chuck;
		//VideoManager::xOffsetInitial = 540;
		//VideoManager::yOffsetInitial = 360;
		//VideoManager::xOffset = (int*)chuck->getPointer("x", 4);
		//VideoManager::yOffset = (int*)chuck->getPointer("y", 4);
	}

	//chuck = ObjectManager::generate("Fire");
	//StateManager::currentRoom->add(chuck);

	//chuck = ObjectManager::generate("Fire");
	//StateManager::currentRoom->add(chuck);
	//chuck = ObjectManager::generate("Fire");
	//StateManager::currentRoom->add(chuck);
	//chuck = ObjectManager::generate("Fire");
	//StateManager::currentRoom->add(chuck);
	//chuck = ObjectManager::generate("Fire");
	//StateManager::currentRoom->add(chuck);

	while (!quit)
	{
		StateManager::update();
	}

	return 0;
}