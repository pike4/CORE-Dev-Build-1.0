#include "CORE_Graphics.h"
#include "Visible.h"
#include "CORE.h"
#include "ImageElement.h"
#include "Entity.h"

#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_TTF.h"
#include <string>

namespace CORE_Graphics
{

#pragma region Initialization Methods

	//Initialize graphics subsystems with default parameters
	bool start()
	{
		if (!InitSDL())
		{
			printf("SDL Initialization failed!");
			return false;
		}

		if (!InitWindow(1080, 720, "CORE", false))
		{
			printf("Window Initialization Failed!");
			return false;
		}

		gameObjectDrawingVector = new std::vector<Visible*>;

		return true;
	}

	//TODO: figure out how to get parameters to subsystems at runtime
	//TODO: Initialize graphics subsystems with given parameters
	//bool start(VideoManagerArgs* args)

	void handleEvent(int eventCode, int posOrNeg, int x, int y)
	{

	}

	bool InitSDL()
	{
		bool success = true;
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL failed to initialize!");
			success = false;
		}

		if (IMG_Init(IMG_INIT_PNG) < 0)
		{
			printf("Failed to start SDL_IMG library. Reason: %s", IMG_GetError());
			success = false;
		}

		if (TTF_Init() < 0)
		{
			printf("Failed to start SDL_TTF. Reason: %s", TTF_GetError());
			success = false;
		}

		return success;
	}

	bool InitWindow(int w, int h, std::string name, bool isFullscreen)
	{
		mWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
		mScreenSurface = SDL_GetWindowSurface(mWindow);
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

		if (mWindow == NULL)
		{
			printf("Video Manager failed to create window \n");
			return false;
		}

		if (mScreenSurface == NULL)
		{
			printf("Video Manager failed to create screen surface \n");
			return false;
		}

		else return true;
	}

#pragma endregion

#pragma region Update Methods
	void update()
	{
		SDL_RenderClear(mRenderer);

		if (currentRoom)
		{
			currentRoom->draw();
		}

		for each(MenuScreen* menuScreen in CORE::currentMenuScreens)
		{
			menuScreen->draw();
		}

		while (!drawQueue.empty())
		{
			drawOrder next = drawQueue.top();
			applyTexture(next.x, next.y, next.tex);
			drawQueue.pop();
		}

		SDL_RenderPresent(mRenderer);
		//updateQueue();
	}

	void addVisible(Visible* visible)
	{
		//gameObjectDrawingVector->push_back(visible);
	}

#pragma endregion

#pragma region Draw Methods
	void setScreenBackground(int r, int g, int b)
	{
		//This shouldn't be necessary. SDL_RenderClear handles this
		SDL_Rect scrRect;

		scrRect.x = 0;
		scrRect.y = 0;
		scrRect.w = 480;
		scrRect.h = 640;


		SDL_RenderFillRect(mRenderer, &scrRect);
	}

	void addDraw(int x, int y, texture tex, int zIndex)
	{
		drawOrder newOrder = { x, y, tex, zIndex };
		drawQueue.push(newOrder);
	}

	void applyTexture(int x, int y, SDL_Texture* source)
	{
		SDL_Rect dest;
		SDL_Rect src;

		int w;
		int h;
		int tempX = 0;
		int tempY = 0;

		SDL_QueryTexture(source, NULL, NULL, &w, &h);

		if (xOffset && yOffset)
		{
			tempX = *xOffset;
			tempY = *yOffset;
		}

		if (tempX != x)
		{
			int iawdn = 109;
		}

		dest.x = x - tempX + xOffsetInitial;
		dest.y = y - tempY + yOffsetInitial;
		dest.w = w;
		dest.h = h;

		src.x = 0;
		src.y = 0;
		src.w = w;
		src.h = h;

		SDL_RenderCopy(mRenderer, source, &src, &dest);
	}

	void applyTexture(int x, int y, SDL_Renderer* destination, SDL_Texture* source, double rotation, SDL_RendererFlip flip, SDL_Point point)
	{
		SDL_Rect dest;
		SDL_Rect src;

		int w;
		int h;

		SDL_QueryTexture(source, NULL, NULL, &w, &h);

		dest.x = x;
		dest.y = y;
		dest.w = w;
		dest.h = h;

		src.x = 0;
		src.y = 0;
		src.w = w;
		src.h = h;

		SDL_RenderCopyEx(mRenderer, source, &src, &dest, rotation, &point, flip);
	}

	void setScreenBackground(std::string filename)
	{

	}

#pragma endregion

	void getAnimationFromSpriteSheet(int framesX, int framesY, int frameW, int frameH,
		int seperation, std::string fileName, VisibleElement** outFrames)
	{
		SDL_Surface* mainSurface = IMG_Load(fileName.c_str());
		SDL_Surface* tempSurface = new SDL_Surface;
		SDL_Rect curFrame = { 0, 0, frameW, frameH };
		SDL_Rect blitFrame = { 0, 0, frameW, frameH };
		int totalFramesIndex = 0;

		for (int i = 0; i < framesX; i++)
		{
			for (int j = 0; j < framesY; j++)
			{
				tempSurface = SDL_CreateRGBSurface(0, frameW, frameH, 32, 0, 0, 0, 0);
				printf(SDL_GetError());
				curFrame.x = j * (frameW + seperation);
				curFrame.y = i * (frameH + seperation);
				SDL_BlitSurface(mainSurface, &curFrame, tempSurface, &blitFrame);
				outFrames[totalFramesIndex++] = new ImageElement(0, 0, frameW, frameH,
					SDL_CreateTextureFromSurface(mRenderer, tempSurface));
			}
		}
		SDL_FreeSurface(tempSurface);
	}

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Renderer* mRenderer2;
	SDL_Surface* mScreenSurface;
	std::vector <Visible*>* gameObjectDrawingVector;
	std::vector <Visible*>* GUIDrawingVector;
	std::priority_queue<drawOrder> drawQueue;
	MenuScreen* currentGUI;
	Room* currentRoom;
	int* xOffset = 0;
	int* yOffset = 0;
	int xOffsetInitial = 0;
	int yOffsetInitial = 0;
	int state;
	Entity* player;

}

void DrawRectCommand::execute()
{
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(CORE_Graphics::mRenderer, &r, &g, &b, &a);
	SDL_SetRenderDrawColor(CORE_Graphics::mRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(CORE_Graphics::mRenderer, &rect);
	SDL_SetRenderDrawColor(CORE_Graphics::mRenderer, r, g, b, a);
	SDL_RenderPresent(CORE_Graphics::mRenderer);
}