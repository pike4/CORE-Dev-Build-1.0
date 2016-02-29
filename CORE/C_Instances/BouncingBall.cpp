#include "BouncingBall.h"
#include "VideoManager.h"

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

	movementVector.x = prevX;
	movementVector.w = boundingBox.w + x - prevX;

	movementVector.y = prevY;
	movementVector.h = boundingBox.h + y - prevY;

	boundingBox.x = x;
	boundingBox.y = y;
}

void BouncingBall::draw(SDL_Renderer* renderer)
{
	SDL_RenderFillRect(renderer, &movementVector);
	VideoManager::applyTexture(x, y, renderer, mTexture);
}

BouncingBall::~BouncingBall(){}