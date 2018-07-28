#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "CORE.h"
#include "CORE_Audio.h"
#include "CORE_SystemIO.h"
#include "CORE_Graphics.h"
#include "CORE_Devices.h"
#include "MenuScreen.h"
#include "Node.h"
#include "TemplateDef.h"
#include "Entity.h"

#include "SDL.h"
#include "pugixml.hpp"
#include<map>

namespace CORE_Resources
{
	lua_State* L;
	void handle(Event e)
	{

	}

#pragma region Resource Storage Structures
	std::map<std::string, SDL_Texture*> loadedTextures;
	std::map<std::string, Mix_Chunk*> loadedSounds;
	std::map<std::string, Mix_Music*> loadedMusic;
	std::map<std::string, TTF_Font*> loadedFonts;
	std::map<std::string, RenderableCharSet*> loadedCharSets;
	std::map<std::string, std::string> stringVariables;
	std::unordered_set<std::string> loadedFiles;
	std::map<std::string, StateOffsetCalculator*> stateOffsets;
	std::map<std::string, State*> globalStates;
#pragma endregion

#pragma region Event and Event Handler Storage
	std::map<std::string, EventDef> events;
	std::map<std::string, int> eventCodes;
	std::map<std::string, EventHandler*> eventHandlers;
#pragma endregion

#pragma region Game Object Storage Structures
	std::map<std::string, Environment*> environments;
	std::map<std::string, MenuSystem*> menuSystems;
	std::map<std::string, Entity*> prototypes;
	std::map<std::string, TemplateDef*> templates;
#pragma endregion

	int eventID = 10000;

	void start()
	{
		//Define some predefined events
		predefineEvent(mouse1Down, "mouse1Down", { _integer, _integer });
		predefineEvent(mouse1Up, "mouse1Up", { _integer, _integer });
		predefineEvent(mouse2Down, "mouse2Down", { _integer, _integer });
		predefineEvent(mouse2Up, "mouse2Up", { _integer, _integer });
		predefineEvent(mouseMoved, "mouseMoved", { _integer, _integer });
		predefineEvent(collision, "collision", { _entity, _entity });
		predefineEvent(selfCollision, "selfCollision", { _entity });
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
			XMLNode topDef = CORE_Factory::generateNode(node);
			std::string name = topDef.getName();

			if (name == "imports")
			{
				loadImports(topDef);
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

			else if (name == "events")
			{
				loadEvents(topDef);
			}

			else if (name == "eventHandlers")
			{
				loadEventHandlers(topDef);
			}

			else if (name == "menuSystem")
			{
				new MenuSystem(topDef);
			}

			else if (name == "sounds")
			{
				loadSounds(topDef);
			}

			else if (name == "music")
			{
				loadTracks(topDef);
			}

			else if (name == "strings")
			{
				loadStrings(topDef);
			}

			else if (name == "states")
			{
				loadStates(topDef);
			}

			node = node.next_sibling();
		}
	 }
#pragma endregion

#pragma region Asset Loading
	// Load and return the texture of the given file name
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

	// Load and return a music track of the given file name
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

	// Load and return an audio chunk of the given file name
	Mix_Chunk* loadSound(std::string fileName)
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

	//
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

	// Load sounds from the given node
	void loadSounds(XMLNode node)
	{
		std::vector<XMLNode> children = node.getChildren();

		for (int i = 0; i < children.size(); i++)
		{
			std::string name = children[i].getName();
			std::string file = children[i].getVariable("file");

			if (name.empty() || file.empty()) {
				CORE_SystemIO::error("Bad sounds list in XML");
			}

			else {
				CORE_Audio::addSound(name, file);
			}
		}
	}

	void loadStrings(XMLNode node)
	{
		std::vector<XMLNode> variableNodes = node.getChildren();

		for (unsigned int i = 0; i < variableNodes.size(); i++)
		{
			XMLNode curNode = variableNodes[i];

			std::string variableName = curNode.getName();
			std::string newStringVariable = curNode.getMainValue();

			if (!newStringVariable.empty() && !variableName.empty())
			{
				if (stringVariables.find(newStringVariable) == stringVariables.end())
				{
					stringVariables[variableName] = newStringVariable;
				}
			}

			else
			{
				//TODO dev output instead
				CORE_SystemIO::print("Multiple instantiations of string variable \'" +
					variableName + "\'");
			}
		}
	}

	void loadImports(XMLNode node)
	{
		std::vector<XMLNode> curChildren = node.getChildren();

		for (unsigned int i = 0; i < curChildren.size(); i++)
		{
			XMLNode curImportDef = curChildren[i];
			std::string importName = curImportDef.getName();
			loadResourceFile(importName);
		}
	}

