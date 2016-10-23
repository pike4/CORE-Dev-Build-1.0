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
	void assignPointers(Entity* parent);

	virtual void registerSelf(Entity* newParent);

	std::vector<int> events = std::vector<int>();
	std::vector<field> pointers = std::vector<field>();

	Entity* parent;

	virtual Component* spawnCopy();
private:
	
};