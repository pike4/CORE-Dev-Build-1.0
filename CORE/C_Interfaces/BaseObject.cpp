#include "BaseObject.h"
#include "pugixml.hpp"

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