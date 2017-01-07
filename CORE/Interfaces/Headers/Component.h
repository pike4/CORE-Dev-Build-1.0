#pragma once
#include "Controllable.h"
#include "Data.h"
#include <stdlib.h>
#include <vector>

class Room;
class Entity;

typedef struct _field
{
	std::string name;
	void* pointer;
}field;

class Component : public Controllable
{
public:
	Component();

	virtual void assignPointers(Entity* parent);

	virtual void registerSelf(Entity* newParent);

	std::vector<int> events = std::vector<int>();
	std::vector<field> pointers = std::vector<field>();

	Entity* parent;
	int zIndex = 1;

	virtual Component* spawnCopy();
protected:

	//ID to *almost certainly* uniquely identify every componenet and entity in order to 
	//prevent hash collisions between parent and child variables of the same name.
	std::string ID;
};