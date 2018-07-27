#pragma once
#include "CORE.h"
#include "Events.h"

#include "SDL.h"
#include <map>

const int BUTTON_UP = 0;
const int BUTTON_DOWN = 1;


//Interfaces with various input devices and maps device input to standard CORE events
namespace CORE_Devices
{
	extern std::map<int, std::vector<int>> keyMap;
	extern std::map<int, int> hwMap;
	extern int state;
	extern SDL_Event e;

	void update();
	void start();

	int getKeyCode(int keyCode);

	void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);
	void notifyStateManager(Event e);
};
