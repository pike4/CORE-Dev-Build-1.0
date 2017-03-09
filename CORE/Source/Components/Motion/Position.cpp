#include "Position.h"
#include "Entity.h"
#include "Node.h"

void Position::getText(Node* def) {}

void Position::get_data(DataSource* source)
{
	x = source->getData<int>("x");
	y = source->getData<int>("y");
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

Position::Position(Node* definer)
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