#include "BouncingBall.h"

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
}

void BouncingBall::update()
{
	x += xVel;
	y += yVel;

	boundingBox.x = x;
	boundingBox.y = y;
}

BouncingBall::~BouncingBall(){}