	// Load music tracks from the given node
	void loadTracks(XMLNode node)
	{
		std::vector<XMLNode> children = node.getChildren();

		for (int i = 0; i < children.size(); i++)
		{
			std::string name = children[i].getName();
			std::string file = children[i].getVariable("file");

			if (name.empty() || file.empty()) {
				CORE_SystemIO::error("Bad sounds list in XML");
			}

			else {
				CORE_Audio::addTrack(name, file);
			}
		}
	}

	void loadStates(XMLNode node)
	{
		std::vector<XMLNode> stateChildren = node.getChildren();

		for (unsigned int i = 0; i < stateChildren.size(); i++)
		{
			XMLNode curNode = stateChildren[i];
			std::string name = curNode.getName();

			State* newState = CORE_Factory::generateState(curNode);
			if (globalStates.find(name) == globalStates.end())
			{
				globalStates[name] = newState;
			}

			else
			{
				CORE_SystemIO::error("State: " + name + "already exists");
			}
		}
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

		Mix_Chunk* newSound = loadSound(fileName);
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
		XMLNode def = getFirstNodeFromFile(fileName);
		loadTemplates(def);
	}

	void loadTemplates(XMLNode def)
	{
		if (def.getName() == "templates")
		{
			std::vector<XMLNode> templateVector = def.getChildren();

			for (unsigned int i = 0; i < templateVector.size(); i++)
			{
				XMLNode curDefiner = templateVector[i];

				TemplateDef* newTemplate = new TemplateDef(curDefiner);

				templates[newTemplate->name] = newTemplate;
			}
		}
	}
#pragma endregion

#pragma region Prototyping
	void loadPrototypes(std::string fileName)
	{
		XMLNode def = getFirstNodeFromFile(fileName);
		loadPrototypes(def);
	}

	/**
	Function: loadPrototype

	Purpose:
		Load entity prototypes from the given node and store for global access
	*/
	void loadPrototypes(XMLNode def)
	{
		if ( def.null() )
		{
			 CORE_SystemIO::error("Null events node!");
			 return;
		}

		std::string name = def.getName();

		if (name != "prototypes")
		{
			 CORE_SystemIO::error("loadPrototypes was called with node: "
				  + name + " must be called with prototypes node");
			return;
		}

		std::vector<XMLNode> prototypeVector = def.getChildren();

		for (unsigned int i = 0; i < prototypeVector.size(); i++)
		{
			XMLNode tempDef = prototypeVector[i];

			Entity* prototype = (Entity*) CORE_Factory::generateObject(tempDef);
			std::string prototypeName = tempDef.getVariable("name");

			if (prototype)
			{
				addPrototype(prototypeName, prototype);
			}
		}
	}

	/**
	Function: addPrototype

	Purpose:
		Store a prototype of the given name for global access
	*/
	void addPrototype(std::string name, Entity* prototype)
	{
		if (prototype && prototypes.find(name) == prototypes.end())
		{
			prototypes[name] = prototype;
		}

		else if(!prototype)
		{
			CORE_SystemIO::error("Entity prototype " + name + " is undefined and cannot be added");
		}

		else
		{
			CORE_SystemIO::error("a prototype of this name already exists");
		}
	}

#pragma endregion

#pragma region Events
	/**
		Function: getEventCode

		Purpose:
			Get the event code for the given event name
	*/
	int getEventCode(std::string name)
	{
		if (eventCodes.find(name) != eventCodes.end())
		{
			return eventCodes[name];
		}

		CORE_SystemIO::error("Event " + name + " not found");
		return keyError;
	}

	/**
	Function: loadEvents

	Purpose:
		Load the event definitions from the given node and store for global access
	*/
	void loadEvents(XMLNode def)
	{
		 if (def.null() )
		 {
			  CORE_SystemIO::error("Null events node!");
			  return;
		 }

		 std::string name = def.getName();

		std::vector<XMLNode>  eventNodes = def.getChildren();

		 for (unsigned int i = 0; i < eventNodes.size(); i++) 
		 {	 
			  XMLNode cur = eventNodes[i];
			  std::string curName = cur.getName();

			  if (events.find(curName) != events.end()) 
			  {
					CORE_SystemIO::error("Event " + curName + " already defined");
			  }

			  else 
			  {
					EventDef newEvent(cur);
					eventCodes[curName] = eventID++;
					events[curName] = newEvent;
			  }
		 }
	}

