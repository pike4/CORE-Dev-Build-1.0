#pragma once
#include "Mobile.h"
#include "Collidable.h"
#include "SDL.h"

class BouncingBall : public Mobile, public Collidable
{
public:
	BouncingBall(int x, int y, int w, int h, SDL_Texture* m_Texture);
	BouncingBall(int x, int y, int w, int h, double xVel, double yVel, SDL_Texture* m_Texture);
	void update();
	virtual void draw(SDL_Renderer* renderer);
	virtual ~BouncingBall();

};