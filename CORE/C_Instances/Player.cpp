#include "PLayer.h"
#include "Thing.h"
#include "SDL.h"
#include <stack>
#include <iostream>
#include "VideoManager.h"
#include "ObjectManager.h"

Player::Player(int x, int y, SDL_Texture* texture) : Mobile(x, y, texture)
{
	this->x = x;
	this->y = y;
	this->mTexture = texture;
	this->xVel = 0;
	this->yVel = 0;
	yDirectionStack.push(0);
	xDirectionStack.push(0);
	walkSpeed = 2;

	VideoManager::addVisible(this);
	ObjectManager::addUpdatable(this);
}

void Player::move()
{
	x += xDirectionStack.top();
	y += yDirectionStack.top();
}

void Player::update()
{
	move();
}

void Player::walkDown(int type)
{
	if (type > 0)
	{
		if (!yDirectionStack.empty() && yDirectionStack.top() <= 0 && yDirectionStack.size() <= 2)
		{
			yDirectionStack.push(walkSpeed);
			//std::cout << yDirectionStack.top(), type;
		}
	}

	else
	{
		if (!yDirectionStack.empty() && yDirectionStack.top() != 0)
		{
			yDirectionStack.pop();
		}
	}
}

void Player::walkUp(int type)
{
	if (type > 0)
	{
		if (!yDirectionStack.empty() && yDirectionStack.top() >= 0 && yDirectionStack.size() <= 2)
		{
			yDirectionStack.push(walkSpeed * -1);
		}
	}

	else
	{
		if (!yDirectionStack.empty() && yDirectionStack.top() != 0)
		{
			yDirectionStack.pop();
		}
	}
}

void Player::walkLeft(int type)
{
	if (type > 0)
	{
		if (!xDirectionStack.empty() && xDirectionStack.top() >= 0 && yDirectionStack.size() <= 2)
		{
			xDirectionStack.push(walkSpeed * -1);
		}
	}

	else
	{
		if (!xDirectionStack.empty() && xDirectionStack.top() != 0)
		{
			xDirectionStack.pop();
		}
	}
}

void Player::walkRight(int type)
{
	if (type > 0)
	{
		if (!xDirectionStack.empty() && xDirectionStack.top() <= 0 && yDirectionStack.size() <= 2)
		{
			xDirectionStack.push(walkSpeed);
		}
	}

	else
	{
		if (!xDirectionStack.empty() && xDirectionStack.top() != 0)
		{
			xDirectionStack.pop();
		}
	}
}