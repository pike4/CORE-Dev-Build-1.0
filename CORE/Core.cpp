#include "SDL.h"
#include "SDL_Mixer.h"
#include "SDL_TTF.h"
#include "SDL_Image.h"

#include "Room.h"
#include "MenuSystem.h"

#include "Environment.h"

#include "Thing.h"
#include "Updatable.h"
#include "ObjectManager.h"
#include "VideoManager.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "AssetsManifest.h"
#include "TextObjects.h"
#include "BouncingBall.h"
#include "Spinner.h"
#include "Button.h"
#include "NavigationButton.h"
#include "SystemManager.h"
#include "pugixml.hpp"
#include "ResourceHashtable.h"
#include <map>
#include "SpeechBox.h"
#include "TextElement.h"

#undef main

SDL_Event e;

bool quit;

int main()
{
	StateManager::start();

	SDL_Texture* guy = SystemManager::loadTexture("Assets/Sprites/guy.png");
	SDL_Texture* real = SystemManager::loadTexture("Assets/Sprites/real.png");
	SDL_Texture* greg = SystemManager::loadTexture("Assets/Sprites/niceword.png");
	SDL_Texture* cage = SystemManager::loadTexture("Assets/Sprites/cage.png");
	SDL_Texture* peepee = SystemManager::loadTexture("Assets/Sprites/peepee.png");
	SDL_Texture* ball = SystemManager::loadTexture("Assets/Sprites/IMG_BouncingBall.png");

	SDL_Texture* hover = SystemManager::loadTexture("Assets/Sprites/BlankHover.png");
	SDL_Texture* held = SystemManager::loadTexture("Assets/Sprites/BlankHeld.png");
	SDL_Texture* def = SystemManager::loadTexture("Assets/Sprites/BlankDefault.png");
	
	Mix_Music* mega_Music = SystemManager::loadMusic("Assets/Music/a.ogg");
	TTF_Font* sans = TTF_OpenFont("Assets/Fonts/comic.ttf", 12);
	TTF_Font* bigSans = TTF_OpenFont("Assets/Fonts/comic.ttf", 50);
	pew = AudioManager::loadChunk("Assets/Music/pew.wav");
	//AudioManager::startMusicLoop(mega_Music);
	Environment* environment2 = new Environment("room.xml");

	SDL_Color red;
	red.r = 100;

	RenderableCharSet chars = RenderableCharSet(12, sans, red, VideoManager::mRenderer);

	TextElement testText = TextElement(100, 100, 200, 200, &chars);
	testText.stringToLines("We need a hang glider, and a crotch less uncle sam costume, and I want the entire field of your largest stadium covered end to end with naked red heads, and I want the stands packed with every man that remotely resembles my father.");

	SDL_Rect temprect = testText.box;

	while(true)
	{
		SDL_RenderDrawRect(VideoManager::mRenderer, &temprect);
		testText.draw(VideoManager::mRenderer);
		SDL_RenderPresent(VideoManager::mRenderer);
	}

	MenuSystem* argh = new MenuSystem("g.xml");


	StateManager::goToEnvironment("first");
	StateManager::goToMenuSystem("Pause Menu");
	StateManager::goToGUIInCurrentMenuSystem("main");

	StateManager::goToRoomInCurrentEnvironment("living room");

	while (!quit)
	{
		StateManager::update();
	}

	return 0;
}