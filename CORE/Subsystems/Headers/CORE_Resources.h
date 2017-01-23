#pragma once
//GameObject Includes
#include "Entity.h"
#include "MenuSystem.h"
#include "Environment.h"

//Resource Includes
#include "RenderableCharSet.h"
#include "Definer.h"
#include "TemplateDef.h"

#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_TTF.h"
#include "SDL_Mixer.h"
#include <map>
#include <unordered_set>
#include <string>

//Functions and data structures to load, store, and free assets and game object definitions
//Is not responsible for maintaining maps or structures used only by certain subsystems like 
//CORE_SystemIO::streams;
namespace CORE_Resources
{
	void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

	Entity* getPrototype(std::string prototypeName);
	TemplateDef* getTemplate(std::string name);
	Environment* getEnvironment(std::string environmentName);
	MenuSystem* getMenuSystem(std::string menuName);

	//****************************
	//Resource Storage Structures
	//****************************
	extern std::map<std::string, SDL_Texture*> loadedTextures;
	extern std::map<std::string, Mix_Chunk*> loadedSounds;
	extern std::map<std::string, TTF_Font*> loadedFonts;
	extern std::map<std::string, Mix_Music*> loadedMusic;
	extern std::map<std::string, RenderableCharSet*> loadedCharSets;
	extern std::unordered_set<std::string> loadedFiles;

	//********************************
	//Game Object Storage Structures
	//********************************
	extern std::map<std::string, Environment*> environments;
	extern std::map<std::string, MenuSystem*> menuSystems;
	extern std::map<std::string, Entity*> prototypes;
	extern std::map<std::string, TemplateDef*> templates;

	//****************************
	//Load XML asset
	//****************************
	void loadResourceFile(std::string fileName);

	//****************************
	//Asset Loading
	//****************************
	SDL_Texture* loadTexture(std::string fileName);
	Mix_Music* loadMusic(std::string fileName);
	Mix_Chunk* loadChunk(std::string fileName);
	TTF_Font* loadFont(std::string fileName, int size);

	//****************************
	//Asset Assignment
	//****************************
	SDL_Texture* assignTexture(std::string fileName);
	Mix_Chunk* assignSound(std::string fileName);
	TTF_Font* assignFont(std::string fileName, int size);
	RenderableCharSet* assignCharSet(std::string fontName, int fontSize, SDL_Color color);
	RenderableCharSet* assignCharSet(std::string name);

	//*****************
	//Templating
	//*****************
	void loadTemplates(std::string fileName);
	void loadTemplates(Definer* definer);

	//*****************
	//Prototyping
	//*****************
	void loadPrototypes(std::string fileName);
	void loadPrototypes(Definer* def);
	void addPrototype(std::string name, Entity* prototype);

	Definer* getTopNodeFromFile(std::string fileName);
	Definer* getFirstNodeFromFile(std::string fileName);
}