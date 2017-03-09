#pragma once

#include "MenuScreen.h"
#include "Visible.h"
#include "Room.h"
#include "DrawOrder.h"

#include "SDL.h"
#include <string>
#include <queue>

using namespace std;

class VisibleElement;
class Entity;

/*
   Purpose: To expose a common, public API to the rest of the engine for:
   
   1. Decoupling engine implementation from third party graphics libraries
   2. Getting graphical assets such as images and fonts from the system
   3. Drawing CORE-defined graphical primitives
   4. Enqueueing draws so that they occur asynchronously from other steps in the game loop and in a 
      proper order
*/

namespace CORE_Graphics
{
	extern int state;

	extern SDL_Window* mWindow;
	extern SDL_Surface* mScreenSurface;
	extern SDL_Renderer* mRenderer;
	extern SDL_Renderer* mRenderer2;

	extern int* xOffset;
	extern int* yOffset;
	extern int xOffsetInitial;
	extern int yOffsetInitial;

	extern MenuScreen* currentGUI;
	extern Room* currentRoom;

	extern std::vector <Visible*>* gameObjectDrawingVector;
	extern std::vector <Visible*>* GUIDrawingVector;
	extern std::priority_queue<drawOrder> drawQueue;

//Methods involving engine setup and window initialization
#pragma region Initialization Methods

	//Initialize Graphics subsystem
	bool start();

	//Initialize SDL and its subsystems
	bool InitSDL();

	//Initialize the display window
	bool InitWindow(int w, int h, std::string name, bool isFullscreen);

	//Enqueue a visible element to draw
	void addDraw(int x, int y, texture tex, int zIndex);

#pragma endregion

//Methods used for applying surfaces to and drawing on the screen
#pragma region Drawing Methods
	void setScreenBackground(string filename);

	void setScreenBackground(int r, int g, int b);

   //TODO to return a "texture" object once it is implemented 
   SDL_Texture* loadSprite(std::string fileName);

	void getAnimationFromSpriteSheet(int framesX, int framesY, int frameW, int frameH,
		int seperation, std::string fileName, VisibleElement** outFrames);
#pragma endregion

	void update();

	void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

   void drawRect(int x, int y, int w, int h, SDL_Color color);

	void applyTexture(int x, int y, SDL_Texture* source);

	void applyTexture(int x, int y, SDL_Texture* source,
			double rotation, SDL_RendererFlip flip, SDL_Point point);
};