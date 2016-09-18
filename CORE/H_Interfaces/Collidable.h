#pragma once
#include "SDL.h"
#include "pugixml.hpp"
#include "UpdatableComponent.h"
#include <vector>

class BouncingBall;
class Player;
class Cursor;
class Door;
class Room;

class Collidable : public Component
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
	Collidable(pugi::xml_node node, Room* room);
	Collidable(Collidable&);
	Collidable(Collidable&, Room* room);

	Collidable* spawnCopy();

	virtual void move(int x, int y);
	

	virtual void addTo(Room*);

	virtual ~Collidable();
	
	int* prevXPtr;
	int* prevYPtr;

	void onCollide(Collidable*);
};