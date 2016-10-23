#include "Position.h"
#include "Entity.h"

void Position::assignPointers(Entity* parent)
{
	x = (int*) parent->getPointer("x", sizeof(int));
	y = (int*) parent->getPointer("y", sizeof(int));

	*x = 0;
	*y = 0;
}

void Position::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case updateStep:

		break;
	}
}

Position::Position()
{
	pointers.push_back({ "x", sizeof(int), &x });
	pointers.push_back({ "y", sizeof(int), &y });
}

Position::Position(pugi::xml_node node)
	: Position()
{}

Position::Position(Position& other)
	:Position()
{}

Component* Position::spawnCopy()
{
	return new Position();
}

void Position::move(int aX, int aY)
{
	*x = aX;
	*y = aY;
}