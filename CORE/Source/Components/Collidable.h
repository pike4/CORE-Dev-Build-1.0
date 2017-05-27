#pragma once
#include "SDL.h"
#include "Component.h"
#include "Node.h"
#include <vector>

class Room;

class Collidable : public Component
{
public:
	enum collidibleTypes
	{
		eWall, Entity, cPlayer, Button, Bullet, TriggerZone, cCursor, cDoor
	};

	int collidableType;

	SDL_Rect boundingBox;
	SDL_Rect movementVector;

	Collidable::Collidable(Node* definer);
	Collidable(int, int, int, int);
	Collidable(Node* definer, std::vector<Collidable*>* collidableVector);
	Collidable(Collidable&);

	Collidable* spawnCopy();

	virtual void move(int x, int y);
	
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	virtual ~Collidable();
	
	int* prevXPtr;
	int* prevYPtr;

	void onCollide(Collidable*);
};