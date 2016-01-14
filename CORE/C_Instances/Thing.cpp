#include "Mobile.h"
#include "VideoManager.h"
#include "ObjectManager.h"

void Thing::update()
{
	//x += xVel;
	//y += yVel;
	move();
}

Thing::Thing(int x, int y, SDL_Texture* texture) : Mobile(x, y, texture)
{
	xVel = 0;
	yVel = 0;

	VideoManager::addVisible(this);
	ObjectManager::addUpdatable(this);
}

Thing::Thing(int x, int y, int xVel, int yVel, SDL_Texture* texture) : Mobile(x, y, texture)
{
	this->xVel = xVel;
	this->yVel = yVel;

	VideoManager::addVisible(this);
	ObjectManager::addUpdatable(this);
}


int Thing::getX()
{
	return x;
}
int Thing::getY()
{
	return y;
}