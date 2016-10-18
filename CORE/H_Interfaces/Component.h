#pragma once
#include "Controllable.h"
#include <stdlib.h>
#include <vector>

class Room;
class Entity;

class Component : public Controllable
{
public:
	virtual void move(int x, int y) {};

	virtual void assignPointers(Entity* parent) {};
	virtual void registerSelf(Entity* newParent);

	std::vector<int> events;

	Entity* parent;

	virtual Component* spawnCopy();
private:
	
};