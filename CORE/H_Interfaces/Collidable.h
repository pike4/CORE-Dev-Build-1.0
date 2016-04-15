#pragma once
#include "SDL.h"
#include "pugixml.hpp"

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
	Collidable(pugi::xml_node);
	virtual ~Collidable();
	
	int* prevXPtr;
	int* prevYPtr;

	void onCollide(Collidable*);
	virtual void onCollide(BouncingBall*) = 0;
	virtual void onCollide(Player*) = 0;
	virtual void onCollide(Cursor*) = 0;
};