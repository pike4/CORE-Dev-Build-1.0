#include "CORE.h"
#include "CORE_Devices.h"
#include "CORE_Resources.h"

#include "SDL.h"

namespace CORE_Devices
{
	void start()
	{
		keyMap[SDLK_w].push_back(walkForwardButtonDown);
		keyMap[SDLK_s].push_back(walkBackwardButtonDown);
		keyMap[SDLK_a].push_back(walkLeftButtonDown);
		keyMap[SDLK_d].push_back(walkRightButtonDown);
		keyMap[SDL_MOUSEMOTION].push_back(mouseMoved);
		keyMap[SDL_MOUSEBUTTONDOWN].push_back(mouse1Down);
		keyMap[SDL_MOUSEBUTTONUP].push_back(mouse1Up);
	}

	void update()
	{
		while (SDL_PollEvent(&e))
		{

			switch (e.type)
			{
				case SDL_QUIT:
				{
					CORE::quit = true;
					break;
				}
			
				case SDL_KEYDOWN:
				{
					if (e.key.repeat)
						break;
					notifyStateManager(e.key.keysym.sym, BUTTON_DOWN);
					break;
				}

				case SDL_KEYUP:
				{
					notifyStateManager(e.key.keysym.sym, BUTTON_UP);
					break;
				}

				case SDL_MOUSEMOTION:
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					notifyStateManager(SDL_MOUSEMOTION, 0, x, y);
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					notifyStateManager(SDL_MOUSEBUTTONDOWN, 1, x, y);
					break;
				}

				case SDL_MOUSEBUTTONUP:
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					notifyStateManager(SDL_MOUSEBUTTONUP, 0, x, y);
					break;
				}
			}
		}

	}

	void handleEvent(int eventCode, int posOrNeg, int x, int y)
	{

	}

	//Maps the current keycode to all of its matching CORE events and passes them to the State
	//Manager along with some other info as needed
	void notifyStateManager(int keyCode, int posOrNeg, int x, int y)
	{
		if (keyMap.find(keyCode) != keyMap.end())
		{
			for (unsigned int i = 0; i < keyMap[keyCode].size(); i++)
			{
				CORE::handleEvent(keyMap[keyCode][i],  posOrNeg, x, y);
			}
		}
	}
	
	SDL_Event e;
	int state;
	std::map<int, std::vector<int>> keyMap;
}