#include "Position.h"
#include "Entity.h"

void Position::assignPointers(Entity* parent)
{
	x = (SimpleData<int>*) parent->getData<int>("x");
	y = (SimpleData<int>*) parent->getData<int>("y");

	*x = 0;
	*y = 0;
}

void Position::handleInput(int key, int upDown, int aX, int aY)
{
	switch (key)
	{
	case updateStep:

		break;
	case updatePos:
		*x = aX;
		*y = aY;
		break;
	}
}

Position::Position()
{
	pointers.push_back({ "x", &x });
	pointers.push_back({ "y", &y });
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