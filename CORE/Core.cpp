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
#include "TextObjects.h"
#include "Spinner.h"

#undef main

SDL_Event e;

bool quit;

int main()
{
	StateManager::start();

	SDL_Texture* guy = VideoManager::loadTexture("Sprites/guy.bmp");
	SDL_Texture* real = VideoManager::loadTexture("Sprites/real.bmp");
	SDL_Texture* fag = VideoManager::loadTexture("Sprites/niceword.bmp");
	SDL_Texture* cage = VideoManager::loadTexture("Sprites/cage.bmp");
	SDL_Texture* peepee = VideoManager::loadTexture("Sprites/peepee.bmp");
	Mix_Music* mega_Music = AudioManager::loadMusic("Assets/Music/a.ogg");
	TTF_Font* sans = TTF_OpenFont("Assets/Fonts/comic.ttf", 12);
	pew = AudioManager::loadChunk("Assets/Music/pew.wav");

	AudioManager::startMusicLoop(mega_Music);

	ObjectManager::add(new Thing(100, 100, guy)); 

	SDL_Color color;
	color.a = 0;
	color.r = 0;
	color.g = 0;
	color.b = 255;

	SDL_Point point;
	point.x = 0;
	point.y = 0;
	
	ObjectManager::player = new Player(300, 200, fag);
	ObjectManager::add(new Thing(200, 200, real));
	ObjectManager::add(new Spinner(400, 350, cage, SDL_FLIP_NONE, 0, point, 10.0));
	ObjectManager::add(new Spinner(100, 100, peepee, SDL_FLIP_NONE, 0, point, 100.0));
	ObjectManager::add(new Spinner(400, 200, cage, SDL_FLIP_NONE, 0, point, -210.0));
	ObjectManager::add(new Spinner(200, 350, fag, SDL_FLIP_NONE, 0, point, 20.0));
	ObjectManager::add(new Spinner(400, 50, peepee, SDL_FLIP_NONE, 0, point, -10.0));
	ObjectManager::add(new PlainText(0, 0, sans, "I will build a great wall and nobody builds walls better than me, believe me and I\'ll build them very inexpensively.", color));
	ObjectManager::add(new PlainText(0, 30, sans, "I will build a great, great wall on our southern border, and I will make Mexico pay for that wall. Mark my words.", color));

	while (!quit)
	{
		StateManager::update();
	}

	return 0;
}