#include "VideoManager.h"
#include "Visible.h"
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_TTF.h"
#include <string>


#pragma region Initialization Methods
bool VideoManager::start()
{
	if (!InitSDL())
	{
		printf("SDL Initialization failed!");
		return false;
	}

	if (!InitWindow(640, 480, "Deez nutz", false))
	{
		printf("Window Initialization Failed!");
		return false;
	}
}

bool VideoManager::InitSDL()
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

bool VideoManager::InitWindow(int w, int h, std::string name, bool isFullscreen)
{
	mWindow = SDL_CreateWindow("Deez Nuts", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	mScreenSurface = SDL_GetWindowSurface(mWindow);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);

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

#pragma region Manager Implementation Methods
void VideoManager::update()
{
	updateQueue();

	SDL_RenderClear(mRenderer);

	for (int x = 0; x < drawingVector.size(); x++)
	{
		//applyTexture(drawingVector[x]->getX(), drawingVector[x]->getY(), mRenderer, drawingVector[x]->mTexture);
		drawingVector[x]->draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void VideoManager::addVisible(Visible* visible)
{
	drawingVector.push_back(visible);
}

void VideoManager::removeVisible(Visible* V)
{
	for (int x = 0; x < drawingVector.size(); x++)
	{
		if (drawingVector[x] == V)
		{
			drawingVector.erase(drawingVector.begin() + x);
			return;
		}
	}
}

#pragma endregion

#pragma region Draw Methods
void VideoManager::setScreenBackground(int r, int g, int b)
{
	SDL_Rect scrRect;

	scrRect.x = 0;
	scrRect.y = 0;
	scrRect.w = 480;
	scrRect.h = 640;


	SDL_RenderFillRect(mRenderer, &scrRect);
}

void VideoManager::applyTexture(int x, int y, SDL_Renderer* destination, SDL_Texture* source)
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

	SDL_RenderCopy(destination, source, &src, &dest);
}

void VideoManager::applyTexture(int x, int y, SDL_Renderer* destination, SDL_Texture* source, double rotation, SDL_RendererFlip flip, SDL_Point point)
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

void VideoManager::setScreenBackground(std::string filename)
{

}

#pragma endregion

SDL_Texture* VideoManager::loadTexture(string fileName)
{
	SDL_Surface* loadedTexture = IMG_Load(fileName.c_str());
	SDL_Texture* optimizedSurface = NULL;

	if (loadedTexture == NULL)
	{
		printf("Could not find image\n");
	}

	else
	{

		optimizedSurface = SDL_CreateTextureFromSurface(mRenderer, loadedTexture);

		SDL_FreeSurface(loadedTexture);
	}

	return optimizedSurface;
}



SDL_Window* VideoManager::mWindow;
SDL_Renderer* VideoManager::mRenderer;
SDL_Surface* VideoManager::mScreenSurface;
std::vector <Visible*> VideoManager::drawingVector;

void FlashCommand::execute()
{
	printf(b.c_str());
}