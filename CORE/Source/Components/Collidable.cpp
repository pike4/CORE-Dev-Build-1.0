#include "Collidable.h"
#include "CORE_Factory.h"
#include "stdio.h"
#include "Node.h"
#include "Room.h"

#include <vector>

Collidable::Collidable(int x, int y, int w, int h)
{
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = w;
	boundingBox.h = h;
}

Collidable::Collidable(XMLNode definer)
{
	boundingBox.x = Util::toInt(definer.getVariable("x"));
	boundingBox.y = Util::toInt(definer.getVariable("y"));
	boundingBox.w = Util::toInt(definer.getVariable("w"));
	boundingBox.h = Util::toInt(definer.getVariable("h"));
}

Collidable::Collidable(XMLNode definer, std::vector<Collidable*>* collidableVector)
	:Collidable(definer)
{
	collidableVector->push_back(this);
}

Collidable::Collidable(Collidable& other)
	:Collidable(other.boundingBox.x, other.boundingBox.y, other.boundingBox.w, other.boundingBox.h)
{
	collidableType = other.collidableType;
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

void Collidable::handle(Event e)
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