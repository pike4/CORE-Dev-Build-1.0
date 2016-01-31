#include "Mobile.h"

void Mobile::move()
{
	x += xVel;
	y += yVel;
}

void Mobile::setXVel(double value)
{
	xVel = value;
}

void Mobile::setYVel(double value)
{
	yVel = value;
}

Mobile::Mobile(int x, int y, SDL_Texture* texture) : Visible(texture), BaseObject(x, y)
{}
