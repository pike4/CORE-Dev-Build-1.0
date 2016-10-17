#include "Position.h"
#include "GameObject.h"

void Position::assignPointers(GameObject* parent)
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
	x = NULL;
	y = NULL;
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