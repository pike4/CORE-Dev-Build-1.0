#include "BouncingBall.h"
#include "VideoManager.h"
#include "Math.h"

BouncingBall::BouncingBall(int x, int y, int w, int h, SDL_Texture* mTexture)
	:Mobile(x, y, mTexture), Collidable(x, y, w, h)
{
	xVel = 0;
	yVel = 0;
}

BouncingBall::BouncingBall(int x, int y, int w, int h, double aXVel, double aYVel, SDL_Texture* mTexture)
	:Mobile(x, y, mTexture), Collidable(x, y, w, h)
{
	xVel = aXVel;
	yVel = aYVel;

	prevXPtr = &prevX;
	prevYPtr = &prevY;
}

void BouncingBall::update()
{
	prevX = x;
	prevY = y;

	x += xVel;
	y += yVel;

	boundingBox.x = x;
	boundingBox.y = y;

	if (xVel < 0)
	{
		movementVector.x = prevX + boundingBox.w;
		movementVector.w = xVel - ( boundingBox.w);
	}

	else if (xVel > 0)
	{
		movementVector.x = prevX;
		movementVector.w = xVel + ( boundingBox.w);
	}

	if (yVel < 0)
	{
		movementVector.y = prevY + boundingBox.h;
		movementVector.h = yVel -  boundingBox.h;
	}

	else if (yVel > 0)
	{
		movementVector.y = prevY;
		movementVector.h = yVel +  boundingBox.h;
	}

	
}

void BouncingBall::draw(SDL_Renderer* renderer)
{
	SDL_RenderFillRect(renderer, &movementVector);
	VideoManager::applyTexture(x, y, renderer, mTexture);
}

BouncingBall::~BouncingBall(){}