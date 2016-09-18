#pragma once
#include <stdlib.h>

class Room;
class GameObject;

class Component
{
public:
	virtual void addTo(Room*) = 0;
	virtual void addTo(GameObject*);
	virtual void move(int x, int y) = 0;

	GameObject* parent;

	virtual Component* spawnCopy() 
	{
		//TODO: warning this should not have been called, please overload
		return NULL;
	};
private:
	
};