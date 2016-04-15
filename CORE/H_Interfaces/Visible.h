#pragma once
#include "SDL.h"
#include "BaseObject.h"
#include "pugixml.hpp"



class Visible
{
public:
	SDL_Texture* mTexture;

	Visible(SDL_Texture* texture);
	Visible(pugi::xml_node);
	Visible();
	virtual ~Visible();

	virtual void draw(SDL_Renderer* renderer);

	virtual int getX() = 0;
	virtual int getY() = 0;
};