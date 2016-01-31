#include "SDL.h"
#include "SDL_Mixer.h"
#include "SDL_TTF.h"
#include "SDL_Image.h"

#include "Thing.h"
#include "Updatable.h"
#include "ObjectManager.h"
#include "VideoManager.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "AssetsManifest.h"

#undef main

SDL_Event e;

bool quit;

int main()
{
	StateManager::start();

	SDL_Texture* guy = VideoManager::loadTexture("Sprites/guy.bmp");
	SDL_Texture* real = VideoManager::loadTexture("Sprites/real.bmp");
	Mix_Music* mega_Music = AudioManager::loadMusic("Assets/Music/a.ogg");
	pew = AudioManager::loadChunk("Assets/Music/pew.wav");

	AudioManager::startMusicLoop(mega_Music);

	ObjectManager::add(new Thing(100, 100, guy)); 

	ObjectManager::add(new Thing(400, 100, real));
	ObjectManager::add(new Thing(300, 100, 1, 0, real));
	ObjectManager::add(new Thing(200, 100, 1, 0, real));
	ObjectManager::add(new Thing(100, 100, 0, 1, real));
	ObjectManager::add(new Thing(100, 200, 0, 1, real));
	ObjectManager::add(new Thing(400, 200, -1, 0, real));
	ObjectManager::player = new Thing(300, 200, real);
	ObjectManager::add(new Thing(200, 200, real));
	

	while (!quit)
	{
		StateManager::update();
	}

	return 0;
}