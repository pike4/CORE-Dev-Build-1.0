#include "Mobile.h"
#include "VideoManager.h"

void Mobile::move()
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
	VideoManager::applyTexture(x, y, renderer, mTexture);
}

Mobile::Mobile(int x, int y, SDL_Texture* texture) : Visible(texture), BaseObject(x, y)
{
	//All instantiation taken care of by parents. Free loading prick.
}

Mobile::Mobile(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Visible*>* drawVector, std::vector<Updatable*>*  updateVector) : Visible(node, drawVector), BaseObject(node, objectVector), Updatable(updateVector)
{
	//Same
}

Mobile::~Mobile()
{
	
}