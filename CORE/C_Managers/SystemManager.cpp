#include "SDL.h"
#include "SystemManager.h"
#include "ObjectManager.h"
#include "StateManager.h"
#include "Door.h"
#include "AudioManager.h"
#include "Commands.h"
#include "pugixml.hpp"
#include "MenuScreen.h"
#include<map>
void SystemManager::start()
{
	curTime = 0;
	prevTime = 0;
	totalTime = 0;
	totalFrames = 0;
	outputInterval = 2000;
	FPSTimer = *new Timer();
}

void SystemManager::update()
{
	switch (state)
	{
	case CORE_RUNNING:
		updateRunning();
		break;

	case CORE_IN_MENU:
		updateInMenu();
		break;

	case CORE_BLOCKING:
		updateInMenu();
		break;

	case CORE_PAUSED:
		updateInMenu();
		break;
	}
	
}

void SystemManager::updateRunning()
{
	curTime = SDL_GetTicks();
	//updateTime();
	updateQueue();
	updateFPS();
	//printFPS();
}

void SystemManager::updateInMenu()
{

}

void SystemManager::updatePaused()
{

}

void SystemManager::updateBlocking()
{

}

void SystemManager::handleEvent(int eventCode, int posOrNeg, int x, int y)
{

}

#pragma region State Transitions
void SystemManager::goToRunning()
{
	state = CORE_RUNNING;
}

void SystemManager::goToBlocking()
{
	state = CORE_BLOCKING;
}

void SystemManager::goToInMenu()
{
	state = CORE_IN_MENU;
}

void SystemManager::goToPaused()
{
	state = CORE_PAUSED;
}
#pragma endregion

void SystemManager::setoutputInterval(Uint32 ms)
{
	outputInterval = ms;
}

void SystemManager::updateTime()
{
	FPSTimer.updateTime();
}

//To check if the specified time has passed since previous update
bool SystemManager::hasElapsed(Uint32 ms)
{
	return ms >= (curTime - prevTime);
}

//Increments the total number of frames since the FPS was last calculated
void SystemManager::updateFPS()
{
	totalFrames++;
}

//Calculates and prints the average FPS over the time interval specified in outputInterval
void SystemManager::printFPS()
{
	if (FPSTimer.hasElapsed(outputInterval))
	{
		int y = FPSTimer.elapsed();
		printf("FPS: %f \t", 1000 * (float) totalFrames/FPSTimer.elapsed());

		printObjectCount();

		FPSTimer.updateTime();
		totalFrames = 0;

		printFPS();
	}
}

void SystemManager::printObjectCount()
{
	if (FPSTimer.hasElapsed(outputInterval))
	{
		std::vector <BaseObject*>* HH = ObjectManager::getObjectVector();
		printf("Object Count: \t %i\n", HH->size());
	}
}

void SystemManager::flush()
{
	
}

SDL_Texture* SystemManager::loadTexture(std::string fileName)
{
	SDL_Surface* loadedTexture = IMG_Load(fileName.c_str());
	SDL_Texture* optimizedSurface = NULL;

	if (loadedTexture == NULL)
	{
		if (fileName.empty())
		{
			fileName = "NO NAME GIVEN";
		}

		printf("Could not find image: %s\n", fileName);
	}

	else
	{
		optimizedSurface = SDL_CreateTextureFromSurface(VideoManager::mRenderer, loadedTexture);
		SDL_FreeSurface(loadedTexture);
	}

	return optimizedSurface;
}

Mix_Music* SystemManager::loadMusic(std::string fileName)
{
	Mix_Music* newMusic = Mix_LoadMUS(fileName.c_str());

	if (newMusic == NULL)
	{
		if (fileName.empty())
		{
			fileName = "NO NAME GIVEN";
		}

		printf("Could not find music file: %s\n", fileName);
	}

	return newMusic;
}

Mix_Chunk* SystemManager::loadChunk(std::string fileName)
{
	
	Mix_Chunk* newChunk = Mix_LoadWAV(fileName.c_str());

	if (newChunk == NULL)
	{
		if (fileName.empty())
		{
			fileName = "NO NAME GIVEN";
		}

		printf("Could not find sound file: %s\n", fileName);
	}

	return newChunk;
}

TTF_Font* SystemManager::loadFont(std::string fileName, int size)
{
	TTF_Font* newFont = TTF_OpenFont(fileName.c_str(), size);

	if (newFont == NULL)
	{

		if (fileName.empty())
		{
			fileName = "NO NAME GIVEN";
		}

		printf("Could not find font: %s\n", fileName);
	}

	return newFont;
}

//Retrieve the texture with the given filename from the hashmap, loading and inserting the texture if it isn't there
SDL_Texture* SystemManager::assignTexture(std::string fileName)
{
	if (loadedTextures.find(fileName) != loadedTextures.end())
	{
		return loadedTextures[fileName];
	}

	SDL_Texture* newTex = loadTexture(fileName);
	if (newTex != NULL)
	{
		loadedTextures[fileName] = newTex;
	}

	return newTex;
}

Mix_Chunk* SystemManager::assignSound(std::string fileName)
{
	if (loadedSounds.find(fileName) != loadedSounds.end())
	{
		return loadedSounds[fileName];
	}

	Mix_Chunk* newSound = loadChunk(fileName);
	if (newSound != NULL)
	{
		loadedSounds.insert(std::pair<std::string, Mix_Chunk*>(fileName, newSound));
	}

	return newSound;
}

TTF_Font* SystemManager::assignFont(std::string fileName, int size)
{
	if (loadedFonts.find(fileName) != loadedFonts.end())
	{
		return loadedFonts[fileName];
	}

	TTF_Font* newFont = loadFont(fileName, size);

	if (newFont != NULL)
	{
		loadedFonts[fileName] = newFont;
	}

	return newFont;
}

RenderableCharSet* SystemManager::assignCharSet(std::string name, int fontSize, SDL_Color color)
{
	name.append(std::to_string(fontSize));
	
	if (loadedCharSets.find(name) != loadedCharSets.end())
	{
		return loadedCharSets[name];
	}

	TTF_Font* newFont = assignFont(name.c_str(), fontSize);

	loadedCharSets[name] = new RenderableCharSet(fontSize, newFont, color, VideoManager::mRenderer);
}

RenderableCharSet* SystemManager::assignCharSet(std::string name)
{
	if (loadedCharSets.find(name) != loadedCharSets.end())
	{
		return loadedCharSets[name];
	}
}

Uint32 SystemManager::curTime;
Uint32 SystemManager::prevTime;
Uint32 SystemManager::outputInterval;
Uint32 SystemManager::totalTime;
Uint32 SystemManager::totalFrames;

std::map<std::string, SDL_Texture*> SystemManager::loadedTextures;
std::map<std::string, Mix_Chunk*> SystemManager::loadedSounds;
std::map<std::string, Mix_Music*> SystemManager::loadedMusic;
std::map<std::string, TTF_Font*> SystemManager::loadedFonts;
std::map<std::string, RenderableCharSet*> SystemManager::loadedCharSets;


Timer SystemManager::FPSTimer;
string SystemManager::buffer;
int SystemManager::state;

void MouseSendCommand::execute()
{
	//printf("Mouse: %d, %d", point.x, point.y);
}