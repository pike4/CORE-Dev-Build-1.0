#pragma once
#include "SDL.h"
#include "BaseObject.h"
#include "pugixml.hpp"
#include <vector>



class Visible
{
public:
	SDL_Texture* mTexture;

	Visible(SDL_Texture* texture);
	Visible(pugi::xml_node, std::vector<Visible*>*);
	Visible();
	virtual ~Visible();

	virtual void draw(SDL_Renderer* renderer);

	virtual int getX() = 0;
	virtual int getY() = 0;
};