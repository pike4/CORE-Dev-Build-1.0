#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "CORE.h"
#include "CORE_Audio.h"
#include "CORE_Graphics.h"
#include "Commands.h"
#include "MenuScreen.h"
#include "Definer.h"
#include "TemplateDef.h"
#include "Entity.h"

#include "SDL.h"
#include "pugixml.hpp"
#include<map>

namespace CORE_Resources
{
	void handleEvent(int eventCode, int posOrNeg, int x, int y)
	{

	}

#pragma region XML
	void loadResourceFile(std::string fileName)
	{
		if (loadedFiles.find(fileName) != loadedFiles.end())
		{
			return;
		}

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(fileName.c_str());
		pugi::xml_node node = doc.first_child();
		node = node.first_child();

		while (node)
		{
			Definer* topDef = CORE_Factory::generateDefiner(node);
			std::string name = topDef->getName();

			if (name == "imports")
			{
				std::vector<Definer*>* curChildren = topDef->getChildren();

				for (unsigned int i = 0; i < curChildren->size(); i++)
				{
					Definer* curImportDef = (*curChildren)[i];
					std::string importName = curImportDef->getName();
					loadResourceFile(importName);
				}
			}

			else if (name == "prototypes")
			{
				loadPrototypes(topDef);
			}

			else if (name == "templates")
			{
				loadTemplates(topDef);
			}

			else if (name == "environment")
			{
				new Environment(topDef);
			}

			else if (name == "menuSystem")
			{
				new MenuSystem(topDef);
			}

			node = node.next_sibling();
		}
	}
#pragma endregion

#pragma region Asset Loading
	SDL_Texture* loadTexture(std::string fileName)
	{
		SDL_Surface* loadedTexture = IMG_Load(fileName.c_str());
		SDL_Texture* optimizedSurface = NULL;

		if (loadedTexture == NULL)
		{
			if (fileName.empty())
			{
				fileName = "NO NAME GIVEN";
			}

			printf("Could not find image: %s\n", fileName.c_str());
		}

		else
		{
			optimizedSurface = SDL_CreateTextureFromSurface(CORE_Graphics::mRenderer, loadedTexture);
			SDL_FreeSurface(loadedTexture);
		}

		return optimizedSurface;
	}

	Mix_Music* loadMusic(std::string fileName)
	{
		Mix_Music* newMusic = Mix_LoadMUS(fileName.c_str());

		if (newMusic == NULL)
		{
			if (fileName.empty())
			{
				fileName = "NO NAME GIVEN";
			}

			printf("Could not find music file: %s\n", fileName.c_str());
		}

		return newMusic;
	}

	Mix_Chunk* loadChunk(std::string fileName)
	{

		Mix_Chunk* newChunk = Mix_LoadWAV(fileName.c_str());

		if (newChunk == NULL)
		{
			if (fileName.empty())
			{
				fileName = "NO NAME GIVEN";
			}

			printf("Could not find sound file: %s\n", fileName.c_str());
		}

		return newChunk;
	}

	TTF_Font* loadFont(std::string fileName, int size)
	{
		TTF_Font* newFont = TTF_OpenFont(fileName.c_str(), size);

		if (newFont == NULL)
		{

			if (fileName.empty())
			{
				fileName = "NO NAME GIVEN";
			}

			printf("Could not find font: %s\n", fileName.c_str());
		}

		return newFont;
	}
#pragma endregion

#pragma region Asset Assignment
	//Retrieve the texture with the given filename from the hashmap, loading and inserting the 
	//texture if it isn't there
	SDL_Texture* assignTexture(std::string fileName)
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

	Mix_Chunk* assignSound(std::string fileName)
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

	TTF_Font* assignFont(std::string fileName, int size)
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

	RenderableCharSet* assignCharSet(std::string name, int fontSize, SDL_Color color)
	{
		name.append(std::to_string(fontSize));

		if (loadedCharSets.find(name) == loadedCharSets.end())
		{
			TTF_Font* newFont = assignFont(name.c_str(), fontSize);

			loadedCharSets[name] = new RenderableCharSet(fontSize, newFont, color,
				CORE_Graphics::mRenderer);
		}

		return loadedCharSets[name];

	}

