#pragma once
#include "pugixml.hpp"
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
};