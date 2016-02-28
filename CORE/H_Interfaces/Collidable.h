#pragma once
#include "SDL.h"


class Collidable
{
public:
	SDL_Rect boundingBox;
	Collidable(int, int, int, int);
	virtual ~Collidable();
	

	void onCollide();
};