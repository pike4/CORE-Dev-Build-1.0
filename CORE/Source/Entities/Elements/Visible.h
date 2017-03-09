#pragma once
#include "SDL.h"
#include "pugixml.hpp"
#include <vector>

class Room;

class Visible
{
public:
	SDL_Texture* mTexture;

	Visible(SDL_Texture* texture);
	Visible(pugi::xml_node, Room* room);
	Visible(pugi::xml_node);
	Visible(pugi::xml_node, std::vector<Visible*>* drawVector);
	Visible(Room*);
	Visible();
	virtual ~Visible();

	virtual void draw(SDL_Renderer* renderer);

	virtual int getX() = 0;
	virtual int getY() = 0;
};