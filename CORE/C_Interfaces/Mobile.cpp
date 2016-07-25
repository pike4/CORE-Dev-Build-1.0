#include "Mobile.h"
#include "VideoManager.h"

void Mobile::updatePos()
{
	prevX = x;
	prevY = y;

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

int Mobile::getX()
{
	return x;
}

int Mobile::getY()
{
	return y;
}

void Mobile::draw(SDL_Renderer* renderer)
{
	element->draw(renderer);
}


Mobile::Mobile(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Drawable*>* drawVector, std::vector<Updatable*>*  updateVector) : SimpleDrawable(node), BaseObject(node, objectVector), Updatable(updateVector)
{
	//Same
}

Mobile::Mobile(pugi::xml_node node, Room* room): SimpleDrawable(node, room), BaseObject(node, room), Updatable(room)
{
	//Samey same
}

Mobile::~Mobile()
{
	
}