#pragma once
#include "SDL.h"
#include "Globals.h"
#include "Commands.h"
#include "VideoManager.h"





class EventManager : public Manager
{
public:

	static void update()
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_KEYDOWN)
			{
				VideoManager::enqueue(new FlashCommand("butt"));

				if (e.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
			}

			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				SoundManager::enqueue(new PlayCommand());
			}
		}

	}

	static void start()
	{

	}
};