#pragma once
#include "pugixml.hpp"
#include "Component.h"
#include <vector>

class Room;

class BaseObject
{
public:
	int x, y;

	BaseObject(int x, int y);
	BaseObject(pugi::xml_node, std::vector<BaseObject*>* objectVector);
	BaseObject(pugi::xml_node, Room* room);
	BaseObject(pugi::xml_node node);

	BaseObject(BaseObject& other);
	BaseObject(BaseObject& other, Room* room);

	virtual void add(Room*);
	virtual void move(int x, int y);

	virtual BaseObject* spawnCopy(Room* room);
	virtual BaseObject* spawnCopy();
};