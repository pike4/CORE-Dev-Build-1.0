#include "Position.h"
#include "Entity.h"
#include "DefaultNode.h"

void Position::getText(DefaultNode* def) {}

void Position::get_data(DataSource* source)
{
	x = source->getData<int>("x");
	y = source->getData<int>("y");
}

void Position::handle(Event e)
{
	switch (e.opcode)
	{
	//case updateStep:

	//	break;
	//case updatePos:
	//	*x = e[0];
	//	*y = e.arguments[0];
	//	break;
	}
}

Position::Position()
{
	pointers.push_back({ "x", &x });
	pointers.push_back({ "y", &y });
}

Position::Position(DefaultNode* definer)
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