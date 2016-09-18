#include "Player.h"
#include "Thing.h"
#include "SDL.h"
#include <stack>
#include <iostream>
#include "VideoManager.h"
#include "ObjectManager.h"
#include "Subject.h"
#include "EventManager.h"
#include "ImageElement.h"

//Player::Player(int aX, int aY, int aW, int aH, SDL_Texture* texture) : Mobile(aX, aY, texture), Collidable(aX, aY, aW, aH), Controllable()
//{
//	x = aX;
//	y = aY;
//	element = new ImageElement(aX, aY, aW, aH, texture);
//	xVel = 0;
//	yVel = 0;
//	boundingBox.x = aX;
//	boundingBox.y = aY;
//	boundingBox.w = aW;
//	boundingBox.h = aH;
//	walkSpeed = 2;
//
//	prevXPtr = &prevX;
//	prevYPtr = &prevY;
//}

Player::Player(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Drawable*>* drawVector, std::vector<Updatable*>* updateVector, std::vector<Collidable*>* collidableVector, std::vector<Controllable*>* controllableVector)
: Mobile(node, objectVector), Collidable(node, collidableVector), Controllable(controllableVector)
{
	prevXPtr = &prevX;
	prevYPtr = &prevY;

	collidableType = cPlayer;
}

Player::Player(pugi::xml_node node)
	:Mobile(node), Collidable(node)
{

}

Player::Player(pugi::xml_node node, Room* room)
	:Mobile(node, room), Collidable(node, room), Controllable(room)
{
	prevXPtr = &prevX;
	prevYPtr = &prevY;

	collidableType = cPlayer;
}

BaseObject* Player::spawnCopy(Room* room)
{
	return NULL;
}

void Player::updatePos()
{
	x += xVel;
	y += yVel;
	prevX = x;
	prevY = y;
	boundingBox.x = x;
	boundingBox.y = y;
}

void Player::update()
{
	updatePos();
	//move(x, y);
}

void Player::walkDown(int type)
{
	if (type)
	{
		yVel += 1;
	}

	else
	{
		yVel -= 1;
	}
}

void Player::walkUp(int type)
{
	if (type)
	{
		yVel -= 1;
	}

	else
	{
		yVel += 1;
	}
}

void Player::walkLeft(int type)
{
	if (type)
	{
		xVel -= 1;
	}

	else
	{
		xVel += 1;
	}
}

void Player::walkRight(int type)
{
	if (type)
	{
		xVel += 1;
	}

	else
	{
		xVel -= 1;
	}
}

void Player::onCollide(BouncingBall* b)
{

}

void Player::onCollide(Player* p)
{

}

void Player::onCollide(Cursor* c)
{

}

void Player::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case walkForwardButtonDown:
		if (upDown)
			yVel -=1;
		else
			yVel += 1;
		break;
	case walkBackwardButtonDown:
		if (upDown)
			yVel += 1;
		else
			yVel -= 1;
		break;
	case walkLeftButtonDown:
		if (upDown)
			xVel -= 1;
		else
			xVel += 1;
		break;
	case walkRightButtonDown:
		if (upDown)
			xVel += 1;
		else
			xVel -= 1;
		break;
	}
}

void Player::onCollide(Door* d) {}