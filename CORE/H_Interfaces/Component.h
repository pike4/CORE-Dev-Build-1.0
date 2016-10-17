#pragma once
#include "Controllable.h"
#include <stdlib.h>
#include <vector>

class Room;
class GameObject;

class Component : public Controllable
{
public:
	virtual void addTo(Room*) {};
	virtual void addTo(GameObject*);
	virtual void move(int x, int y) {};

	virtual void assignPointers(GameObject* parent) {};
	virtual void registerSelf(GameObject* newParent);

	std::vector<int> events;

	GameObject* parent;

	virtual Component* spawnCopy();
private:
	
};