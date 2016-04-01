#include "Collidable.h"
#include "ObjectManager.h"
#include "stdio.h"

Collidable::Collidable(int x, int y, int w, int h)
{
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = w;
	boundingBox.h = h;

	ObjectManager::addCollidable(this);
}

Collidable::~Collidable()
{
	printf("a\n");
}

void Collidable::onCollide(Collidable* C)
{
	switch (C->collidableType)
	{
	case Entity:
		onCollide((BouncingBall*)C);
		break;
	case cCursor:
		onCollide((Cursor*)C);
		break;
	case eWall:
		break;

	default:
		break;

	}
}