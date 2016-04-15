#include "SDL.h"
#include "SDL_Image.h"
#include "Timer.h"
#include "VideoManager.h"
#include "_Manager.h"
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include "pugixml.hpp""

#pragma once

using namespace std;

#pragma once

class SystemManager : public Manager
{
public:
	static int state;

	static void start();

	static void update();

	static void updateRunning();
	static void updateInMenu();
	static void updatePaused();
	static void updateBlocking();

	static void goToBlocking();
	static void goToPaused();
	static void goToRunning();
	static void goToInMenu();

	static std::map<char*, SDL_Texture*> loadedTextures;
	static std::map<char*, Mix_Chunk*> loadedSounds;
	static std::map<char*, TTF_Font*> loadedFonts;
	static std::map<char*, Mix_Music*> loadedMusic;

	static SDL_Texture* loadTexture(char* fileName);
	static Mix_Music* loadMusic(char* fileName);
	static Mix_Chunk* loadChunk(char* fileName);
	static TTF_Font* loadFont(char* fileName);

	static SDL_Texture* assignTexture(char* fileName);
	static Mix_Chunk* assignSound(char* fileName);
	static TTF_Font* assignFont(char* fileName);

	static void updateFPS();

	static void stop();

	static void changeState(int state);

	static void flush();

	static void setoutputInterval(Uint32 ms);

	static bool hasElapsed(Uint32 ms);

	static void updateTime();
	static void printFPS();
	static void printObjectCount();
	static void drawableCount();


	static GUI* GUI_LoadFromFile(pugi::xml_node node);
	static Button* Button_LoadFromFile(pugi::xml_node node);

private:
	static Uint32 curTime;
	static Uint32 prevTime;
	static Uint32 outputInterval;

	static Uint32 totalTime;
	static Uint32 totalFrames;

	static Timer FPSTimer;

	static string buffer;
};