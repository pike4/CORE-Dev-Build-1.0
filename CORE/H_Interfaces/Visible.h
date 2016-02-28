#pragma once
#include "SDL.h"
#include "BaseObject.h"



class Visible
{
public:
	SDL_Texture* mTexture;

	Visible(SDL_Texture* texture);
	virtual ~Visible();

	virtual void draw(SDL_Renderer* renderer);

	virtual int getX() = 0;
	virtual int getY() = 0;
};