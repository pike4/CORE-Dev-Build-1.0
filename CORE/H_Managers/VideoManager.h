#pragma once

#include "SDL.h"
#include "Globals.h"
#include "_Manager.h"
#include <string>
#include <queue>
#include "Commands.h"
#include "Visible.h"

using namespace std;




class VideoManager : public Manager
{
public:

	static int state;

	static SDL_Window* mWindow;
	static SDL_Surface* mScreenSurface;
	static SDL_Renderer* mRenderer;

//Methods involving engine setup and window initialization
#pragma region Initialization Methods

	//TODO: Make this an override method for the manager abstract class
	static bool start();

	//Initialize SDL and its subsystems
	static bool InitSDL();

	//Initialize the engine window
	static bool InitWindow(int w, int h, std::string name, bool isFullscreen);

#pragma endregion

//Methods used for applying surfaces to and drawing on the screen
#pragma region Drawing Methods

	static void setScreenBackground(string filename);

	static void setScreenBackground(int r, int g, int b);

	static void applyTexture(int x, int y, SDL_Renderer* destination, SDL_Texture* source);

	static void applyTexture(int x, int y, SDL_Renderer* destination, SDL_Texture* source, double rotation, SDL_RendererFlip flip, SDL_Point point);

	static void removeVisible(Visible* V);

#pragma endregion

		static SDL_Texture* loadTexture(string fileName);


//TODO: add these methods to all other manager classes and create a manager virtual class
	static void update();

	static void addVisible(Visible* visible);

private:
	static std::vector <Visible*> drawingVector;
};