#pragma once

#include "Commands.h"
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

namespace CORE_Graphics
{

}

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

	//TODO: Make this an override method for the manager abstract class
	bool start();

	//Initialize SDL and its subsystems
	bool InitSDL();

	//Initialize the engine window
	bool InitWindow(int w, int h, std::string name, bool isFullscreen);

	void addDraw(int x, int y, texture tex, int zIndex);

#pragma endregion

//Methods used for applying surfaces to and drawing on the screen
#pragma region Drawing Methods

	void setScreenBackground(string filename);

	void setScreenBackground(int r, int g, int b);

	void getAnimationFromSpriteSheet(int framesX, int framesY, int frameW, int frameH,
		int seperation, std::string fileName, VisibleElement** outFrmaes);
#pragma endregion

	void update();

	void addVisible(Visible* visible);

	void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

	void applyTexture(int x, int y, SDL_Texture* source);

	void applyTexture(int x, int y, SDL_Renderer* destination, SDL_Texture* source,
			double rotation, SDL_RendererFlip flip, SDL_Point point);

};