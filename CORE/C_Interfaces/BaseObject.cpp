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

BaseObject::BaseObject(BaseObject& other)
{
	x = other.x;
	y = other.y;
}

BaseObject::BaseObject(BaseObject& other, Room* room)
	:BaseObject(other)
{
	room->objectVector->push_back(this);
}

BaseObject* BaseObject::spawnCopy(Room* room)
{
	//TODO
	//Throw warning: attempted to generate prototype <prototypeName>. prototype is not of a type with a valid copy constructor. Please imnplement valid copy constructors and spawnCopy overrrides
	return this;
}

BaseObject* BaseObject::spawnCopy()
{
	//TODO
	//Throw warning: attempted to generate prototype <prototypeName>. prototype is not of a type with a valid copy constructor. Please imnplement valid copy constructors and spawnCopy overrrides
	return new BaseObject(*this);
}

void BaseObject::add(Room* room)
{
	if (room != NULL)
	{
		room->objectVector->push_back(this);
	}
}

void BaseObject::move(int aX, int aY)
{
	x = aX;
	y = aY;
}