	/**
	Function: loadEventHandlers

	Purpose:
		Define event handler prototypes from the given node
	*/
	void loadEventHandlers(XMLNode def)
	{
		if (def.null())
		{
			CORE_SystemIO::error("Null event handlers node!");
			return;
		}

		std::vector<XMLNode> handlerVector = def.getChildren();

		for (unsigned int i = 0; i < handlerVector.size(); i++)
		{
			XMLNode curHandlerNode = handlerVector[i];
			std::string handlerName = curHandlerNode.getName();
			std::vector<CORE_TypeTraits::PrimitiveType> handlerFormat;

			if (eventHandlers.find(handlerName) == eventHandlers.end())
			{
				//Parse the format from the format node
				EventHandler* newHandler = CORE_Factory::constructEventHandler(curHandlerNode);

				if (newHandler)
				{
					eventHandlers[handlerName] = newHandler;
				}
			}

			else
			{
				CORE_SystemIO::error("EventHandler \'" + handlerName + "\' is already defined");
			}
		}
	}

	/**
	Function: getEventHandler

	Purpose:
		Get an event handler, returning NULL if not available
	*/
	EventHandler* getEventHandler(std::string name)
	{
		if (eventHandlers.find(name) != eventHandlers.end())
		{
			return eventHandlers[name]->spawnCopy();
		}

		return NULL;
	}

	void predefineEvent(int opCode, std::string name, std::vector<PrimitiveType> format)
	{
		if (eventCodes.find(name) == eventCodes.end() && events.find(name) == events.end())
		{
			eventCodes[name] = opCode;
			events[name] = EventDef(name, format);
		}

		else
		{
			CORE_SystemIO::error("Event " + name + " already defined");
		}
	}
#pragma endregion

	/**
	Function: resolveVariable

	Purpose:
		Return the value of the global string variable of the given name
	*/
	std::string resolveVariable(std::string variableName)
	{
		 std::string ret = "";

		 if (variableName[0] == '$')
		 {
			  variableName = variableName.substr(1);

			  if (stringVariables.find(variableName) != stringVariables.end())
			  {
					ret = stringVariables[variableName];
			  }

			  else
			  {
					//TODO make error
					CORE_SystemIO::print("Undefined variable: " + variableName);
			  }
		 }

		 else
		 {
			  //TODO make dev error
			  CORE_SystemIO::print("Malformed variable name: " + variableName + 
				  " - Variable names must be lead by $\n");
		 }

		 return ret;
	}

	/**
	Function: checkVariable

	Purpose:
		Check if the given string is the name of a defined global variable, returning 
		the value if defined, the original string otherwise
	*/
	std::string checkVariable(std::string variableName)
	{
		 std::string ret = variableName;

		 if (variableName[0] == '$')
		 {
			  variableName = variableName.substr(1);

			  if (stringVariables.find(variableName) != stringVariables.end())
			  {
					ret = stringVariables[variableName];
			  }
		 }

		 return ret;
	}

	//--------------------------------------------------------------------------------------------------

	StateOffsetCalculator* getStateOffsetCalculator(std::vector<std::string> variables)
	{
		 StateOffsetCalculator* ret = NULL;

		 //Vector must be even: these are name-size pairs
		 if (variables.size() % 2)
			  return NULL;

		 std::vector<std::string>  names;
		 int runningSize = 0;
		 int temp = 0;

		 //Extract the names to a new vector for sorting 
		 //and temporarily store the sizes in the offsets map
		 for (unsigned int i = 0; i < variables.size(); i += 2)
		 {
			  int newSize = CORE_TypeTraits::getDataObjectSize(variables[i + 1]);
			  if (newSize == -1)
					CORE_SystemIO::error("Undefined type in offset calculator constructor");



			  names.push_back("_" + variables[i] + "-" + std::to_string(newSize));
		 }

		 //Lexographically sort the names
		 std::sort(names.begin(), names.end(), std::less<std::string>());

		 //The string containing all name-size pairs for the requested offsetCalculator
		 std::string fullName = "";

		 //Concatenate the sorted names and sizes into a string to look up the offset calculator
		 for (unsigned int i = 0; i < names.size(); i++)
		 {
			  fullName += names[i];
		 }

		 if (stateOffsets.find(fullName) != stateOffsets.end())
		 {
			  ret = stateOffsets[fullName];
		 }

		 else
		 {
			  //Create and store a new offset calculator if one is not available
			  ret = new StateOffsetCalculator(variables);
			  stateOffsets[fullName] = ret;
		 }

		 return ret;
	}

	//--------------------------------------------------------------------------------------------------

	XMLNode getFirstNodeFromFile(std::string fileName)
	{
		pugi::xml_document* doc = new pugi::xml_document();
		pugi::xml_parse_result* result = new pugi::xml_parse_result(
			doc->load_file(fileName.c_str()));
		pugi::xml_node* node = new pugi::xml_node(doc->first_child());

		return CORE_Factory::generateNode(*node);
	}
}