	RenderableCharSet* assignCharSet(std::string name)
	{
		if (loadedCharSets.find(name) != loadedCharSets.end())
		{
			return loadedCharSets[name];
		}

		else
			return NULL;
	}
#pragma endregion

#pragma region Asset Access
	Entity* getPrototype(std::string prototypeName)
	{
		Entity* ret = NULL;

		if (prototypes.find(prototypeName) != prototypes.end())
		{
			ret = prototypes[prototypeName];
		}

		return ret;
	}

	TemplateDef* getTemplate(std::string name)
	{
		TemplateDef* ret = NULL;

		if (templates.find(name) != templates.end())
		{
			ret = templates[name];
		}

		return ret;
	}

	Environment* getEnvironment(std::string environmentName)
	{
		Environment* ret = NULL;

		if (environments.find(environmentName) != environments.end())
		{
			ret = environments[environmentName];
		}

		return ret;
	}

	MenuSystem* getMenuSystem(std::string menuName)
	{
		MenuSystem* ret = NULL;

		if (menuSystems.find(menuName) != menuSystems.end())
		{
			ret = menuSystems[menuName];
		}

		return ret;
	}
#pragma endregion

#pragma region XML Templating
	void loadTemplates(std::string fileName)
	{
		Definer* def = getFirstNodeFromFile(fileName);
		loadTemplates(def);
	}

	void loadTemplates(Definer* def)
	{
		if (def->getName() == "templates")
		{
			std::vector<Definer*>* templateVector = def->getChildren();

			for (unsigned int i = 0; i < templateVector->size(); i++)
			{
				Definer* curDefiner = (*templateVector)[i];

				TemplateDef* newTemplate = new TemplateDef(curDefiner);

				templates[newTemplate->name] = newTemplate;
			}
		}
	}
#pragma endregion

#pragma region Prototyping
	void loadPrototypes(std::string fileName)
	{
		Definer* def = getFirstNodeFromFile(fileName);
		loadPrototypes(def);
	}

	void loadPrototypes(Definer* def)
	{
		std::string name = def->getName();

		if (name != "prototypes")
		{
			return;
		}

		std::vector<Definer*>* prototypeVector = def->getChildren();

		for (unsigned int i = 0; i < prototypeVector->size(); i++)
		{
			Definer* tempDef = (*prototypeVector)[i];

			Entity* prototype = CORE_Factory::generateGameObject(tempDef);
			std::string prototypeName = tempDef->getVariable("name");

			if (prototype)
			{
				addPrototype(prototypeName, prototype);
			}
		}
	}

	void addPrototype(std::string name, Entity* prototype)
	{
		if (prototype && prototypes.find(name) == prototypes.end())
		{
			prototypes[name] = prototype;
		}

		else if(!prototype)
		{
			//TODO: log error cannot add NULL prototype
		}

		else
		{
			//TODO: log error or warning a prototype of this name already exists
		}
	}
#pragma endregion

#pragma region Resource Storage Structures
	std::map<std::string, SDL_Texture*> loadedTextures;
	std::map<std::string, Mix_Chunk*> loadedSounds;
	std::map<std::string, Mix_Music*> loadedMusic;
	std::map<std::string, TTF_Font*> loadedFonts;
	std::map<std::string, RenderableCharSet*> loadedCharSets;
	std::unordered_set<std::string> loadedFiles;
#pragma endregion

#pragma region Game Object Storage Structures
	std::map<std::string, Environment*> environments;
	std::map<std::string, MenuSystem*> menuSystems;
	std::map<std::string, Entity*> prototypes;
	std::map<std::string, TemplateDef*> templates;
#pragma endregion

	Definer* getTopNodeFromFile(std::string fileName)
	{
		return NULL;
	}

	Definer* getFirstNodeFromFile(std::string fileName)
	{
		pugi::xml_document* doc = new pugi::xml_document();
		pugi::xml_parse_result* result = new pugi::xml_parse_result(
			doc->load_file(fileName.c_str()));
		pugi::xml_node* node = new pugi::xml_node(doc->first_child());

		return CORE_Factory::generateDefiner(*node);
	}
}