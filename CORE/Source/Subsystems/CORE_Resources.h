#pragma once
//GameObject Includes
#include "Entity.h"
#include "MenuSystem.h"
#include "Environment.h"

//Resource Includes
#include "RenderableCharSet.h"
#include "Node.h"
#include "TemplateDef.h"
#include "EventDef.h"
#include "State.h"
#include "StateOffsetCalculator.h"
#include "EventHandler.h"

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

/*
   Purpose:
      1. Provide a global point of access to various constructed resources
         such as character sets, string variables, and Entity prototypes
      2. Provide access to global States
*/

namespace CORE_Resources
{
	void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

	Entity* getPrototype(std::string prototypeName);
	TemplateDef* getTemplate(std::string name);
	Environment* getEnvironment(std::string environmentName);
	MenuSystem* getMenuSystem(std::string menuName);

   StateOffsetCalculator* getStateOffsetCalculator(std::vector<std::string> variables);

   //Get the value of the given variable from the default GLOBAL_STATE state
   template <typename T>
   T getStateValue(std::string variableName)
   {
       return getStateValue<T>("GLOBAL_STATE", variableName);
   }

   //Get the value of the given variable from the given state
   template <typename T>
   T getStateValue(std::string stateName, std::string variableName)
   {
      if (globalStates.find(stateName) != globalStates.end())
      {
         if (globalStates[stateName]->variableOfTypeExists<T>(variableName))
         {
            return globalStates[stateName]->getValue<T>(variableName);
         }

         else
         {
            CORE_SystemIO::error("Requested variable does not exist");
            return 0;
         }
      }
   }

   //Set the value of the given variable from the given state
   template <typename T>
   void setStateValue(std::string stateName, std::string variableName, T newValue)
   {
      if (globalStates.find(stateName) != globalStates.end())
      {
         if (globalStates[stateName]->variableOfTypeExists<T>(variableName)) 
         {
            globalStates[stateName]->setValue<T>(variableName, newValue);
         }

         else 
         {
            CORE_SystemIO::error("Requested variable does not exist");
         }
      }
   }

	//****************************
	//Resource Storage Structures
	//****************************
	extern std::map<std::string, SDL_Texture*> loadedTextures;
	extern std::map<std::string, Mix_Chunk*> loadedSounds;
	extern std::map<std::string, TTF_Font*> loadedFonts;
	extern std::map<std::string, Mix_Music*> loadedMusic;
	extern std::map<std::string, RenderableCharSet*> loadedCharSets;
	extern std::unordered_set<std::string> loadedFiles;
	extern std::map<std::string, std::string> stringVariables;
   
   extern std::map<std::string, EventDef> events;
   extern std::map<std::string, EventHandler*> eventHandlers;
   extern std::map<std::string, StateOffsetCalculator*> stateOffsets;
   extern std::map<std::string, State*> globalStates;

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
	void loadTemplates(Node* definer);

	//*****************
	//Prototyping
	//*****************
	void loadPrototypes(std::string fileName);
	void loadPrototypes(Node* def);
	void addPrototype(std::string name, Entity* prototype);

   //*****************
   //Events
   //*****************
   void loadEvents(Node* def);
   void loadEventHandlers(Node* def);

	Node* getTopNodeFromFile(std::string fileName);
	Node* getFirstNodeFromFile(std::string fileName);

   //*****************
   //String variables
   //*****************
   std::string resolveVariable(std::string variableName);
   std::string checkVariable(std::string variableName);
}