#pragma once
#include "SDL.h"


class Collidable
{
public:
	SDL_Rect boundingBox;
	SDL_Rect movementVector;

	Collidable(int, int, int, int);
	virtual ~Collidable();
	
	int* prevXPtr;
	int* prevYPtr;

	void onCollide();
};