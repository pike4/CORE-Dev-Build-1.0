#include "Velocity.h"
#include "Entity.h"

Velocity::Velocity()
	:Position()
{
	pointers.push_back({ "xVel", sizeof(double), &xVel });
	pointers.push_back({ "yVel", sizeof(double), &yVel });
	pointers.push_back({ "direction", sizeof(int), &direction });
}

Velocity::Velocity(pugi::xml_node node)
	: Position()
{}

Velocity::Velocity(Velocity& other)
	: Position()
{}

Component* Velocity::spawnCopy()
{
	return new Velocity();
}

void Velocity::move(int aX, int aY)
{
	*x = aX;
	*y = aY;
}

void Velocity::assignPointers(Entity* parent)
{
	Position::assignPointers(parent);

	xVel = (double*)parent->getPointer("xVel", sizeof(double));
	yVel = (double*)parent->getPointer("yVel", sizeof(double));

	*xVel = 0;
	*yVel = 0;
}

void Velocity::handleInput(int key, int upDown, int aX, int aY)
{
	Position::handleInput(key, upDown, aX, aY);

	switch (key)
	{
	case updateStep:
		*x += *xVel;
		*y += *yVel;
		break;
	}
}