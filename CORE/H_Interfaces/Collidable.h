#pragma once
#include "SDL.h"
#include "pugixml.hpp"
#include <vector>

class BouncingBall;
class Player;
class Cursor;
class Door;
class Room;

class Collidable
{
public:
	static enum collidibleTypes
	{
		eWall, Entity, cPlayer, Button, Bullet, TriggerZone, cCursor, cDoor
	};

	int collidableType;

	SDL_Rect boundingBox;
	SDL_Rect movementVector;

	Collidable::Collidable(pugi::xml_node node);
	Collidable(int, int, int, int);
	Collidable(pugi::xml_node, std::vector<Collidable*>* collidableVector);
	Collidable::Collidable(pugi::xml_node node, Room* room);
	virtual ~Collidable();
	
	int* prevXPtr;
	int* prevYPtr;

	void onCollide(Collidable*);
	virtual void onCollide(BouncingBall*) = 0;
	virtual void onCollide(Player*) = 0;
	virtual void onCollide(Cursor*) = 0;
	virtual void onCollide(Door*) = 0;
};