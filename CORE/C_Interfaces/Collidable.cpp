#include "Collidable.h"
#include "ObjectManager.h"
#include "stdio.h"
#include "pugixml.hpp"
#include "Room.h"
#include <vector>

Collidable::Collidable(int x, int y, int w, int h)
{
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = w;
	boundingBox.h = h;

	ObjectManager::addCollidable(this);
}

Collidable::Collidable(pugi::xml_node node)
{
	boundingBox.x = atoi(node.child("x").first_child().value());
	boundingBox.y = atoi(node.child("y").first_child().value());
	boundingBox.w = atoi(node.child("w").first_child().value());
	boundingBox.h = atoi(node.child("h").first_child().value());
}

Collidable::Collidable(pugi::xml_node node, std::vector<Collidable*>* collidableVector)
	:Collidable(node)
{
	collidableVector->push_back(this);
}

Collidable::Collidable(pugi::xml_node node, Room* room)
	:Collidable(node)
{
	room->collidableVector->push_back(this);
}

Collidable::Collidable(Collidable& other)
	:Collidable(other.boundingBox.x, other.boundingBox.y, other.boundingBox.w, other.boundingBox.h)
{
	collidableType = other.collidableType;
}

Collidable::Collidable(Collidable& other, Room* room)
	:Collidable(other)
{
	room->collidableVector->push_back(this);
}

Collidable* Collidable::spawnCopy()
{
	return new Collidable(*this);
}

void Collidable::move(int x, int y)
{
	boundingBox.x = x;
	boundingBox.y = y;
}

void Collidable::addTo(Room* room)
{
	if (room != NULL)
	{
		room->collidableVector->push_back(this);
	}
}

void Collidable::handleInput(int key, int upDown, int x, int y)
{
	
}

Collidable::~Collidable()
{
	printf("a\n");
}

void Collidable::onCollide(Collidable* C)
{
	switch (C->collidableType)
	{

	default:
		break;
	}
}