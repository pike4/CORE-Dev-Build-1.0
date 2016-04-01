#pragma once
#include "SDL.h"

class BouncingBall;
class Player;
class Cursor;

class Collidable
{
public:
	static enum collidibleTypes
	{
		eWall, Entity, cPlayer, Button, Bullet, TriggerZone, cCursor
	};

	int collidableType;

	SDL_Rect boundingBox;
	SDL_Rect movementVector;

	Collidable(int, int, int, int);
	virtual ~Collidable();
	
	int* prevXPtr;
	int* prevYPtr;

	void onCollide(Collidable*);
	virtual void onCollide(BouncingBall*) = 0;
	virtual void onCollide(Player*) = 0;
	virtual void onCollide(Cursor*) = 0;
};