#pragma once
#include "SDL.h"

class BouncingBall;
class Player;

class Collidable
{
public:
	static enum collidibleTypes
	{
		Wall, Entity, cPlayer, Button, Bullet, TriggerZone
	};

	SDL_Rect boundingBox;
	SDL_Rect movementVector;

	Collidable(int, int, int, int);
	virtual ~Collidable();
	
	int* prevXPtr;
	int* prevYPtr;

	virtual void onCollide(Collidable*) = 0;
	virtual void onCollide(BouncingBall*) = 0;
	virtual void onCollide(Player*) = 0;
};