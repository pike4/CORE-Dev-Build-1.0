#pragma once

#include <vector>
#include "BaseObject.h"
#include "Updatable.h"
#include "SDL.h"



static std::vector <BaseObject*> EntityVector;

extern SDL_Event e;
extern bool quit;