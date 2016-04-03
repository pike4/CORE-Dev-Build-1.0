#pragma once

#include "SDL.h"
#include "Globals.h"
#include "_Manager.h"
#include <string>
#include <queue>
#include "Commands.h"
#include "GUI.h"
#include "Visible.h"
#include "ManagerArgs.h"

using namespace std;




class VideoManager : public Manager
{
public:

	static int state;

	static SDL_Window* mWindow;
	static SDL_Surface* mScreenSurface;
	static SDL_Renderer* mRenderer;
	static SDL_Renderer* mRenderer2;
//Methods involving engine setup and window initialization
#pragma region Initialization Methods

	//TODO: Make this an override method for the manager abstract class
	static bool start();
	static bool start(VideoManagerArgs* args);

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

	static void update();
	static void drawCurrentGUI();

	static void updateRunning();
	static void updateInMenu();
	static void updatePaused();
	static void updateBlocking();

	static void goToBlocking();
	static void goToPaused();
	static void goToRunning();
	static void goToInMenu();

	static void addVisible(Visible* visible);
	static GUI* currentGUI;

private:
	static std::vector <Visible*> gameObjectDrawingVector;
	static std::vector <Visible*>* GUIDrawingVector;
};