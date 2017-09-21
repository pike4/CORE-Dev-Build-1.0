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

void Velocity::get_data(DataSource* source)
{
   Position::get_data(source);
   xVel = source->getData<double>("xVel");
   yVel = source->getData<double>("yVel");
}

void Velocity::handle(Event e)
{
	Position::handle(e);
	switch (e.opcode)
	{
	case updateStep:
		*x += *xVel;
		*y += *yVel;
		break;
	}
}