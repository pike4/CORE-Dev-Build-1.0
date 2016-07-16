#include "BouncingBall.h"
#include "VideoManager.h"
#include "Math.h"
#include "Cursor.h"

BouncingBall::BouncingBall(int x, int y, int w, int h, SDL_Texture* mTexture)
	:Mobile(x, y, mTexture), Collidable(x, y, w, h)
{
	xVel = 0;
	yVel = 0;

	collidableType = Entity;
}

BouncingBall::BouncingBall(int x, int y, int w, int h, double aXVel, double aYVel, SDL_Texture* mTexture)
	:Mobile(x, y, mTexture), Collidable(x, y, w, h)
{
	xVel = aXVel;
	yVel = aYVel;

	SDL_QueryTexture(mTexture, NULL, NULL, &boundingBox.w, &boundingBox.h);

	prevXPtr = &prevX;
	prevYPtr = &prevY;

	collidableType = Entity;
}

BouncingBall::BouncingBall(pugi::xml_node node, std::vector<BaseObject*>* objectVec, std::vector<Visible*>* drawVec, std::vector<Updatable*>* updateVec, std::vector<Collidable*>* collidableVector)
	:Mobile(node, objectVec, drawVec, updateVec), Collidable(node, collidableVector)
{
	int load_xVel, loadyVel;

	char* str_xVel = (char*)node.child("xVel").first_child().value();
	char* str_yVel = (char*)node.child("yVel").first_child().value();

	try { xVel = stoi(str_xVel); }
	catch(exception)
	{ xVel = 0; }

	try { yVel = stoi(str_yVel); }
	catch (exception)
	{ yVel = 0; }


	SDL_QueryTexture(mTexture, NULL, NULL, &boundingBox.w, &boundingBox.h);

	prevXPtr = &prevX;
	prevYPtr = &prevY;

	collidableType = Entity;
}

void BouncingBall::update()
{
	prevX = x;
	prevY = y;

	x += (int) xVel;
	y += (int) yVel;

	boundingBox.x = x;
	boundingBox.y = y;

	if (xVel < 0)
	{
		movementVector.x = (int) prevX + boundingBox.w;
		movementVector.w = (int) xVel - ( boundingBox.w);
	}

	else if (xVel >= 0)
	{
		movementVector.x = prevX;
		movementVector.w = xVel + ( boundingBox.w);
	}

	if (yVel < 0)
	{
		movementVector.y = prevY + boundingBox.h;
		movementVector.h = yVel -  boundingBox.h;
	}

	else if (yVel >= 0)
	{
		movementVector.y = prevY;
		movementVector.h = yVel +  boundingBox.h;
	}

	
}

void BouncingBall::draw(SDL_Renderer* renderer)
{
	//SDL_RenderFillRect(renderer, &movementVector);
	VideoManager::applyTexture(x, y, renderer, mTexture);
}

void BouncingBall::onCollide(Player* h)
{

}

void BouncingBall::onCollide(BouncingBall* h)
{

}

void BouncingBall::onCollide(Cursor* C)
{
	
}

void BouncingBall::onCollide(Door* d) {}

BouncingBall::~BouncingBall(){}