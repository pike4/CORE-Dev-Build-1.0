#include "BaseObject.h"
#include "pugixml.hpp"
#include <vector>
#include "Room.h"

BaseObject::BaseObject(int x, int y)
{
	this->x = x;
	this->y = y;
}

BaseObject::BaseObject(pugi::xml_node node)
{
	x = atoi(node.child("x").first_child().value());
	y = atoi(node.child("y").first_child().value());
}

BaseObject::BaseObject(pugi::xml_node node, std::vector<BaseObject*>* objectVector) : BaseObject(node)
{
	objectVector->push_back(this);
}

BaseObject::BaseObject(pugi::xml_node node, Room* room) : BaseObject(node)
{
	room->objectVector->push_back(this);
}