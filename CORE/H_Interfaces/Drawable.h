#pragma once
#include "SDL.h"

class Drawable
{
public:
	virtual void draw(SDL_Renderer* renderer) = 0;
	int zIndex = 1;
};