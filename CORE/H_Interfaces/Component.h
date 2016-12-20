#pragma once
#include "Controllable.h"
#include <stdlib.h>
#include <vector>

class Room;
class Entity;

typedef struct _field
{
	std::string name;
	unsigned char size;
	void* pointer;
}field;

class Component : public Controllable
{
public:
	Component();

	void assignPointers(Entity* parent);

	//Search up to the top-level parent for the pointer with the given name
	void* findAncestorPointer(std::string name) const;

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