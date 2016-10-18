#include "Mobile.h"
#include "VideoManager.h"
#include "Entity.h"

void Mobile::updatePos()
{
	prevX = x;
	prevY = y;

	x += xVel;
	y += yVel;

	//parent->move(x, y);
}

void Mobile::setXVel(double value)
{
	xVel = value;
}

void Mobile::setYVel(double value)
{
	yVel = value;
}

int Mobile::getX()
{
	return x;
}

int Mobile::getY()
{
	return y;
}

Mobile::Mobile(pugi::xml_node node, std::vector<BaseObject*>* objectVector)
	: BaseObject(node, objectVector)
{
	//Same
}

Mobile::Mobile(pugi::xml_node node, Room* room): BaseObject(node, room)
{
	//Samey same
}

Mobile::Mobile(pugi::xml_node node) : BaseObject(node)
{

}

void Mobile::move(int aX, int aY)
{
	x = aX;
	y = aY;
}

void Mobile::addTo(Room* room)
{
	room->updateVector->push_back(this);
}

void Mobile::update()
{
	updatePos();
}

Mobile::~Mobile()
{
	
}