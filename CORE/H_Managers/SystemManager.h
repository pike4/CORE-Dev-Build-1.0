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
#include "NavigationButton.h"
#include "RenderableCharSet.h"

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

	static std::map<std::string, SDL_Texture*> loadedTextures;
	static std::map<std::string, Mix_Chunk*> loadedSounds;
	static std::map<std::string, TTF_Font*> loadedFonts;
	static std::map<std::string, Mix_Music*> loadedMusic;
	static std::map<std::string, RenderableCharSet*> loadedCharSets;

	static SDL_Texture* loadTexture(std::string fileName);
	static Mix_Music* loadMusic(std::string fileName);
	static Mix_Chunk* loadChunk(std::string fileName);
	static TTF_Font* loadFont(std::string fileName, int size);

	static void loadGameObjects(char* fileName, std::vector<BaseObject*>*, std::vector<Visible*>*, std::vector<Updatable*>*, std::vector<Collidable*>*, std::vector<Controllable*>*);

	static SDL_Texture* assignTexture(std::string fileName);
	static Mix_Chunk* assignSound(std::string fileName);
	static TTF_Font* assignFont(std::string fileName, int size);
	static RenderableCharSet* assignCharSet(std::string fontName, int fontSize, SDL_Color color);
	static RenderableCharSet* assignCharSet(std::string name);

	static void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

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

private:
	static Uint32 curTime;
	static Uint32 prevTime;
	static Uint32 outputInterval;

	static Uint32 totalTime;
	static Uint32 totalFrames;

	static Timer FPSTimer;

	static string buffer;
};