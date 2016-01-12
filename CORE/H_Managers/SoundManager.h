#include "SDL.h"
#include "SDL_Mixer.h"
#include "Commands.h"
#include "_Manager.h"

#pragma once

class SoundManager : public Manager
{
public:

	static bool start();

	static void update();

};

