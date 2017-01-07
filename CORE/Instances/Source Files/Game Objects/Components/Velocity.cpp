#include "Velocity.h"
#include "Entity.h"

Velocity::Velocity()
	:Position()
{
	pointers.push_back({ "xVel", &xVel });
	pointers.push_back({ "yVel", &yVel });
	pointers.push_back({ "direction", &direction });
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

	xVel = parent->getData<double>("xVel");
	yVel = parent->getData<double>("yVel");

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