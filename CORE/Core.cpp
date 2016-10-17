#pragma warning(disable : 4018)
#pragma warning(disable : 4244)

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
#include "AssetsManifest.h"
#include "NavigationButton.h"
#include "SystemManager.h"
#include "pugixml.hpp"
#include <map>
#include "SpeechBox.h"
#include "UpdatableTextElement.h"
#include "ImageElement.h"
#include "GUI_Area.h"
#include "GameObjectTypes.h"
#include "GameObject.h"

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
	pew = AudioManager::loadChunk("Assets/Music/pew.wav");
	
	Environment* environment2 = new Environment("room.xml");

	SDL_Color red;
	red.r = 100;

	Timer genTimer;

	SystemManager::loadPrototypes("prototypes.xml");
	GameObject* chuck = NULL;
	
	GameObject* chucksFriend = StateManager::prototypes["Charlie"];

	RenderableCharSet chars = RenderableCharSet(12, sans, red, VideoManager::mRenderer);

	StateManager::goToEnvironment("first");
	StateManager::goToRoomInCurrentEnvironment("living room");

	for (int i = 0; i < 1; i++)
	{
		chuck = ObjectManager::generate("Charlie");
		StateManager::currentRoom->add(chuck);
		chuck->move(540, 360);
	}

	chuck = ObjectManager::generate("Fire");
	StateManager::currentRoom->add(chuck);
	chuck->move(50, 50);
	chuck = ObjectManager::generate("Fire");
	StateManager::currentRoom->add(chuck);
	chuck->move(900, 50);
	chuck = ObjectManager::generate("Fire");
	StateManager::currentRoom->add(chuck);
	chuck->move(50, 580);
	chuck = ObjectManager::generate("Fire");
	StateManager::currentRoom->add(chuck);
	chuck->move(900, 580);

	while (!quit)
	{
		StateManager::update();
	}

	return 0;
}