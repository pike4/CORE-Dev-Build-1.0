#include "SDL.h"
#include "SystemManager.h"
#include "ObjectManager.h"
#include "StateManager.h"
#include "BouncingBall.h"
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

void SystemManager::loadGameObjects(char* fileName, std::vector<BaseObject*>* objectVector, std::vector<Visible*>* drawVector, std::vector<Updatable*>* updateVector, std::vector<Collidable*>* collidableVector, std::vector<Controllable*>* controllableVector)
{
	if (fileName == NULL || objectVector == NULL || drawVector == NULL || updateVector == NULL || collidableVector == NULL)
	{
		return;
	}

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(fileName);

	pugi::xml_node node = doc.first_child().first_child();
	
	do
	{
		if (strcmp(node.name(), "BouncingBall") == 0)
		{
			new BouncingBall(node, objectVector, drawVector, updateVector, collidableVector);
		}

		else if (!strcmp(node.name(), "Player"))
		{
			new Player(node, objectVector, drawVector, updateVector, collidableVector, controllableVector);
		}

		else if (!strcmp(node.name(), "Door"))
		{
			new Door(node, objectVector, drawVector, collidableVector);
		}

		node = node.next_sibling();
	} while (node.name() != "");
}

SDL_Texture* SystemManager::loadTexture(char* fileName)
{
	SDL_Surface* loadedTexture = IMG_Load(fileName);
	SDL_Texture* optimizedSurface = NULL;

	if (loadedTexture == NULL)
	{
		if (strcmp(fileName, "") == 0)
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

Mix_Music* SystemManager::loadMusic(char* fileName)
{
	Mix_Music* newMusic = Mix_LoadMUS(fileName);

	if (newMusic == NULL)
	{
		if (strcmp(fileName, "") == 0)
		{
			fileName = "NO NAME GIVEN";
		}

		printf("Could not find music file: %s\n", fileName);
	}

	return newMusic;
}

Mix_Chunk* SystemManager::loadChunk(char* fileName)
{
	
	Mix_Chunk* newChunk = Mix_LoadWAV(fileName);

	if (newChunk == NULL)
	{
		if (strcmp(fileName, "") == 0)
		{
			fileName = "NO NAME GIVEN";
		}

		printf("Could not find sound file: %s\n", fileName);
	}

	return newChunk;
}

TTF_Font* SystemManager::loadFont(char* fileName, int size)
{
	TTF_Font* newFont = TTF_OpenFont(fileName, size);

	if (newFont == NULL)
	{

		if (strcmp(fileName, "") == 0)
		{
			fileName = "NO NAME GIVEN";
		}

		printf("Could not find font: %s\n", fileName);
	}

	return newFont;
}

//Retrieve the texture with the given filename from the hashmap, loading and inserting the texture if it isn't there
SDL_Texture* SystemManager::assignTexture(char* fileName)
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

Mix_Chunk* SystemManager::assignSound(char* fileName)
{
	if (loadedSounds.find(fileName) != loadedSounds.end())
	{
		return loadedSounds[fileName];
	}

	Mix_Chunk* newSound = loadChunk(fileName);
	if (newSound != NULL)
	{
		loadedSounds.insert(std::pair<char*, Mix_Chunk*>(fileName, newSound));
	}

	return newSound;
}

TTF_Font* SystemManager::assignFont(char* fileName, int size)
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

RenderableCharSet* SystemManager::assignCharSet(char* fontName, int fontSize, SDL_Color color)
{
	char* name = fontName;
	strcat(name, std::to_string(fontSize).c_str());
	
	if (loadedCharSets.find(name) != loadedCharSets.end())
	{
		return loadedCharSets[name];
	}

	TTF_Font* newFont = assignFont(fontName, fontSize);

	loadedCharSets[name] = new RenderableCharSet(fontSize, newFont, color, VideoManager::mRenderer);


}

MenuScreen* SystemManager::GUI_LoadFromFile(pugi::xml_node node)
{
	MenuScreen* newGUI = new MenuScreen();

	pugi::xml_node childNode = node.first_child();
	char* curName;
	do
	{
		curName = (char*)childNode.name();

		if (!strcmp(curName, "name"))
		{
			newGUI->name = (char*) childNode.first_child().value();
		}

		if (strcmp(curName, "button") == 0)
		{
			newGUI->controls.push_back(Button_LoadFromFile(childNode));
		}

		else if (strcmp(curName, "background") == 0)
		{

		}
		childNode = childNode.next_sibling();

	} while (strcmp(curName, "") != 0);

	return newGUI;
}

Button* SystemManager::Button_LoadFromFile(pugi::xml_node node)
{
	int x, y, w, h, fontSize;
	SDL_Texture* held;
	SDL_Texture* hover;
	SDL_Texture* def;
	TTF_Font* font;
	char* text;
	printf("%s\n", node.name());
	x = atoi(node.child("x").first_child().value());
	y = atoi(node.child("y").first_child().value());
	w = atoi(node.child("w").first_child().value());
	h = atoi(node.child("h").first_child().value());

	def = assignTexture((char*) node.child("DefTexture").first_child().value());
	held= assignTexture((char*)node.child("HeldTexture").first_child().value());
	hover = assignTexture((char*)node.child("HoverTexture").first_child().value());
	text = (char*)node.child("text").first_child().value();
	fontSize = atoi(node.child("fontSize").first_child().value());
	font = assignFont((char*)node.child("font").first_child().value(), fontSize);

	SDL_Color col;
	col.a = 20;

	//return new Button(x, y, def, held, hover, text, font, col, NULL);
	return NULL;
}



Uint32 SystemManager::curTime;
Uint32 SystemManager::prevTime;
Uint32 SystemManager::outputInterval;
Uint32 SystemManager::totalTime;
Uint32 SystemManager::totalFrames;

std::map<char*, SDL_Texture*> SystemManager::loadedTextures;
std::map<char*, Mix_Chunk*> SystemManager::loadedSounds;
std::map<char*, Mix_Music*> SystemManager::loadedMusic;
std::map<char*, TTF_Font*> SystemManager::loadedFonts;
std::map<char*, RenderableCharSet*> SystemManager::loadedCharSets;


Timer SystemManager::FPSTimer;
string SystemManager::buffer;
int SystemManager::state;

void MouseSendCommand::execute()
{
	//printf("Mouse: %d, %d", point.x, point.y);
}