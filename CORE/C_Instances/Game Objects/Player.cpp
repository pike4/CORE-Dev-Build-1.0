#include "PLayer.h"
#include "Thing.h"
#include "SDL.h"
#include <stack>
#include <iostream>
#include "VideoManager.h"
#include "ObjectManager.h"

Player::Player(int aX, int aY, int aW, int aH, SDL_Texture* texture) : Mobile(aX, aY, texture), Collidable(aX, aY, aW, aH)
{
	x = aX;
	y = aY;
	mTexture = texture;
	xVel = 0;
	yVel = 0;
	boundingBox.x = aX;
	boundingBox.y = aY;
	boundingBox.w = aW;
	boundingBox.h = aH;
	walkSpeed = 2;

	prevXPtr = &prevX;
	prevYPtr = &prevY;
}

Player::Player(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Visible*>* drawVector, std::vector<Updatable*>* updateVector, std::vector<Collidable*>* collidableVector)
: Mobile(node, objectVector, drawVector, updateVector), Collidable(node, collidableVector)
{
	ObjectManager::player = this;
}

void Player::move()
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
	move();
}

void Player::walkDown(int type)
{
	yVel = 4;
}

void Player::walkUp(int type)
{
	yVel = -4;
}

void Player::walkLeft(int type)
{
	xVel = -4;
}

void Player::walkRight(int type)
{
	xVel = 4;
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